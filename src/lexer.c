#include "../include/lexer.h"

static Lexer *init(char *file_name) {
    FILE *file_ptr = fopen(file_name, "r");
    if (!file_ptr) {
        perror("Error opening file");
        exit(1);
    }

    // getting the file size
    fseek(file_ptr, 0, SEEK_END);
    uint64_t size = ftell(file_ptr);
    rewind(file_ptr);

    Lexer *lexer = (Lexer)malloc(sizeof(Lexer);
    lexer->buffer = (char*)malloc(size + 1);
    lexer->curr_token = lexer->buffer;
    lexer->line_start = lexer->buffer;
    if (!lexer->buffer) {
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

static int lex(Lexer *lexer) {
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
                add_token(lexer, T_PLUS, '+');
                break;
            case '-':
                add_token(lexer, T_MINUS, '-');
                break;
            case '*':
                add_token(lexer, T_MULTIPLY, '*');
                break;
            case '/':
                add_token(lexer, T_DIVIDE, '/');
                break;
            case '=':
                add_token(lexer, T_ASSIGN, '=');
                break;
            case '<':
                add_token(lexer, T_LT, '<');
                break;
            case '>':
                add_token(lexer, T_GT, '>');
                break;
            case '(':
                add_token(lexer, T_LPAREN, '(');
                break;
            case ')':
                add_token(lexer, T_RPAREN, ')');
                break;
            case '{':
                add_token(lexer, T_LBRACE, '{');
                break;
            case '}':
                add_token(lexer, T_RBRACE, '}');
                break;
            case ';':
                add_token(lexer, T_SEMI, ';');
                break;
            default:
                if (*lexer->curr_token == '"') {
                    // handle strings TODO
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
                    
                    uint32_t str_len = lexer->curr_token - start;
                    char *number = (char*)malloc(str_len + 1);

                    strncpy(number, start, str_len);
                    number[str_len] = '\0';

                    add_token(lexer, is_float == 0 ? T_INT : T_FLOAT, number);
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

    add_token(lexer, T_EOF, NULL);
    return 0;
}

static void add_token(Lexer *lexer, Token type, char *token) {
    lexer->tokens[lexer->token_count].token = type;
    lexer->tokens[lexer->token_count].value = token;

    lexer->curr_token++;
    lexer->token_count++;
}

static void handle_identifier(Lexer *lexer) {
    // need to parse the "identifier" and then check if its a keyword
    char *start = lexer->curr_token;
    while (isalnum(*lexer->curr_token) || *lexer->curr_token == '_')
        lexer->curr_token++;

    uint32_t str_len = lexer->curr_token - start;
    char *identifier = (char*)malloc(str_len + 1);
    
    strncpy(identifier, start, str_len);
    identifier[str_len] = '\0';

    if (strcmp(identifier, "i8") == 0) {
        add_token(lexer, T_I8, identifier);
    }
    else if (strcmp(identifier, "i16") == 0) {
        add_token(lexer, T_I16, identifier);
    }
    else if (strcmp(identifier, "i32") == 0) {
        add_token(lexer, T_I32, identifier);
    }
    else if (strcmp(identifier, "i64") == 0) {
        add_token(lexer, T_I64, identifier);
    }
    else if (strcmp(identifier, "u8") == 0) {
        add_token(lexer, T_U8, identifier);
    }
    else if (strcmp(identifier, "u16") == 0) {
        add_token(lexer, T_U16, identifier);
    }
    else if (strcmp(identifier, "u32") == 0) {
        add_token(lexer, T_U32, identifier);
    }
    else if (strcmp(identifier, "u64") == 0) {
        add_token(lexer, T_U64, identifier);
    }
    else if (strcmp(identifier, "f32") == 0) {
        add_token(lexer, T_F32, identifier);
    }
    else if (strcmp(identifier, "f64") == 0) {
        add_token(lexer, T_F64, identifier);
    }
    else if (strcmp(identifier, "return") == 0) {
        add_token(lexer, T_RETURN, identifier);
    }
    else if (strcmp(identifier, "print") == 0) {
        add_token(lexer, T_PRINT, identifier);
    }
    else {
        // variable/function names
        add_token(lexer, T_IDENT, identifier);
    }
}
