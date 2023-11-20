#ifndef COMMON_H
#define COMMON_H

#define STRSIZE 300
#define BUFFSIZE 2000

#include <stdio.h>
#include <stdlib.h>

void fileRead(FILE *fl, char ***buff, int *strNum);

void cleaner(char **buff, int len);

#endif