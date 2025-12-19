#include "../tools/methods.c"

int * get_highers_array(int qt_highers, char * row) {
    int * highers = malloc(sizeof(int) * qt_highers);
    for (int i = 0; i < qt_highers; i++) {
        highers[i] = row[i] - '0';
    }

    return highers;
}

int main() {
    FILE *fptr = fopen("day3/input.txt", "r");
    //FILE *fptr = fopen("day3/example.txt", "r");
    
    long int sum = 0;
    char * row;
    while ((row = get_row(fptr)) != NULL) {
        printf("INIT ROW -> %s.\n", row);
        int * highers = get_highers_array(2, row);

        for (int index = 2; row[index] != '|'; index++) {
            int number = row[index] - '0';
            if (number <= 0) continue;

            if (highers[1] > highers[0]) {
                highers[0] = highers[1];
                highers[1] = number;
                continue;
            }

            if (number > highers[1]) {
                highers[1] = number;
            }
        }
        
        char ch_higher_0 = highers[0] + '0';
        char ch_higher_1 = highers[1] + '0';

        char * ch_higher = malloc(sizeof(char) * 2);
        ch_higher[0] = ch_higher_0;
        ch_higher[1] = ch_higher_1;

        printf("result: %s\n", ch_higher);

        sum += atoi(ch_higher);
    }

    printf("%ld\n", sum);

    return 0;
}