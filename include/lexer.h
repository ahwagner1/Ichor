#ifndef _ICHOR_LEXER_H
#define _ICHOR_LEXER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "language.h"

typedef struct {
    char *value;
    Token token;
} TokenData;

typedef struct {
    size_t token_count;
    size_t line_number;
    char *buffer;
    char *curr_token;
    char *line_start;
    TokenData *tokens;
} Lexer;

static Lexer *init(char *file_name);
static int lex(Lexer *lexer);
static int token_to_int(Token token);
static void add_token(Lexer *lexer, Token type, char *token);
static void handle_identifier(Lexer *lexer);
static void clean(Lexer *lexer);

#endif /* _ICHOR_LEXER_H */
