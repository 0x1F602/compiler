#ifndef PARSER_H
#define PARSER_H

int program(fileStruct*);
token declarelist(fileStruct*);
token idlist(fileStruct*);
token statementlist(fileStruct*,token);
token outputlist(fileStruct*);
token expression(fileStruct*);
token expression2(fileStruct*, token);

int retval1;

#endif
