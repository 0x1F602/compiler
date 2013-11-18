#ifndef PARSER_H
#define PARSER_H

int program(fileStruct*);
token declarelist(fileStruct*);
token idlist(fileStruct*);
token statementlist(fileStruct*,token);
token outputlist(fileStruct*);

int retval1;

#endif
