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

}

/* usage:
 * handle_one_params(argv[1]);
 */

void handle_one_params(char * source) {

}

/* usage:
 * handle_two_params(argv[1], argv[2]);
 */

void handle_two_params(char * source, char * target) {

}
