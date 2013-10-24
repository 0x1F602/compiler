#include "headers/openfile.h"

#define max_size 32
#define max_tokens 5

const char * src_prompt = "Source filename: ";
const char * tar_prompt = "Target filename: ";

char * prompt_user(const char * message) {
    printf(message);
    char * input = (char *) malloc(max_size);
    //scanf("%[A-Za-z0-9 \.]s\n", input); // should use regex but askldjalskdja;sldfjk
    fgets(input, max_size, stdin);
    size_t len = strlen(input) - 1;
    if (input[len]=='\n') {
        input[len]='\0';
    }
    /* stole this solution from http://stackoverflow.com/a/2693827 */
    return input;
}

openfile_data handle_no_params(void) {
    char * src_filename = prompt_user(src_prompt);
    openfile_data of_d;
    if (strlen(src_filename) > 0) {
        of_d = handle_one_params(src_filename);
    }
    free(src_filename);

    return of_d;
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

    free(ts.tokens); 

    return extension;
}

char * check_or_add_extension(char * filename, char * default_extension) {
    char * extension = find_extension(filename);
    //printf("Found extension from %s: %s\n", filename, extension);
    char * new_filename = (char *) malloc(32);
    strcpy(new_filename, filename);
    sprintf(new_filename, "%s", filename);
    if (extension == NULL) {
        strcat(new_filename, default_extension);
    }
    else {
        //printf("%s %s\n\n", filename, extension);
        sprintf(new_filename, "%s.%s", filename, extension);
    }
    //printf("Filename: %s\n", filename);
    return new_filename;
}

void generate_filename(char * source, char * target, char * output_ext) {
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
        strcat(target, source_filename_body);
        strcat(target, output_ext);
    }
    free(ts.tokens);
}

openfile_data handle_one_params(char * source) {
    source = check_or_add_extension(source, INPUT_EXTENSION);
    char * target = (char *) malloc(max_size);
    //char * target = prompt_user(tar_prompt);
    if (strlen(target) <= 0) {
        generate_filename(source, target, OUTPUT_EXTENSION);
    }
    //target = check_or_add_extension(target, OUTPUT_EXTENSION);
    openfile_data ofd = handle_two_params(source, target);
    return ofd;
}

openfile_data handle_two_params(char * source, char * target) {
    source = check_or_add_extension(source, INPUT_EXTENSION);
    //target = check_or_add_extension(target, OUTPUT_EXTENSION);
    // here we need to detect the filename separate from the extension
    // and we need to take the filename and add in a c for the extension
    //target = 
    printf("Source: %s, Target: %s\n", source, target);
    openfile_data of_d;
    FILE * target_file; FILE * source_file;
	char outc_name[32];
    // open target
    if (target_file = fopen(target,"r")) {
        char * new_target = (char *) malloc(32);
        strcpy(new_target, target);
        strcat(new_target,".bak");
        rename(target, new_target);
        free(new_target);
        fclose(target_file);
    }

    if (strcmp(target,source)!=0) {
        // open source
        source_file = fopen(source, "r");
        if (source_file == NULL) {
            printf("Source file doesn't exist.\n");
            return of_d; // sorry about the hacky solution but everyone realized it was due 9/4 on 9/4
        }
        target_file = fopen(target, "w");
        char * listing_filename = (char *) malloc(32);
        generate_filename(source, listing_filename, ".LIS");
        FILE * tempfile1 = fopen("tmp1", "w");
        FILE * tempfile2 = fopen(listing_filename, "w");
		FILE * tempfile3 = fopen("tmp2","wr");
		FILE * outc = fopen(target,"w");
        // implementing agreed upon pseudocode
        of_d.input = source_file;
        of_d.output = target_file;
        of_d.temp1 = tempfile1;
        of_d.listing_file = tempfile2;
		of_d.temp2 = tempfile3;
		of_d.outc = outc;
    }
    else {
        printf("ERROR: Target can't be Source!\n");
    }
    
    free(source); free(target);

    return of_d;
}
