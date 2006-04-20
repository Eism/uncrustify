/**
 * @file options.h
 * Enum and settings for all the options.
 *
 * $Id$
 */
#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED


typedef enum
{
   AT_BOOL,    /**< true / false */
   AT_IARF,    /**< Ignore / Add / Remove / Force */
   AT_NUM,     /**< Number */
} argtype_t;

/** Arg values - these are bit fields*/
typedef enum
{
   AV_IGNORE = 0,
   AV_ADD    = 1,
   AV_REMOVE = 2,
   AV_FORCE  = 3, /**< remove + add */
} argval_t;

typedef union op_val_t
{
   argval_t a;
   int      n;
   bool     b;
} op_val_t;

/**
 * Keep this grouped by functionality
 */
enum uncrustify_options
{
   /*
    * Basic Indenting stuff
    */
   UO_indent,                   //TODO: 0=don't change indentation, 1=change indentation

   UO_input_tab_size,           // tab size on input file: usually 8
   UO_output_tab_size,          // tab size for output: usually 8

   UO_indent_columns,           // ie 3 or 8
   UO_indent_with_tabs,         // 1=only to the 'level' indent, 2=use tabs for indenting
   UO_indent_brace_struct,      //TODO: spaces to indent brace after struct/enum/union def
   UO_indent_paren,             //TODO: indent for open paren on next line (1)
   UO_indent_paren_nl,          // indent-align under paren for open followed by nl
   UO_leave_preproc_space,      //TODO: if true, leave the spaces between '#' and preprocessor commands
   UO_pp_indent,                //TODO: spaces to indent preprocessors (0)

   UO_indent_switch_case,       // spaces to indent case from switch
   UO_indent_case_body,         // spaces to indent case body from case
   UO_indent_case_brace,        //TODO: spaces to indent '{' from case (usually 0 or indent_columns)

   UO_indent_brace,             // spaces to indent '{' from level (usually 0)
   UO_indent_braces,            // whether to indent the braces of not
   UO_indent_label,             // 0=left >0=col from left, <0=sub from brace indent

   UO_indent_align_string,      // True/False - indent align broken strings

   UO_indent_col1_comment,      // indent comments in column 1

   UO_indent_func_call_param,   // indent continued function calls to indent_columns

   /*
    * Misc inter-element spacing
    */

   UO_sp_before_sparen,     // space before '(' of 'if/for/while/switch'
   UO_sp_after_sparen,      /* space after  ')' of 'if/for/while/switch'
                             * the do-while does not get set here */
   UO_sp_paren_brace,       // space between ')' and '{'

   UO_sp_after_cast,        // space after cast - "(int) a" vs "(int)a"

   UO_sp_before_byref,      // space before '&' of 'fcn(int& idx)'

   UO_sp_inside_angle,      // space inside '<>', as in '<class T>'
   UO_sp_inside_sparen,     // space inside 'if( xxx )' vs 'if(xxx)'
   UO_sp_inside_fparen,     // space inside 'foo( xxx )' vs 'foo(xxx)'
   UO_sp_inside_paren,      // space inside '+ ( xxx )' vs '+ (xxx)'
   UO_sp_inside_square,     // space inside 'byte[ 5 ]' vs 'byte[5]'
   UO_sp_after_angle,       // space after  '<>', as in '<class T>'
   UO_sp_before_angle,      // space before '<>', as in '<class T>'
   UO_sp_before_square,     // space before single '['
   UO_sp_before_squares,    // space before '[]', as in 'byte []'

   UO_sp_paren_paren,       // space between nested parens - '( (' vs '(('

   UO_sp_return_paren,      // space between 'return' and '('
   UO_sp_sizeof_paren,      // space between 'sizeof' and '('

   UO_sp_after_comma,       // space after ','

   UO_sp_arith,             // space around + - / * etc
   UO_sp_bool,              // space around || &&
   UO_sp_compare,           // space around < > ==, etc
   UO_sp_assign,            // space around =, +=, etc

   UO_sp_func_def_paren,    // space between 'func' and '(' - "foo (" vs "foo("
   UO_sp_func_call_paren,   // space between 'func' and '(' - "foo (" vs "foo("
   UO_sp_func_proto_paren,  // space between 'func' and '(' - "foo (" vs "foo("
   UO_sp_func_class_paren,  // space between ctor/dtor and '('

   UO_sp_type_func,         // space between return type and 'func'
                            // a minimum of 1 is forced except for '*'

   UO_sp_special_semi,      /* space empty stmt ';' on while, if, for
                             * example "while (*p++ = ' ') ;" */
   UO_sp_before_semi,          // space before all ';'
   UO_sp_inside_braces,        // space inside '{' and '}' - "{ 1, 2, 3 }"
   UO_sp_inside_braces_enum,   // space inside enum '{' and '}' - "{ a, b, c }"
   UO_sp_inside_braces_struct, // space inside struct/union '{' and '}'


   /*
    * Line splitting options (for long lines)
    */

   UO_code_width,           //TODO: ie 80 columns
   UO_ls_before_bool_op,    //TODO: break line before of after boolean op
   UO_ls_before_paren,      //TODO: break before open paren
   UO_ls_after_arith,       //TODO: break after arith op '+', etc
   UO_ls_honor_newlines,    //TODO: don't remove newlines on split lines


   /*
    * code alignment (not left column spaces/tabs)
    */

   UO_align_with_tabs,            // use tabs for aligning (0/1)
   UO_align_on_tabstop,           // always align on tabstops
   UO_align_nl_cont,              // align the back-slash \n combo (macros)
   UO_align_enum_equ,             // align the '=' in enums
   UO_align_assign_span,          // align on '='. 0=don't align
   UO_align_assign_thresh,        // align on '='. 0=don't align
   UO_align_right_cmt_span,       // align comment that end lines. 0=don't align
   UO_align_var_def_span,         // align variable defs on variable (span for regular stuff)
   UO_align_var_def_inline,       // also align inline struct/enum/union var defs
   UO_align_var_def_star,         // the star is part of the variable name
   UO_align_var_def_colon,        // align the colon in struct bit fields
   UO_align_var_struct_span,      // span for struct/union (0=don't align)
   UO_align_pp_define_span,       // align bodies in #define statments
   UO_align_pp_define_col_min,    //TODO: min column for a #define value
   UO_align_pp_define_col_max,    //TODO: max column for a #define value
   UO_align_pp_define_gap,        // min space between define label and value "#define a <---> 16"
   UO_align_enum_col_min,         //TODO: the min column for enum '=' alignment
   UO_align_enum_col_max,         //TODO: the max column for enum '=' alignment
   UO_align_struct_init_span,     // align structure initializer values
   UO_align_func_proto_span,      // align function prototypes
   UO_align_number_left,          // left-align numbers (not fully supported, yet)
   UO_align_typedef_span,         // align single-line typedefs
   UO_align_typedef_gap,          // minimum spacing
   UO_align_keep_tabs,            // keep non-indenting tabs


   /*
    * Newline adding and removing options
    */

   UO_nl_fdef_brace,             // "int foo() {" vs "int foo()\n{"
   UO_nl_func_decl_args,         //TODO: newline after each ',' in a function decl
   UO_nl_func_decl_end,          //TODO: newline before the ')' in a function decl
   UO_nl_func_type_name,         //TODO: newline between return type and func name in def
   UO_nl_func_var_def_blk,       // newline after a block of variable defs
   UO_nl_before_case,            // newline before 'case' statement
   UO_nl_after_return,           /* newline after return statement */
   UO_nl_after_case,             /* disallow nested "case 1: a=3;" */
   UO_nl_fcall_brace,            /* newline between function call and open brace */
   UO_nl_squeeze_ifdef,          /* no blanks after #ifxx, #elxx, or before #endif */
   UO_nl_enum_brace,             /* nl between enum and brace */
   UO_nl_struct_brace,           /* nl between struct and brace */
   UO_nl_union_brace,            /* nl between union and brace */
   UO_nl_assign_brace,           /* nl between '=' and brace */

   UO_nl_do_brace,               /* nl between do and { */
   UO_nl_if_brace,               /* nl between if and { */
   UO_nl_for_brace,              /* nl between for and { */
   UO_nl_else_brace,             /* nl between else and { */
   UO_nl_while_brace,            /* nl between while and { */
   UO_nl_switch_brace,           /* nl between switch and { */
   UO_nl_brace_else,             // nl between } and else
   UO_nl_brace_while,            // nl between } and while of do stmt

   UO_nl_define_macro,           // alter newlines in #define macros


   /*
    * Blank line options
    */

   UO_blc_before_block_comment,      //TODO: before a block comment (stand-alone comment-multi)
   UO_blc_after_func_body,           //TODO: after the closing brace of a function body
   UO_blc_after_func_proto,          //TODO: after each prototype
   UO_blc_after_func_proto_group,    //TODO: after a block of prototypes
   UO_blc_after_var_def_group,       //TODO: after a group of variable defs at top of proc
   UO_blc_after_ifdef,               //TODO: after #if or #ifdef - but not if covers whole file
   UO_blc_max,                       //TODO: maximum consecutive newlines (3 is good)

   UO_eat_blanks_after_open_brace,   // remove blank lines after {
   UO_eat_blanks_before_close_brace, // remove blank lines before }


   /*
    * code modifying options (non-whitespace)
    */

   UO_mod_paren_on_return,       // add or remove paren on return
   UO_mod_full_brace_nl,         // max number of newlines to span w/o braces
   UO_mod_full_brace_if,         // add or remove braces on if
   UO_mod_full_brace_for,        // add or remove braces on for
   UO_mod_full_brace_do,         // add or remove braces on do
   UO_mod_full_brace_while,      // add or remove braces on while


   /*
    * Comment modifications
    */

   UO_cmt_star_cont,       // put a star on subsequent comment lines


   /* This is used to get the enumeration count */
   UO_option_count
};

struct options_name_tab
{
   int        id;
   argtype_t  type;
   const char *name;
};

#ifdef DEFINE_OPTION_NAME_TABLE

#define OPTDEF(_x, t)     { UO_ ## _x, t, # _x }

/* Keep this table sorted! */
options_name_tab option_name_table[] =
{
   OPTDEF(align_assign_span,             AT_NUM),
   OPTDEF(align_assign_thresh,           AT_NUM),
   OPTDEF(align_enum_col_max,            AT_NUM),
   OPTDEF(align_enum_col_min,            AT_NUM),
   OPTDEF(align_enum_equ,                AT_NUM),
   OPTDEF(align_func_proto_span,         AT_NUM),
   OPTDEF(align_keep_tabs,               AT_BOOL),
   OPTDEF(align_nl_cont,                 AT_BOOL),
   OPTDEF(align_number_left,             AT_BOOL),
   OPTDEF(align_on_tabstop,              AT_BOOL),
   OPTDEF(align_pp_define_col_max,       AT_NUM),
   OPTDEF(align_pp_define_col_min,       AT_NUM),
   OPTDEF(align_pp_define_gap,           AT_NUM),
   OPTDEF(align_pp_define_span,          AT_NUM),
   OPTDEF(align_right_cmt_span,          AT_NUM),
   OPTDEF(align_struct_init_span,        AT_NUM),
   OPTDEF(align_typedef_gap,             AT_NUM),
   OPTDEF(align_typedef_span,            AT_NUM),
   OPTDEF(align_var_def_colon,           AT_BOOL),
   OPTDEF(align_var_def_inline,          AT_BOOL),
   OPTDEF(align_var_def_span,            AT_NUM),
   OPTDEF(align_var_def_star,            AT_BOOL),
   OPTDEF(align_var_struct_span,         AT_NUM),
   OPTDEF(align_with_tabs,               AT_BOOL),
   OPTDEF(blc_after_func_body,           AT_NUM),
   OPTDEF(blc_after_func_proto,          AT_NUM),
   OPTDEF(blc_after_func_proto_group,    AT_NUM),
   OPTDEF(blc_after_ifdef,               AT_NUM),
   OPTDEF(blc_after_var_def_group,       AT_NUM),
   OPTDEF(blc_before_block_comment,      AT_NUM),
   OPTDEF(blc_max,                       AT_NUM),
   OPTDEF(cmt_star_cont,                 AT_BOOL),
   OPTDEF(code_width,                    AT_NUM),
   OPTDEF(eat_blanks_after_open_brace,   AT_BOOL),
   OPTDEF(eat_blanks_before_close_brace, AT_BOOL),
   OPTDEF(indent,                        AT_BOOL),
   OPTDEF(indent_align_string,           AT_BOOL),
   OPTDEF(indent_brace,                  AT_NUM),
   OPTDEF(indent_brace_struct,           AT_NUM),
   OPTDEF(indent_braces,                 AT_BOOL),
   OPTDEF(indent_case_body,              AT_NUM),
   OPTDEF(indent_case_brace,             AT_NUM),
   OPTDEF(indent_col1_comment,           AT_BOOL),
   OPTDEF(indent_columns,                AT_NUM),
   OPTDEF(indent_func_call_param,        AT_BOOL),
   OPTDEF(indent_label,                  AT_NUM),
   OPTDEF(indent_paren,                  AT_NUM),
   OPTDEF(indent_paren_nl,               AT_BOOL),
   OPTDEF(indent_switch_case,            AT_NUM),
   OPTDEF(indent_with_tabs,              AT_NUM),
   OPTDEF(input_tab_size,                AT_NUM),
   OPTDEF(leave_preproc_space,           AT_BOOL),
   OPTDEF(ls_after_arith,                AT_BOOL),
   OPTDEF(ls_before_bool_op,             AT_BOOL),
   OPTDEF(ls_before_paren,               AT_BOOL),
   OPTDEF(ls_honor_newlines,             AT_BOOL),
   OPTDEF(mod_full_brace_do,             AT_IARF),
   OPTDEF(mod_full_brace_for,            AT_IARF),
   OPTDEF(mod_full_brace_if,             AT_IARF),
   OPTDEF(mod_full_brace_nl,             AT_NUM),
   OPTDEF(mod_full_brace_while,          AT_IARF),
   OPTDEF(mod_paren_on_return,           AT_IARF),
   OPTDEF(nl_after_case,                 AT_BOOL),
   OPTDEF(nl_after_return,               AT_BOOL),
   OPTDEF(nl_assign_brace,               AT_IARF),
   OPTDEF(nl_before_case,                AT_BOOL),
   OPTDEF(nl_brace_else,                 AT_IARF),
   OPTDEF(nl_brace_while,                AT_IARF),
   OPTDEF(nl_define_macro,               AT_BOOL),
   OPTDEF(nl_do_brace,                   AT_IARF),
   OPTDEF(nl_else_brace,                 AT_IARF),
   OPTDEF(nl_enum_brace,                 AT_IARF),
   OPTDEF(nl_fcall_brace,                AT_IARF),
   OPTDEF(nl_fdef_brace,                 AT_IARF),
   OPTDEF(nl_for_brace,                  AT_IARF),
   OPTDEF(nl_func_decl_args,             AT_IARF),
   OPTDEF(nl_func_decl_end,              AT_IARF),
   OPTDEF(nl_func_type_name,             AT_IARF),
   OPTDEF(nl_func_var_def_blk,           AT_NUM),
   OPTDEF(nl_if_brace,                   AT_IARF),
   OPTDEF(nl_squeeze_ifdef,              AT_BOOL),
   OPTDEF(nl_struct_brace,               AT_IARF),
   OPTDEF(nl_switch_brace,               AT_IARF),
   OPTDEF(nl_union_brace,                AT_IARF),
   OPTDEF(nl_while_brace,                AT_IARF),
   OPTDEF(output_tab_size,               AT_NUM),
   OPTDEF(pp_indent,                     AT_NUM),
   OPTDEF(sp_after_angle,                AT_IARF),
   OPTDEF(sp_after_cast,                 AT_IARF),
   OPTDEF(sp_after_comma,                AT_IARF),
   OPTDEF(sp_after_sparen,               AT_IARF),
   OPTDEF(sp_arith,                      AT_IARF),
   OPTDEF(sp_assign,                     AT_IARF),
   OPTDEF(sp_before_angle,               AT_IARF),
   OPTDEF(sp_before_byref,               AT_IARF),
   OPTDEF(sp_before_semi,                AT_IARF),
   OPTDEF(sp_before_sparen,              AT_IARF),
   OPTDEF(sp_before_square,              AT_IARF),
   OPTDEF(sp_before_squares,             AT_IARF),
   OPTDEF(sp_bool,                       AT_IARF),
   OPTDEF(sp_compare,                    AT_IARF),
   OPTDEF(sp_func_call_paren,            AT_IARF),
   OPTDEF(sp_func_class_paren,           AT_IARF),
   OPTDEF(sp_func_def_paren,             AT_IARF),
   OPTDEF(sp_func_proto_paren,           AT_IARF),
   OPTDEF(sp_inside_angle,               AT_IARF),
   OPTDEF(sp_inside_braces,              AT_IARF),
   OPTDEF(sp_inside_braces_enum,         AT_IARF),
   OPTDEF(sp_inside_braces_struct,       AT_IARF),
   OPTDEF(sp_inside_fparen,              AT_IARF),
   OPTDEF(sp_inside_paren,               AT_IARF),
   OPTDEF(sp_inside_sparen,              AT_IARF),
   OPTDEF(sp_inside_square,              AT_IARF),
   OPTDEF(sp_paren_brace,                AT_IARF),
   OPTDEF(sp_paren_paren,                AT_IARF),
   OPTDEF(sp_return_paren,               AT_IARF),
   OPTDEF(sp_sizeof_paren,               AT_IARF),
   OPTDEF(sp_special_semi,               AT_IARF),
   OPTDEF(sp_type_func,                  AT_IARF),
};

#endif   /* DEFINE_OPTION_NAME_TABLE */

#endif   /* OPTIONS_H_INCLUDED */

