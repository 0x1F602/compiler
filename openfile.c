#include "openfile.h"

/* usage:
 * char * prompt = "Prompt: ";
 * char * entered = prompt_user(prompt);
 * assumes size of entered text is less than 32
 */
char * prompt_user(char * message) {
    printf(message);
    size_t max_size = 32;
    char * input = (char *) malloc(max_size);
    scanf("%31s", input);
    return input;
}

/* usage:
 * handle_no_params();
 */

void handle_no_params(void) {
    char * src_filename = prompt_user(src_prompt);
    if (strlen(src_filename) >= 0) {
        handle_one_params(src_filename);
    }
}

char * check_or_add_extension(char * filename, char * default_extension) {
    char delim[] = "."; // file extension delimiter is a period in most OS...optional on linux, os x
    char * this_token;
    char ** tokens; unsigned short int index = 0;
    this_token = strtok(filename, delim);
    tokens[index] = this_token; 
    while (this_token != NULL) {
        this_token = strtok(NULL, delim);
        index++;
        tokens[index] = this_token;
    }

    if (index < 1) {
        filename = strcat(filename, default_extension);
    }
    return filename;
}

void handle_one_params(char * source) {

}

/* usage:
 * handle_two_params(argv[1], argv[2]);
 */

void handle_two_params(char * source, char * target) {

}
