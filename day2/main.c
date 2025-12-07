#include "../tools/methods.c"

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

long int check_half(long int number) {
    int size = get_decimals_case(number);

    if (size % 2 == 1) return 0;

    char * ch_number = malloc(sizeof(char) * size);
    sprintf(ch_number, "%ld", number);

    int half_size = size / 2;

    char * left_half = strncpy(malloc(sizeof(char) * half_size), ch_number, half_size);
    char * right_half = strncpy(malloc(sizeof(char) * half_size), ch_number + half_size, half_size);

    if (strcmp(left_half, right_half) == 0) return number;
    
    return 0;
}

long int get_invalids_in_range(long int init_range, long int end_range) {
    long int sum_invalids = 0;
    
    while (init_range <= end_range) {
        sum_invalids += check_half(init_range);
        init_range++;
    }

    return sum_invalids;
}

int main() {
    FILE *fptr = fopen("day2/input.txt", "r");
    // FILE *fptr = fopen("day2/example.txt", "r");

    char * row = get_row(fptr);

    int index = 0;
    char * range;
    long int sum_invalids = 0;

    while (row[index] != '\n') {
        while (row[index] != ',' && row[index] != '\n') index++;

        range = malloc(sizeof(char) * index);
        strncpy(range, row, index);
        printf("----------INIT RANGE %s\n", range);

        char * init_range;
        char * end_range;
        int end_size;

        for (int i = 0; i < index; i++) {
            if (range[i] == '-') {
                init_range = malloc(sizeof(char) * i);
                strncpy(init_range, range, i);
                
                range += i + 1;
                end_size = index - i - 1;
                break;
            }
        }

        end_range = malloc(sizeof(char) * end_size);
        strncpy(end_range, range, end_size);

        sum_invalids += get_invalids_in_range(atol(init_range), atol(end_range));

        if (row[index] == ',') row += 1;
        row += index;
        index = 0;
    }

    printf("\nfinal sum: %ld\n", sum_invalids);

    return 0;
}