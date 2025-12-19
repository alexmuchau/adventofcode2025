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
    fgetc(fptr);
    return text;
}

int get_decimals_case(long int number) {
    int count = 0;

    if (number == 0) {
        count = 1;
    } else {
        if (number < 0) {
            number = -number;
        }

        while (number > 0) {
            number /= 10;
            count++;
        }
    }

    return count;
}

#endif