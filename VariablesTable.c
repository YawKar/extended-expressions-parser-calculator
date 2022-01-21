#include "VariablesTable.h"
#include "StringFunctions.h"
#include <stdlib.h>

int isVariableInTable(VariablesTable* varsTable, char* variableName) {
    for (int i = 0; i < varsTable->variablesNumber; ++i) {
        if (areStringsEqual(varsTable->variablesNames[i], variableName))
            return 1;
    }
    return 0;
}

int indexOfVariableInTable(VariablesTable* varsTable, char* variableName) {
    for (int i = 0; i < varsTable->variablesNumber; ++i) {
        if (areStringsEqual(varsTable->variablesNames[i], variableName))
            return i;
    }
    return -1;
}

void addVariableToTable(VariablesTable* varsTable, VariableNode* varNode) {
    if (isVariableInTable(varsTable, varNode->variableName)) {
        int varIndex = indexOfVariableInTable(varsTable, varNode->variableName);
        varsTable->variablesNodes[varIndex] = varNode;
        return;
    }
    else {
        char** newVariablesNames = (char**)malloc(sizeof(char*) * (varsTable->variablesNumber + 1));
        VariableNode** newVariablesNodes = (VariableNode**)malloc(sizeof(VariableNode*) * (varsTable->variablesNumber + 1));
        for (int i = 0; i < varsTable->variablesNumber; ++i) {
            newVariablesNames[i] = varsTable->variablesNames[i];
            newVariablesNodes[i] = varsTable->variablesNodes[i];
        }
        newVariablesNames[varsTable->variablesNumber] = varNode->variableName;
        newVariablesNodes[varsTable->variablesNumber] = varNode;
        ++varsTable->variablesNumber;
    }
}