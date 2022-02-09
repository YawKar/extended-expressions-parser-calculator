#include "VariablesTable.h"
#include "../StringFunctions/StringFunctions.h"
#include <stdlib.h>

VariablesTable* newVariablesTable() {
    VariablesTable* variablesTable = (VariablesTable*)malloc(sizeof(VariablesTable));
    variablesTable->variablesNames = NULL;
    variablesTable->variablesNodes = NULL;
    variablesTable->variablesNumber = 0;
    return variablesTable;
}

int isVariableInTable(VariablesTable* variablesTable, char* variableName) {
    for (int i = 0; i < variablesTable->variablesNumber; ++i) {
        if (areStringsEqual(variablesTable->variablesNames[i], variableName))
            return 1;
    }
    return 0;
}

int indexOfVariableInTable(VariablesTable* variablesTable, char* variableName) {
    for (int i = 0; i < variablesTable->variablesNumber; ++i) {
        if (areStringsEqual(variablesTable->variablesNames[i], variableName))
            return i;
    }
    return -1;
}

void addVariableNameToTable(VariablesTable* variablesTable, char* variableName) {
    if (isVariableInTable(variablesTable, variableName)) {
        // Variable already exists
        return;
    }
    char** newVariablesNames = (char**)malloc(sizeof(char*) * (variablesTable->variablesNumber + 1));
    VariableNode** newVariablesNodes = (VariableNode**)malloc(sizeof(VariableNode*) * (variablesTable->variablesNumber + 1));
    for (int currentIndex = 0; currentIndex < variablesTable->variablesNumber; ++currentIndex) {
        newVariablesNames[currentIndex] = variablesTable->variablesNames[currentIndex];
        newVariablesNodes[currentIndex] = variablesTable->variablesNodes[currentIndex];
    }
    newVariablesNames[variablesTable->variablesNumber] = copyString(variableName);
    newVariablesNodes[variablesTable->variablesNumber] = NULL;
    variablesTable->variablesNames = newVariablesNames;
    variablesTable->variablesNodes = newVariablesNodes;
    ++variablesTable->variablesNumber;
}

void assignNodeForVariableInTable(VariablesTable* variablesTable, char* variableName, VariableNode* variableNode) {
    int variableIndex = indexOfVariableInTable(variablesTable, variableName);
    if (variableIndex == -1) {
        // Doesn't exist
        addVariableNameToTable(variablesTable, variableName);
        variableIndex = indexOfVariableInTable(variablesTable, variableName);
    }
    variablesTable->variablesNodes[variableIndex] = variableNode;
}

VariableNode* getVariableNodeFromTable(VariablesTable* variablesTable, char* variableName) {
    int variableIndex = indexOfVariableInTable(variablesTable, variableName);
    if (variableIndex == -1)
        return NULL;
    return variablesTable->variablesNodes[variableIndex];
}
