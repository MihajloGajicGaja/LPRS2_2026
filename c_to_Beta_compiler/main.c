#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "munch.h"
#include "instructions.h"
#include "liveness.h"

extern int yyparse(void);
extern FILE *yyin;
extern ASTNode *root;

Instr *instrList_head = NULL;
Instr *instrList_tail = NULL;

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
    }else{
        printf("Insuficent arguments!\n");
        return 1;
    }

    if (yyparse() == 0){
        if (root){
            printf("===================AST=====================\n");
            ast_print(root, 0);
            printf("\n\n\n");

            printf("===================MUNCHIN'=====================\n");
            munch_stmt(root);

            printf("===================LIVENESS=====================\n");
            liveness();
            print_instructionList(instrList_head);

            if(instrList_head != NULL){
                free_InstrList(instrList_head);
            }
        }
        else
            printf("Empty program\n");

        ast_free(root);
        fclose(input);
    } else {
        fprintf(stderr, "Parsing failed\n");
    }

    return 0;
}
