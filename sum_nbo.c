#include "sum_nbo.h"

uint32_t read_uint32(FILE *file) {
    uint32_t num;
    if (fread(&num, sizeof(uint32_t), 1, file) != 1) {
        fprintf(stderr, "Error: Could not read 4 bytes\n");
        exit(EXIT_FAILURE);
    }
    return ntohl(num);
}

void print_number(uint32_t num, int idx, int total_files) {
    printf("%u(0x%x) ", num, num);
    if (idx < total_files - 1) {
        printf("+ ");
    } else {
        printf("= ");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [<file2>...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    uint32_t total_sum = 0;
    for (int i = 1; i < argc; ++i) {
        FILE *file = fopen(argv[i], "rb");
        if (file == NULL) {
            fprintf(stderr, "Error: Could not open file %s\n", argv[i]);
            return EXIT_FAILURE;
        }

        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        if (fileSize < sizeof(uint32_t)) {
            fprintf(stderr, "Error: File %s is too small to contain a 32-bit integer\n", argv[i]);
            fclose(file);
            return EXIT_FAILURE;
        }

        uint32_t num = read_uint32(file);
        total_sum += num;

        print_number(num, i, argc);

        fclose(file);
    }
    
    printf("%u(0x%x)\n", total_sum, total_sum);
    return EXIT_SUCCESS;
}
