#include <stdio.h>
#include <stdlib.h>
#include "InputFunctions.h"

char* getLine() {
    char* line = (char*)malloc(100);
    char* linep = line;
    size_t lenmax = 100;
    size_t len = lenmax;
    int ch;
    if (line == NULL)
        return NULL;
    for (;;) {
        ch = fgetc(stdin);
        if (ch == EOF)
            break;
        if (--len == 0) {
            len = lenmax;
            char* linen = (char*)realloc(linep, lenmax *= 2);
            if (linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }
        if ((*line++ = ch) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}