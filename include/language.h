#ifndef _ICHOR_LANGUAGE_H_
#define _ICHOR_LANGUAGE_H_

typedef enum {
    T_PLUS,
    T_MINUS,
    T_MULTIPLY,
    T_DIVIDE,
    T_ASSIGN,
    T_LT,
    T_GT,
    T_LPAREN,
    T_RPAREN,
    T_LBRACE,
    T_RBRACE,
    T_SEMI,
    T_IDENT,
    T_EOF,
    T_INT,
    T_FLOAT,
    
    /* keywords */

    // types
    T_I8,
    T_I16,
    T_I32,
    T_I64,
    T_U8,
    T_U16,
    T_U32,
    T_U64,
    T_F32,
    T_F64,

    T_RETURN,
    T_PRINT
} Token;


#endif /* _ICHOR_LANGUAGE_H_ */
