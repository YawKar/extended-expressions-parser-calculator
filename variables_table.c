#include "nodes.h"
#include "misc/string_procedures.h"

int isVariableInTable (VariablesTable* varsTable, char* variableName) {
    for (int i = 0; i < varsTable->variablesNumber; ++i) {
        if (are_equal_strings(varsTable->variablesNames[i], variableName))
            return 1;        
    }
    return 0;
}

void addVariableToTable (VariablesTable* varsTable, VariableNode* varNode) {
    if (isVariableInTable(varsTable, varNode->variableName)) {
        int varIndex = indexOfVariableInTable(varsTable, varNode->variableName);
        varsTable->variablesNodes[varIndex] = varNode;
        return;
    } else {
        char** newVariablesNames = (char**) malloc(sizeof(char*) * (varsTable->variablesNumber + 1));
        VariableNode** newVariablesNodes = (VariableNode**) malloc(sizeof(VariableNode*) * (varsTable->variablesNumber + 1));
        for (int i = 0; i < varsTable->variablesNumber; ++i) {
            newVariablesNames[i] = varsTable->variablesNames[i];
            newVariablesNodes[i] = varsTable->variablesNodes[i];
        }
        newVariablesNames[varsTable->variablesNumber] = varNode->variableName;
        newVariablesNodes[varsTable->variablesNumber] = varNode;
        ++varsTable->variablesNumber;
    }
}
