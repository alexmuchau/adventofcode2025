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

    char direction;
    char * row;
    char * char_number;
    int size_number, number;

    char c;
    do
    {
        row = get_row(fptr);
        if (row == NULL) break;
        direction = row[0];
        
        size_number = 0;
        while (row[size_number + 1] != '|') size_number++;
        char_number = malloc(sizeof(char) * size_number);
        strncpy(char_number, row + 1, size_number);
        number = atoi(char_number);

        printf("number:%d, curr:%d, direction:%c\n", number, curr, direction);
        if (number >= 100) {
            count += number / max;
            number %= 100;
        }

        if (direction == 'L') {
            curr -= number;
        } else {
            curr += number;
        }

        if (curr < 0) {
            if (number * -1 != curr) {
                count++;
                printf("Add+1 (negativo), count:%d\n", count);;
            }
            curr = max + curr;
        } else if (curr >= max) {
            curr = curr % 100;
            count++;
            printf("Add+1, count:%d\n", count);
        } else if (curr == 0) {
            count++;
            printf("Add+1, count:%d\n", count);
        }

        printf("%d\n\n", curr);
    } while ((c = fgetc(fptr)) != EOF);

    printf("%d\n", count);
    
    return 0;
}