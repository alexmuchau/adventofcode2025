#ifndef MOV_M_H
#define MOV_M_H

#include "methods.h"

char * get_row(FILE *fptr) {
    fpos_t old_pos;
    fgetpos(fptr, &old_pos);

    char c;
    int size = 1;
    while ((c = fgetc(fptr)) != '\n' && c != EOF) size++;
    if (c == EOF) return NULL;
    char * text = malloc(sizeof(char) * size + 1);

    fsetpos(fptr, &old_pos);
    fgets(text, size, fptr);

    text[size + 1] = '|';

    return text;
}

#endif