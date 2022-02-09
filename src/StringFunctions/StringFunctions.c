#include <string.h>
#include <stdlib.h>
#include "StringFunctions.h"

char* removeCharCopy(char* origString, char rmChar) {
    int copyLength = 0;
    int origLength = strlen(origString);
    for (int i = 0; i < origLength; ++i) {
        if (origString[i] != rmChar)
            ++copyLength;
    }
    if (copyLength == 0)
        return (char*)NULL;
    char* new_str = (char*)malloc(sizeof(char) * (copyLength + 1));
    char* iter = new_str;
    for (int i = 0; i < origLength; ++i) {
        if (origString[i] != rmChar)
            *iter = origString[i], ++iter;
    }
    *iter = '\0';
    return new_str;
}

int areStringsEqual(char* string1, char* string2) {
    int string1Len = strlen(string1);
    int string2Len = strlen(string2);
    if (string1Len != string2Len)
        return 0;
    for (int i = 0; i < string1Len; ++i) {
        if (string1[i] != string2[i])
            return 0;
    }
    return 1;
}

char* copyString(char* origString) {
    int origStringLength = strlen(origString);
    char* copiedString = (char*)malloc(sizeof(char) * (origStringLength + 1));
    for (int i = 0; i < origStringLength; ++i) {
        copiedString[i] = origString[i];
    }
    copiedString[origStringLength] = '\0';
    return copiedString;
}