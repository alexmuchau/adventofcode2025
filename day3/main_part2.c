#include "../tools/methods.c"

int convert_char_to_int(char to_convert) {
    int new = to_convert - '0';
    return new;
}

char * get_highers_array(int qt_highers, char * row, int last_idx) {
    char * highers = malloc(sizeof(int) * qt_highers);
    memcpy(highers, row + (last_idx - qt_highers), qt_highers);

    return highers;
}

char * swap_higher(char * highers, int number, int qt_highers, int swap_idx) {
    if (highers[swap_idx] - '0' == number) return highers;

    char * new_highers = malloc(sizeof(char) * qt_highers);
    new_highers[0] = number + '0';

    int last_half_size = (qt_highers - 1) - swap_idx;
    int first_half_size = (qt_highers - 1) - last_half_size;

    // printf("first: %d - last: %d\n", first_half_size, last_half_size);
    if (first_half_size > 0) {
        strncpy(new_highers + 1, highers, first_half_size);
        // printf("first_half: %d - %s\n", first_half_size, new_highers);
    }

    if (last_half_size > 0) {
        strncpy(new_highers + 1 + first_half_size, highers + (swap_idx + 1), last_half_size);
        // printf("last_half: %d - %s\n", last_half_size, new_highers);
    }

    return new_highers;
}

int get_lowest_digit(char * highers, int qt_highers) {
    int lowest_idx = 0;
    for (int i = 1; i < qt_highers; i++)
        if (highers[i] < highers[lowest_idx]) lowest_idx = i;
    
    return lowest_idx;
}

int main() {
    // FILE *fptr = fopen("day3/input.txt", "r");
    FILE *fptr = fopen("day3/example.txt", "r");
    
    int qt_highers = 12;
    long int sum = 0;
    char * row;
    while ((row = get_row(fptr)) != NULL) {
        long unsigned int last_idx = strlen(row);
        printf("INIT ROW -> %s. Row size: %zu\n", row, last_idx);
        
        char * highers = get_highers_array(qt_highers, row, last_idx);
        int lowest_number_idx = get_lowest_digit(highers, qt_highers);
        
        for (int index = last_idx - qt_highers - 1; index >= 0; index--) {
            // printf("HIGHERS: %s, lowest: %d\n", highers, lowest_number_idx);
            int number = convert_char_to_int(row[index]);
            // printf("--------\nInit number: %d\n", number);
            if (number < 1) continue;
            
            char * new_highers = swap_higher(highers, number, qt_highers, lowest_number_idx);
            if (atol(new_highers) > atol(highers)) {
                // printf("%ld > %ld = true\n", atol(new_highers), atol(highers));
                highers = new_highers;
                lowest_number_idx = get_lowest_digit(highers, qt_highers);
            }
            // printf("--------\n");
        }
        
        printf("result: %s\n", highers);
        sum += atol(highers);
    }

    printf("%ld\n", sum);

    return 0;
}
