#ifndef _VARIABLES_TABLE_HEADER
#define _VARIABLES_TABLE_HEADER
#include "../Nodes/VariableNode/VariableNode.h"

typedef struct VariablesTable VariablesTable;
struct VariablesTable {
    char** variablesNames;
    int variablesNumber;
    VariableNode** variablesNodes;
};

VariablesTable* newVariablesTable();
VariableNode* getVariableNodeFromTable(VariablesTable* variablesTable, char* variableName);
int isVariableInTable(VariablesTable* variablesTable, char* variableName);
void addVariableNameToTable(VariablesTable* variablesTable, char* variableName);
void assignNodeForVariableInTable(VariablesTable* variablesTable, char* variableName, VariableNode* variableNode);
int indexOfVariableInTable(VariablesTable* variablesTable, char* variableName);
#endif
