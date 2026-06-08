#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

extern int yyparse(void);
extern FILE *yyin;

extern ASTNode *root;

void ast_print(ASTNode *node, int indent);

void ast_free(ASTNode *node);

int main(int argc, char **argv)
{
    FILE *input;

    if (argc > 1) {
        input = fopen(argv[1], "r");

        if (!input) {
            fprintf(stderr, "Cannot open file %s\n", argv[1]);
            return 1;
        }

        yyin = input;
    }

    if (yyparse() == 0) {
        if (root)
            ast_print(root, 0);
        else
            printf("Empty program\n");

        ast_free(root);
    } else {
        fprintf(stderr, "Parsing failed\n");
    }

    return 0;
}
