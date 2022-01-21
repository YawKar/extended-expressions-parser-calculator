#ifndef _VARIABLES_TABLE_HEADER
#define _VARIABLES_TABLE_HEADER
#include "VariableNode.h"

typedef struct VariablesTable VariablesTable;
struct VariablesTable {
    char** variablesNames;
    int variablesNumber;
    VariableNode** variablesNodes;
};

int isVariableInTable(VariablesTable* varsTable, char* variableName);
void addVariableToTable(VariablesTable* varsTable, VariableNode* varNode);
int indexOfVariableInTable(VariablesTable* varsTable, char* variableName);
#endif