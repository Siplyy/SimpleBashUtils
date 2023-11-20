#ifndef HELP_H
#define HELP_H

#define STRINGSSIZE 100

#include <regex.h>

#include "../common/common.h"
#include "getopt.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void substringOccurrences(const char *input, const char *substring, int iFlag,
                          int hFlag, int nFlag, int countFilesFlag,
                          char *fileName, int k);

char **readRegular(char **strings, char *filename, int *ctr);

void printer(char *buff);

char **parcing(int argc, char **argv, int *cFlag, int *eFlag, int *fFlag,
               int *hFlag, int *iFlag, int *lFlag, int *nFlag, int *oFlag,
               int *sFlag, int *vFlag, int *argvNumber, int *stringsLen);

void finder(char **buff, int buffLen, char **strings, int stringsLen, int cFlag,
            int hFlag, int iFlag, int lFlag, int nFlag, int oFlag, int vFlag,
            char *fileName, int countFilesFlag);

#endif
