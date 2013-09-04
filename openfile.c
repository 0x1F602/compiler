#include "openfile.h"
#include <string.h>

/* usage:
 * char * prompt = "Prompt: ";
 * char * entered = prompt_user(prompt);
 * assumes size of entered text is less than 32
 */

#define max_size 32
#define max_tokens 5

char * prompt_user(const char * message) {
    printf(message);
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

tokened_string tokenize(char * string) {
    char * this_token;
    char delim[] = "."; // file extension delimiter is a period in most OS...optional on linux, os x
    char ** tokens = (char **) malloc(max_size * max_tokens); unsigned short int index = 0;
    this_token = strtok(string, delim);
    tokens[index] = this_token; 
    this_token = strtok(NULL, delim);
    while (this_token != NULL) {
        index++;
        tokens[index] = this_token;
        this_token = strtok(NULL, delim);
    }
    char * extension = "";
    if (index >= 1) {
        extension = tokens[index];
    }
    tokened_string ts;
    ts.tokens = tokens;
    ts.index = index;
    return ts;
}

char * find_extension(char * filename) {
    tokened_string ts = tokenize(filename);
    char * extension = NULL;

    if (ts.index > 0) {
        extension = ts.tokens[ts.index];
    }
    
    return extension;
}

char * check_or_add_extension(char * filename, char * default_extension) {
    char * orig_filename = (char *) malloc(32);
    orig_filename = strcpy(orig_filename, filename);
    char * extension = find_extension(filename);
    //printf("Found extension from %s: %s\n", filename, extension);
    if (extension == NULL) {
        strcat(filename, default_extension);
    }
    else {
        //printf("%s %s\n\n", filename, extension);
        sprintf(filename, "%s.%s", filename, extension);
    }
    //printf("Filename: %s\n", filename);
    return filename;
}

char * generate_filename(char * source) {
    tokened_string ts = tokenize(source);
    char * source_filename_body = ts.tokens[0];
    if (ts.index > 1) {
        int i = 0;
        while (i < ts.index) {
            strcat(source_filename_body, ts.tokens[i]);
            i++;
        }
    }
    else {
        strcat(source_filename_body, OUTPUT_EXTENSION);
    }

    return source_filename_body;
}

void handle_one_params(char * source) {
    source = check_or_add_extension(source, INPUT_EXTENSION);
    char * target = prompt_user(tar_prompt);
    if (strlen(target) <= 0) {
        target = generate_filename(source);
    }
    target = check_or_add_extension(target, OUTPUT_EXTENSION);
    handle_two_params(source, target);
}

/* usage:
 * handle_two_params(argv[1], argv[2]);
 */

void handle_two_params(char * source, char * target) {
    source = check_or_add_extension(source, INPUT_EXTENSION);
    target = check_or_add_extension(target, OUTPUT_EXTENSION);
    printf("Source: %s, Target: %s\n", source, target);
    FILE * target_file; FILE * source_file;
    // open target
    if (target_file = fopen(target,"r")) {
        char * new_target;
        strcpy(new_target, target);
        strcat(new_target,".bak");
        rename(target, new_target);
    }
    target_file = fopen(target, "w");

    // open source
    source_file = fopen(source, "r");
    // write a few lines
    int c;
    do {
        c = fgetc(source_file);
        if (c != EOF) {
            fputc(c, target_file); 
        }
    } while (c != EOF);

    // close_if_open target
    close(target_file);
    // close_if_open source
    close(source_file);
}
