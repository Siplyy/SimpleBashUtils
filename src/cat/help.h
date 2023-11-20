#ifndef HELP_H
#define HELP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/common.h"
#include "getopt.h"

void buffPrint(char **buff, int len);

char *reverse(char *mass, int num);

char *fromIntToChar(int num);

char *addNumber(char *str, int number);

char **copyWithout(char **mass, int *len, int num);

char *replaceSigns(char *str, int check);

int parcing(int argc, char **argv, int *bFlag, int *eFlag, int *EFlag,
            int *nFlag, int *sFlag, int *tFlag, int *TFlag, int *vFlag);

#endif