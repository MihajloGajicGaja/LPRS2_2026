#include "liveness.h"
#include "munch.h"

void build_cfg(){
    LabelMap *map_head = NULL;
    Instr *curr = instrList_head;

    // find labels
    while (curr != NULL) {
        if(curr->Op == JMP && curr->rb != NULL && !strcmp(curr->rb, "LABEL")){
            Instr *target = curr->next;
            while(target != NULL && target->Op == JMP && target->rb != NULL && !strcmp(target->rb, "LABEL")) {
                target = target->next;
            }

            LabelMap *new_entry = malloc(sizeof(LabelMap));
            new_entry->label_name = curr->ra; 
            new_entry->target_instr = target;
            new_entry->next = map_head;
            map_head = new_entry;
        }
        curr = curr->next;
    }

    // find succ instr, of every instr
    curr = instrList_head;
    while (curr != NULL) {
        curr->succ1 = NULL;
        curr->succ2 = NULL;

        // label markers
        if((curr->Op == JMP && curr->rb != NULL && !strcmp(curr->rb, "LABEL")) ||
            (curr->Op == ST && curr->rb != NULL && !strcmp(curr->rb, "GLOBAL_DECL"))){
            curr = curr->next;
            continue;
        }

        // no condition jump
        if(curr->Op == JMP && curr->ra != NULL && !strcmp(curr->ra, "r31")){
            curr->succ1 = find_label_target(map_head, curr->rc);
        }
        // End of function LP
        else if(curr->Op == JMP && curr->ra != NULL && !strcmp(curr->ra, "lp")){
            curr->succ1 = NULL;
        }
        // conditional jump, only instruction with two succ
        else if(curr->Op == BEQ){
            Instr *next_real = curr->next;
            while(next_real != NULL && next_real->Op == JMP && next_real->rb != NULL && !strcmp(next_real->rb, "LABEL")){
                next_real = next_real->next;
            }
            curr->succ1 = next_real;
            curr->succ2 = find_label_target(map_head, curr->rb);
        }
        // default instr
        else{
            Instr *next_real = curr->next;
            while(next_real != NULL && next_real->Op == JMP && next_real->rb != NULL && !strcmp(next_real->rb, "LABEL")){
                next_real = next_real->next;
            }
            curr->succ1 = next_real;
        }
        curr = curr->next;
    }

    LabelMap *tmp;
    while (map_head) {
        tmp = map_head->next;
        free(map_head);
        map_head = tmp;
    }
}

void liveness_analasis(){

}

void resource_allocation(){

}

void liveness(){
    if(!instrList_head) return;

    build_cfg();
    liveness_analasis();
    resource_allocation();

}



Instr* find_label_target(LabelMap *head, const char *name){
    LabelMap *curr = head;
    while (curr) {
        if (strcmp(curr->label_name, name) == 0) {
            return curr->target_instr;
        }
        curr = curr->next;
    }
    return NULL;
}