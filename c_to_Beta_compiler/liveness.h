#ifndef LIVENESS_H
#define LIVENESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructions.h"

typedef struct LabelMap {
    char *label_name;
    Instr *target_instr;
    struct LabelMap *next;
} LabelMap;

void build_cfg();
void liveness_analasis();
void liveness();
void resource_allocation();

Instr* find_label_target(LabelMap *head, const char *name);

#endif