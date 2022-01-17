#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "string_procedures.h"

char* remove_char (char* orig, char rm_char) {
    int final_length = 0;
    int orig_length = strlen(orig);
    for (int i = 0; i < orig_length; ++i) {
        if (orig[i] != rm_char)
            ++final_length;
    }
    if (final_length == 0)
        return (char*) NULL;
    char* new_str = (char*) malloc(sizeof(char) * (final_length + 1));
    char* iter = new_str;
    for (int i = 0; i < orig_length; ++i) {
        if (orig[i] != rm_char)
            *iter = orig[i], ++iter;
    }
    *iter = '\0';
    return new_str;
}

int are_equal_strings (char* str1, char* str2) {
    int str1len = strlen(str1);
    int str2len = strlen(str2);
    if (str1len != str2len)
        return 0;
    for (int i = 0; i < str1len; ++i) {
        if (str1[i] != str2[i])
            return 0;
    }
    return 1;
}

