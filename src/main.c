#include "../include/lexer.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Too few arguments. Try again\n");
        return 1;
    }

    Lexer *lexer = init(argv[1]);
    int result = lex(lexer);
    
    if (result == 0)
        printf("Lexing completed successfully\n");
    else
        printf("Something failed when lexing\n");

    print_tokens(lexer);

    clean(lexer);

    return 0;
}
