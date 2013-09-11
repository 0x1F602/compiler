#include "headers/openfile.h"
#include "headers/scanner.h"

void scanner(openfile_data * of_d_ptr) {
    openfile_data of_d = *of_d_ptr;
    FILE * in = of_d.input;
    FILE * listing_file = of_d.listing_file;
    token t;
    scanner_data s;
    scanner_data * s_p = &s;
    // priming the loop
    s.line_buffer[0] = '\0';
    s.token_buffer[0] = '\0';
    while (fgets(s.line_buffer, MAX_SIZE, in) != NULL) {
        t = match_code_to_token(s_p);
        //format from token and print to temp file
        //watch out for accidentally setting feof on this in there
        if (feof(in)) {
            break;
        }
    }
    return;
}

token match_code_to_token(scanner_data * s_p) {
    token t;
    // while we still have characters..
        // if starts with symbol, go there..
        // if starts with alpha..
        // if starts with int..
    return t;
}
