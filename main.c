#include "openfile.c"

int main(int argc, char * argv[]) {
    printf("Usage: %s [input_file [output_file]]", argv[0]);
    switch (argc) {
        case 3:
            handle_two_params(argv[1], argv[2]);
        break;
        case 2:
            handle_one_params(argv[1]);
        break;
        case 1:
        default:
            handle_no_params();
    }
    return 0;
}
