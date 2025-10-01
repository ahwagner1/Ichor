// Copyright 2025 Ashton Wagner
// SPDX-License-Identifier: Apache-2.0

#include "../include/lexer.h"

Lexer *init(char *file_name) {
    FILE *file_ptr = fopen(file_name, "r");
    if (!file_ptr) {
        perror("Error opening file");
        exit(1);
    }

    // getting the file size
    fseek(file_ptr, 0, SEEK_END);
    uint64_t size = ftell(file_ptr);
    rewind(file_ptr);

    Lexer *lexer = (Lexer*)malloc(sizeof(Lexer));
    lexer->capacity = INIT_TOKEN_CAPACITY;
    lexer->tokens = (TokenData*)malloc(sizeof(TokenData) * INIT_TOKEN_CAPACITY);
    lexer->buffer = (char*)malloc(size + 1);
    lexer->curr_token = lexer->buffer;
    lexer->line_start = lexer->buffer;
    if (!lexer->buffer || !lexer->tokens || !lexer) {
        perror("Error allocating memory");
        fclose(file_ptr);
        exit(1);
    }   

    fread(lexer->buffer, 1, size, file_ptr);
    lexer->buffer[size] = '\0';
    fclose(file_ptr);

    lexer->token_count = 0;
    lexer->line_number = 0;

    return lexer;
}

/*
    TODO
    Clean up how how the token incrementing happens
    Some branches use continue and some dont, make consistent
*/
int lex(Lexer *lexer) {
    while (*lexer->curr_token != '\0') {
        switch (*lexer->curr_token) {
            case ' ':
                break;
            case '\t':
                break;
            case '\n':
                lexer->line_number++;
                lexer->line_start = lexer->curr_token + 1;
                break;
            case '+':
                if (*(lexer->curr_token + 1) == '+') {
                    add_token(lexer, T_INCREMENT, lexer->curr_token, lexer->curr_token + 2);
                    lexer->curr_token++;
                }
                else
                    add_token(lexer, T_PLUS, lexer->curr_token, lexer->curr_token + 1);
                break;
            case '-':
                add_token(lexer, T_MINUS, lexer->curr_token, lexer->curr_token + 1);
                break;
            case '*':
                add_token(lexer, T_MULTIPLY, lexer->curr_token, lexer->curr_token + 1);
                break;
            case '/':
                // only single line comments for now
                if (*(lexer->curr_token + 1) == '/') {
                    lexer->curr_token += 2;
                    while (*lexer->curr_token != '\n' && *lexer->curr_token != '\0')
                        lexer->curr_token++;

                    continue;
                }
                else
                    add_token(lexer, T_DIVIDE, lexer->curr_token, lexer->curr_token + 1);
                break;
            case '=':
                if (*(lexer->curr_token + 1) == '=') {
                    add_token(lexer, T_EQUALS, lexer->curr_token, lexer->curr_token + 2);
                    lexer->curr_token++;
                }
                else
                    add_token(lexer, T_ASSIGN, lexer->curr_token, lexer->curr_token + 1);
                break;
            case '<':
                if (*(lexer->curr_token + 1) == '=') {
                    add_token(lexer, T_LTE, lexer->curr_token, lexer->curr_token + 2);
                    lexer->curr_token++;
                }
                else
                    add_token(lexer, T_LT, lexer->curr_token, lexer->curr_token + 1);
                break;
            case '>':
                if (*(lexer->curr_token + 1) == '=') {
                    add_token(lexer, T_GTE, lexer->curr_token, lexer->curr_token + 2);
                    lexer->curr_token++;
                }
                else
                    add_token(lexer, T_GT, lexer->curr_token, lexer->curr_token + 1);
                break;
            case '(':
                add_token(lexer, T_LPAREN, lexer->curr_token, lexer->curr_token + 1);
                break;
            case ')':
                add_token(lexer, T_RPAREN, lexer->curr_token, lexer->curr_token + 1);
                break;
            case '{':
                add_token(lexer, T_LBRACE, lexer->curr_token, lexer->curr_token + 1);
                break;
            case '}':
                add_token(lexer, T_RBRACE, lexer->curr_token, lexer->curr_token + 1 );
                break;
            case '[':
                add_token(lexer, T_LBRACKET, lexer->curr_token, lexer->curr_token + 1);
                break;
            case ']':
                add_token(lexer, T_RBRACKET, lexer->curr_token, lexer->curr_token + 1);
                break;
            case ';':
                add_token(lexer, T_SEMI, lexer->curr_token, lexer->curr_token + 1);
                break;
            case ':':
                add_token(lexer, T_COLON, lexer->curr_token, lexer->curr_token + 1);
                break;
            case '&':
                // might move this to a waterfall approach eventually
                if (*(lexer->curr_token + 1) == '&') { 
                    add_token(lexer, T_AND, lexer->curr_token, lexer->curr_token + 2);
                    lexer->curr_token++;
                }
                else
                    add_token(lexer, T_BITWISE_AND, lexer->curr_token, lexer->curr_token + 1);
                break;
            case '|':
                if (*(lexer->curr_token + 1) == '|') {
                    add_token(lexer, T_OR, lexer->curr_token, lexer->curr_token + 2);
                    lexer->curr_token++;
                }
                else
                    add_token(lexer, T_BITWISE_OR, lexer->curr_token, lexer->curr_token + 1);
                break;
            case '^':
                add_token(lexer, T_XOR, lexer->curr_token, lexer->curr_token + 1);
                break;
            default:
                if (*lexer->curr_token == '"') {
                    lexer->curr_token++;

                    char *start = lexer->curr_token;
                    while (*lexer->curr_token != '"' && *lexer->curr_token != '\0')
                        lexer->curr_token++;

                    if (*lexer->curr_token == '\0') {
                        printf("Unterminated string\n");
                        exit(1);
                    }
                    
                    add_token(lexer, T_STRING, start, lexer->curr_token);

                }
                else if (isdigit(*lexer->curr_token)) {
                    char *start = lexer->curr_token;

                    while (isdigit(*lexer->curr_token))
                        lexer->curr_token++;

                    uint8_t is_float = 0;
                    if (*lexer->curr_token == '.') {
                        is_float = 1;
                        lexer->curr_token++;
                        
                        // keep grabbing the mantissa portion
                        while (isdigit(*lexer->curr_token))
                            lexer->curr_token++;
                    }

                    add_token(lexer, is_float == 0 ? T_INT : T_FLOAT, start, lexer->curr_token);
                    continue;
                }
                else if (isalpha(*lexer->curr_token)) {
                    handle_identifier(lexer);
                    continue;
                }
                else {
                    printf("Unknow token: %c\n", *lexer->curr_token);
                    exit(1);
                }
                break;
        }
        lexer->curr_token++;
    }

    add_token(lexer, T_EOF, NULL, NULL);
    return 0;
}

char *extract_token(char *start, char *end) {
    if (start == NULL || end == NULL)
        return NULL;

    uint32_t str_len = end - start;
    char *text = (char*)malloc(str_len + 1);

    strncpy(text, start, str_len);
    text[str_len] = '\0';

    return text;
}

void add_token(Lexer *lexer, Token type, char *start, char* end) {
    check_token_capacity(lexer);
    lexer->tokens[lexer->token_count].token = type;
    lexer->tokens[lexer->token_count].value = extract_token(start, end);
    lexer->tokens[lexer->token_count].span  = end - start;
    lexer->tokens[lexer->token_count].line_number = lexer->line_number;
    lexer->tokens[lexer->token_count].start_index = start - lexer->line_start;

    lexer->token_count++;
}

void handle_identifier(Lexer *lexer) {
    // need to parse the "identifier" and then check if its a keyword
    char *start = lexer->curr_token;
    while (isalnum(*lexer->curr_token) || *lexer->curr_token == '_')
        lexer->curr_token++;

    // sort ugly since extract_token does this already but can refactor later lol
    uint32_t str_len = lexer->curr_token - start;
    char *identifier = (char*)malloc(str_len + 1);
    
    strncpy(identifier, start, str_len);
    identifier[str_len] = '\0';

    if (strcmp(identifier, "i8") == 0) {
        add_token(lexer, T_I8, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "i16") == 0) {
        add_token(lexer, T_I16, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "i32") == 0) {
        add_token(lexer, T_I32, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "i64") == 0) {
        add_token(lexer, T_I64, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "u8") == 0) {
        add_token(lexer, T_U8, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "u16") == 0) {
        add_token(lexer, T_U16, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "u32") == 0) {
        add_token(lexer, T_U32, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "u64") == 0) {
        add_token(lexer, T_U64, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "f32") == 0) {
        add_token(lexer, T_F32, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "f64") == 0) {
        add_token(lexer, T_F64, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "return") == 0) {
        add_token(lexer, T_RETURN, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "print") == 0) {
        add_token(lexer, T_PRINT, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "register") == 0) {
        add_token(lexer, T_REGISTER, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "for") == 0) {
        add_token(lexer, T_FOR, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "while") == 0) {
        add_token(lexer, T_WHILE, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "if") == 0) {
        add_token(lexer, T_IF, start, lexer->curr_token);
    }
    else if (strcmp(identifier, "else") == 0) {
        add_token(lexer, T_ELSE, start, lexer->curr_token);
    }
    else {
        // variable/function names
        add_token(lexer, T_IDENT, start, lexer->curr_token);
    }

    free(identifier);
}

void print_tokens(Lexer *lexer) {
    for (size_t i = 0; i < lexer->token_count; ++i) {
        printf("Token: %s, type: %d, line number: %d, start index: %d, span: %d\n", 
            lexer->tokens[i].value,
            lexer->tokens[i].token,
            lexer->tokens[i].line_number,
            lexer->tokens[i].start_index,
            lexer->tokens[i].span
        );
    }
}

void check_token_capacity(Lexer *lexer) {
    if (lexer->token_count >= lexer->capacity) {
        lexer->capacity *= 2;
        lexer->tokens = (TokenData*)realloc(lexer->tokens, sizeof(TokenData) * lexer->capacity);

        if (!lexer->tokens) {
            perror("Failed to realloc memory\n");
            exit(1);
        }
    }
}

void clean(Lexer *lexer) {
    if (lexer->buffer) {
        free(lexer->buffer);
    }

    for (size_t i = 0; i < lexer->token_count; ++i) {
        if (lexer->tokens[i].value)
            free(lexer->tokens[i].value);
    }

    if (lexer->tokens)
        free(lexer->tokens);

    free(lexer);
}
