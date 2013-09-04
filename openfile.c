#include "openfile.h"
#include <string.h>

/* usage:
 * char * prompt = "Prompt: ";
 * char * entered = prompt_user(prompt);
 * assumes size of entered text is less than 32
 */
char * prompt_user(char * message) {
    printf(message);
    char * input = (char *) malloc(32);
    //scanf("%31s", input);	wouldn't accept whitespace
    gets(input);
    if (strlen(input)==0)
    {
    	exit(1);
    }
    return input;
}

/* usage:
 * handle_no_params();
 */

void handle_no_params(void) {
	int check=0;
	char * filename= (char *) malloc(32);
	char * outname = (char *) malloc(32);
	filename= input_file_name();
	while(check!=1)
	{
		if (files.in =  fopen(filename,"r")== NULL)
		{
			filename=input_file_name();
		}
		else
		{
			inf_check=1;
		}
	}
	check=0;
	outname=output_file_name();
	if(files.out= fopen(outname,"r")==NULL)		//will open file without deleting previous one
	{
		fclose(files.out);
		files.out=fopen(outname,"w");			//opens in writeable mode
	}
	else
	{
		
		//create backup file
	}
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

char * input_file_name (void)
{
		char * dotptr = (char *) malloc(32);
		char * filename= (char *) malloc(32);
		char * inf = (char *) malloc(32);
		inf=prompt_user("Please enter an input file name:\t");
		dotptr=inf;
		dotptr=strchr(dotptr,'.');	//finds location of . character
		if (dotptr==NULL)
		{
			filename=inf;
			strcat(filename,INPUT_EXTENSION);
		}
		else
		{
			filename=inf;
		}
		return filename;
}

char * output_file_name (void)
{
		char * dotptr = (char *) malloc(32);
		char * filename= (char *) malloc(32);
		char * inf = (char *) malloc(32);
		inf=prompt_user("Please enter an out file name:\t");
		dotptr=inf;
		dotptr=strchr(dotptr,'.');	//finds location of . character
		if (dotptr==NULL)
		{
			filename=inf;
			strcat(filename,OUTPUT_EXTENSION);
		}
		else
		{
			filename=inf;
		}
		return filename;
}
