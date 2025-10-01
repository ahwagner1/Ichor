// Copyright 2025 Ashton Wagner
// SPDX-License-Identifier: Apache-2.0

#ifndef _ICHOR_LANGUAGE_H_
#define _ICHOR_LANGUAGE_H_

typedef enum {
    T_PLUS,
    T_MINUS,
    T_MULTIPLY,
    T_DIVIDE,
    T_ASSIGN,
    T_LT,
    T_LTE,
    T_GT,
    T_GTE,
    T_EQUALS,
    T_LPAREN,
    T_RPAREN,
    T_LBRACE,
    T_RBRACE,
    T_LBRACKET,
    T_RBRACKET,
    T_SEMI,
    T_COLON,
    T_IDENT,
    T_EOF,
    T_INT, // actual integers
    T_FLOAT, // actual floats
    T_AND,
    T_OR,
    T_INCREMENT,
    T_DECREMENT,
    T_BITWISE_AND,
    T_BITWISE_OR,
    T_XOR,
    
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
    T_STRING,
    T_REGISTER,

    T_RETURN,
    T_PRINT,

    // control flow
    T_FOR,
    T_WHILE,
    T_IF, 
    T_ELSE
} Token;


#endif /* _ICHOR_LANGUAGE_H_ */
