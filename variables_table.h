#ifndef VARIABLES_TABLE_REALISATION
#define VARIABLES_TABLE_REALISATION
#include "nodes.h"
#include "misc/string_procedures.h"

typedef struct VariablesTable VariablesTable;
struct VariablesTable {
    char** variablesNames;
    int variablesNumber;
    VariableNode** variablesNodes;
};

int isVariableInTable (VariablesTable* varsTable, char* variableName);
void addVariableToTable (VariablesTable* varsTable, VariableNode* varNode);
#endif
