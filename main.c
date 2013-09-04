#include "openfile.h"
#include <stdio.h>
int main(int argc, char * argv[]) {
	printf("\nUsage: %s [input_file [output_file]]\n", argv[0]);
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
