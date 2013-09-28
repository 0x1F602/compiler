#include <stdio.h>
#include "headers/openfile.h"
#include "headers/scanner.h"
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

// idea mostly from http://www.mytechinterviews.com/reverse-a-linked-list
token * reverse(token * head) {
    token * t1;
    token * previous = NULL;
    while(head != NULL) {
        t1 = (token *)head->next;
        head->next = (struct token *)previous;
        previous = head;
        head = t1;
    }
    return previous;
}

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
    token ** token_head_ptr;
    *token_head_ptr = NULL;
    scanner(of_d_ptr, token_head_ptr);
    token * token_head = *token_head_ptr;
    token_head = reverse(token_head);
    /* testing the token linked list here */
    token * current = (token *)token_head;
    if(parser(*current))
    {
    	//no errors
    }
    else
    {
    	//syntax error somewhere
    }
/*    do {
        printf("Token: %d\n", current->token_number);
        if (current->next != NULL) {
            current = (token *)current->next;
        }
        else {
            current = NULL;
        }
    } while (current != NULL);
*/    
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
