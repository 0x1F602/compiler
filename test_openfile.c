#include "minunit.h"
#include "openfile.c"

/* taken from http://www.jera.com/techinfo/jtns/jtn002.html */

int tests_run = 0; 

static char * test_prompt() {
    char * prompt = "Enter 1: ";
    char * entered = prompt_user(prompt);
    char * expected = "1";
    if (entered == NULL) {
        mu_assert("error, prompt was null", 0);
    }
    else {
        mu_assert("error, prompt not equal to '1'", strcmp(entered,expected) == 0);
    }
    return 0;
}

static char * all_tests() {
    mu_run_test(test_prompt);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
