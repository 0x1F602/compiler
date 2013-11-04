#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "headers/openfile.h"


fileStruct openfile(int argc, char * argv)
{
    fileStruct file_struct;
    char inputName[35];
    char extName[35];
    char buffer[35];
    size_t len;
    bool exists=false;
    if(argc==1)
    {
        while (!exists)
        {
            printf("Enter an input file name: ");
            fgets(buffer,filenameSize,stdin);
            len = strlen(buffer) - 1;
            if (buffer[len]=='\n') {
                buffer[len]='\0';
            }
            if(file_exists(buffer))
            {
                exists=true;
            }
            else
            {
                printf("File doesn't exist\n");
            }
        }

    }
    else if(argc>=1)
    {
        strcpy(buffer,argv);
        if(file_exists(buffer))
        {
            exists=true;
        }
        else
        {
            printf("File doesn't exist\n");
        }
        while (!exists)
        {
            printf("Enter an input file name: ");
            fgets(buffer,filenameSize,stdin);
            len = strlen(buffer) - 1;
            if (buffer[len]=='\n') {
                buffer[len]='\0';
            }
            if(file_exists(buffer))
            {
                exists=true;
            }
            else
            {
                printf("File doesn't exist\n");
            }
        }
    }
    file_struct.input=fopen(buffer,"r");
    sscanf(buffer,"%[A-Za-z0-9].%[A-Za-z0-9]",inputName,extName);
    sprintf(buffer,"%s.c",inputName);
    file_struct.outc=fopen(buffer,"w");
    sprintf(buffer,"%s.lis",inputName);
    file_struct.lis_file=fopen(buffer,"w");
    sprintf(buffer,"%s.tmp1",inputName);
    file_struct.tmp1=fopen(buffer,"w");
    sprintf(buffer,"%s.tmp2",inputName);
    file_struct.tmp2=fopen(buffer,"w");
    return file_struct;
}

bool file_exists(char * filename)
{
    FILE * file;
    bool flag;
    if (file = fopen(filename, "r"))
    {
        fclose(file);
        flag=true;
    }
    else
    {
        flag=false;
    }
        return flag;
}

