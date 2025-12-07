#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
    FILE *fptr = fopen("day1/input.txt", "r");
    int curr = 50;
    int max = 100;
    int count = 0;

    char c;
    do
    {
        char * row = get_row(fptr);
        if (row == NULL) break;
        char direction = row[0];
        
        int size_number = 0;
        while (row[size_number + 1] != '|') size_number++;
        char * char_number = malloc(sizeof(char) * size_number);
        strncpy(char_number, row + 1, size_number);
        int number = atoi(char_number);

        if (number > 100) number %= 100;

        printf("number:%d, curr:%d, direction:%c\n", number, curr, direction);
        if (direction == 'L') {
            curr -= number;
        } else {
            curr += number;
        }

        if (curr < 0) {
            curr = max + curr;
        }

        if (curr >= max) {
            curr = curr % 100;
        }

        printf("%d\n", curr);

        if (curr == 0) count++;
    } while ((c = fgetc(fptr)) != EOF);

    printf("%d\n", count);
    
    return 0;
}