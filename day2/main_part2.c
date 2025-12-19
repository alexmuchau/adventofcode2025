#include "../tools/methods.c"

long int check_has_sequence(long int number) {
    int size = get_decimals_case(number);
    int half_size = size / 2;

    char * ch_number = malloc(sizeof(char) * size);
    sprintf(ch_number, "%ld", number);

    for (int block_size = half_size; block_size >= 1; block_size--) {
        if (((size + block_size - 1) / block_size) * block_size > size) continue;
        
        // printf("number: %ld, block_size:%d \n", number, block_size);
        char breaked = 'N';
        for (int index = 0; index < size; index += block_size) {
            if (index + (block_size * 2) > size) break;

            char * left_half = strncpy(malloc(sizeof(char) * block_size), ch_number + index, block_size);
            char * right_half = strncpy(malloc(sizeof(char) * block_size), ch_number + index + block_size, block_size);
            
            if (strcmp(left_half, right_half) != 0) {
                // printf("%s == %s: %d\n", left_half, right_half, strcmp(left_half, right_half) == 0);
                breaked = 'Y';
                break;
            }
        }

        if (breaked == 'N') {
            // printf("%ld\n", number);
            return number;
        }
    }

    return 0;
}

long int get_invalids_in_range(long int init_range, long int end_range) {
    long int sum_invalids = 0;
    
    while (init_range <= end_range) {
        sum_invalids += check_has_sequence(init_range);
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