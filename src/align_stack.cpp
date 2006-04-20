/**
 * @file align_stack.c
 * Manages a align stack, which is just a pair of chunk stacks.
 * There can be at most 1 item per line in the stack.
 * The seqnum is actually a line counter.
 *
 * $Id$
 */

#include "align_stack.h"
#include "prototypes.h"

/**
 * Resets the two ChunkLists and zeroes local vars.
 *
 * @param span    The row span limit
 * @param thresh  The column threshold
 */
void AlignStack::Start(int span, int thresh)
{
   LOG_FMT(LAS, "Start(%d, %d)\n", span, thresh);

   m_aligned.Reset();
   m_skipped.Reset();
   m_span      = span;
   m_thresh    = thresh;
   m_max_col   = 0;
   m_nl_seqnum = 0;
   m_seqnum    = 0;
}

/**
 * Calls Add on all the skipped items
 */
void AlignStack::ReAddSkipped()
{
   if (!m_skipped.Empty())
   {
      /* Make a copy of the ChunkStack and clear m_skipped */
      m_scratch.Set(m_skipped);
      m_skipped.Reset();

      const ChunkStack::Entry *ce;

      /* Need to add them in order so that m_nl_seqnum is correct */
      for (int idx = 0; idx < m_scratch.Len(); idx++)
      {
         ce = m_scratch.Get(idx);
         LOG_FMT(LAS, "ReAddSkipped [%d] - ", ce->m_seqnum);
         Add(ce->m_pc, ce->m_seqnum);
      }

      /* Check to see if we need to flush right away */
      NewLines(0);
   }
}

/**
 * Adds an entry to the appropriate stack.
 *
 * @param pc      The chunk
 * @param seqnum  Optional seqnum (0=assign one)
 */
void AlignStack::Add(chunk_t *pc, int seqnum)
{
   /* Assign a seqnum if needed */
   if (seqnum == 0)
   {
      seqnum = m_seqnum;
   }

   /* Check threshold limits */
   if ((m_max_col == 0) || (m_thresh == 0) ||
       ((pc->column <= (m_max_col + m_thresh)) &&
        (pc->column >= (m_max_col - m_thresh))))
   {
      /* we are adding it, so update the newline seqnum */
      if (seqnum > m_nl_seqnum)
      {
         m_nl_seqnum = seqnum;
      }

      m_aligned.Push(pc, seqnum);

      /* See if this pushes out the max_col */
      int endcol = pc->column + pc->len;
      if (endcol > m_max_col)
      {
         LOG_FMT(LAS, "Add-aligned [%d/%d/%d]: line %d, col %d : max_col old %d, new %d\n",
                 seqnum, m_nl_seqnum, m_seqnum,
                 pc->orig_line, pc->column, m_max_col, endcol);
         m_max_col = endcol;

         /**
          * If there were any entries that were skipped, re-add them as they
          * may now be within the threshold
          */
         if (!m_skipped.Empty())
         {
            ReAddSkipped();
         }
      }
      else
      {
         LOG_FMT(LAS, "Add-aligned [%d/%d/%d]: line %d, col %d : col %d <= %d\n",
                 seqnum, m_nl_seqnum, m_seqnum,
                 pc->orig_line, pc->column, endcol, m_max_col);
      }
   }
   else
   {
      /* The threshold check failed, so add it to the skipped list */
      m_skipped.Push(pc, seqnum);
      LOG_FMT(LAS, "Add-skipped [%d/%d/%d]: line %d, col %d <= %d + %d\n",
              seqnum, m_nl_seqnum, m_seqnum,
              pc->orig_line, pc->column, m_max_col, m_thresh);
   }
}

/**
 * Adds some newline and calls Flush() if needed
 */
void AlignStack::NewLines(int cnt)
{
   if (!m_aligned.Empty())
   {
      m_seqnum += cnt;
      if (m_seqnum > (m_nl_seqnum + m_span))
      {
         LOG_FMT(LAS, "Newlines<%d>-", cnt);
         Flush();
      }
      else
      {
         LOG_FMT(LAS, "Newlines<%d>\n", cnt);
      }
   }
}

/**
 * Aligns all the stuff in m_aligned.
 * Re-adds 'newer' items in m_skipped.
 */
void AlignStack::Flush()
{
   int                     last_seqnum = 0;
   int                     idx;
   const ChunkStack::Entry *ce = NULL;

   LOG_FMT(LAS, "Flush\n");

   for (idx = 0; idx < m_aligned.Len(); idx++)
   {
      ce = m_aligned.Get(idx);

      /* Indent, right aligning the aligned token */
      indent_to_column(ce->m_pc, m_max_col - ce->m_pc->len);
   }

   if (ce != NULL)
   {
      last_seqnum = ce->m_seqnum;
      m_aligned.Reset();
   }
   m_max_col = 0;

   if (m_skipped.Empty())
   {
      /* Nothing was skipped, sync the seqnums */
      m_nl_seqnum = m_seqnum;
   }
   else
   {
      /* Remove all items with seqnum < last_seqnum */
      for (idx = 0; idx < m_skipped.Len(); idx++)
      {
         if (m_skipped.Get(idx)->m_seqnum < last_seqnum)
         {
            m_skipped.Zap(idx);
         }
      }
      m_skipped.Collapse();

      /* Add all items from the skipped list */
      ReAddSkipped();
   }
}

/**
 * Aligns everything else and resets the lists.
 */
void AlignStack::End()
{
   if (!m_aligned.Empty())
   {
      LOG_FMT(LAS, "End-");
      Flush();
   }

   m_aligned.Reset();
   m_skipped.Reset();
}

