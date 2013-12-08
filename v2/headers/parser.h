#ifndef PARSER_H
#define PARSER_H

int program(fileStruct*);
token declarelist(fileStruct*);
token idlist(fileStruct*,int,token);
token statementlist(fileStruct*,token);
token statementlist2(fileStruct*,token);
token statementlist3(fileStruct*,token);
token statementlist4(fileStruct*,token);
token outputlist(fileStruct*);
token expression(fileStruct*);
token expression2(fileStruct*, token);
token condition(fileStruct*);
int getType(char*);

int retval1;

struct symbol{
    char name[64];
    int type;
};

struct symbol symboltable[100];

int symbind;

#endif
