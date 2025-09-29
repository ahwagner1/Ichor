#ifndef _ICHOR_LEXER_H
#define _ICHOR_LEXER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "language.h"

#define INIT_TOKEN_CAPACITY 256

typedef struct {
    char *value;
    Token token;
} TokenData;

typedef struct {
    size_t token_count;
    size_t line_number;
    size_t capacity;
    char *buffer;
    char *curr_token;
    char *line_start;
    TokenData *tokens;
} Lexer;

Lexer *init(char *file_name);
int lex(Lexer *lexer);
int token_to_int(Token token);
char* extract_token(char *start, char *end);
void add_token(Lexer *lexer, Token type, char *start, char *end);
void handle_identifier(Lexer *lexer);
void print_tokens(Lexer *lexer);
void check_token_capacity(Lexer *lexer);
void clean(Lexer *lexer);

#endif /* _ICHOR_LEXER_H */
