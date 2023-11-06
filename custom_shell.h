#ifndef SHELL_H
#define SHELL_H

char **splitInputString(char *input, int *argCount);
void tokenizeString(char *str, char *delimiters, char **tokens);
int createChildProcess(char *pathVar, char *systemCallPath, char **tokenArray);
int checkPathForSystemCall(char *pathVar, char **pathArray, char **tokenArray);
char *duplicateString(char *str);
char *_strcat(char *destination, char *source);
char *_strcpy(char *destination, char *source);
int _strlen(char *string);
int _strncmp(char *string1, char *string2, int n);
int _strcmp(char *string1, char *string2);
void splitAndTokenizeString(char *inputString, char *delimiters, char **tokens);
int createChildProcess(char *pathEnv, char *commandPath, char **args);
int checkCommandInPath(char *pathEnv, char **pathDirs, char **args);
char *duplicateString(char *originalString);

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#endif
