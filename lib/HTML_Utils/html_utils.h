#ifndef HTML_UTILS_H
#define HTML_UTILS_H

#include <stdio.h>

void hHTML(FILE* file, int type, char* lexeme);
FILE* beginHTML(char* name);
void closeHTML(FILE* file);
#endif
