#ifndef _ICHOR_PARSER_H_
#define _ICHOR_PARSER_H_

/*
 *  Grammar rules for the language so far, will need to update as I have more ideas
 *  Using regex style for matching, + means one or more of the preceding, * means zero or more
 *
 *  program          -> function_def
 *  function_def     -> type T_IDENT LPAREN paramater_list* RPARAN block
 *  paramater_list   -> param (T_COMMA, param)*
 *  param            -> type T_IDENT
 *  block            -> T_LBRACE statement* T_RBRACE
 *  statement        -> var_decleration
 *                      | return_statement 
 *                      | print_statement
 *                      | expr_statement
 *  var_decleration  -> type T_IDENT T_ASSIGN expr T_SEMI
 *  return_statement -> T_RETURN expr* T_SEMI
 *  print_statement  -> T_PRINT T_LPAREN expr T_RPAREN T_SEMI
 *  expr_statement   -> expr T_SEMI
 *  expr             -> assignment
 *  assignment       -> comparison (T_ASSIGN comparison)*
 *  comparison       -> additive ((T_GT | T_GTE | T_LT | T_LTE) additive)*
 *  additive         -> multiplicative ((T_PLUS | T_MINUS) multiplicative)*
 *  multiplicative   -> unary ((T_MULTIPLY | T_DIVIDE) unary)*
 *  unary            -> (T_INCREMENT | T_DECREMENT) unary
 *                      | primary
 *  primary          -> T_INT
 *                      | T_FLOAT
 *                      | T_STRING
 *                      | T_IDENT
 *                      | T_LPARAN expr T_RPARAN
 *  type             -> T_I8 | T_I16 | T_I32 | T_I64
 *                      | T_U8 | T_U16 | T_U32 | T_U64
 *                      | T_F32 | T_F64
 */

typedef struct {

} Parser;

#endif /* _ICHOR_PARSER_H_ */
