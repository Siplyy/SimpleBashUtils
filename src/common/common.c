#include "common.h"

void fileRead(FILE *fl, char ***buff, int *strNum) {
  int sym = 0;
  int symCounter = 0;
  int strCounter = 0;

  while ((sym = fgetc(fl)) != EOF) {
    (*buff)[strCounter][symCounter] = sym;
    symCounter += 1;

    if (sym == '\n') {
      (*buff)[strCounter][symCounter] = '\0';
      symCounter = 0;
      strCounter += 1;
    }
  }

  if (symCounter > 0) {
    (*buff)[strCounter][symCounter] = '\0';
    strCounter += 1;
  }

  *strNum = strCounter;
}

void cleaner(char **buff, int len) {
  for (int i = 0; i < len; ++i) {
    free(buff[i]);
  }
  free(buff);
}