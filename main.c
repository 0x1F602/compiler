#include <stdio.h>
#include "headers/openfile.h"
/* G4P1
 * Patrik Natali
 * Ian Wlodarczyk
 * Mike Hetzel
 *
 *     ________                               _____  
 *    /  _____/______  ____  __ ________     /  |  | 
 *   /   \  __\_  __ \/  _ \|  |  \____ \   /   |  |_
 *   \    \_\  \  | \(  <_> )  |  /  |_> > /    ^   /
 *    \______  /__|   \____/|____/|   __/  \____   | 
 *           \/                   |__|          |__| 
 */

openfile_data setup(int argc, char * argv[]) {
    openfile_data ofd;
	printf("\nUsage: %s [input_file [output_file]]\n", argv[0]);
    switch (argc) {
        case 3:
            ofd = handle_two_params(argv[1], argv[2]);
        break;
        case 2:
            ofd = handle_one_params(argv[1]);
        break;
        case 1:
        default:
            ofd = handle_no_params();
    }
    return ofd;
}

void calculate(openfile_data of_d) {
    openfile_data * of_d_ptr = &of_d;
    scanner(of_d_ptr);
}

void teardown(openfile_data of_d) {
    fclose(of_d.input);
    fclose(of_d.output);
    fclose(of_d.temp1);
    fclose(of_d.listing_file);
}

int main(int argc, char * argv[]) {
    openfile_data of_d = setup(argc, argv);
    calculate(of_d);
    teardown(of_d);
    return 0;
}
