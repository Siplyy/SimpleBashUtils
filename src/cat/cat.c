#include "cat.h"

char **catB(char **buff, int strNum) {
  int num = 1;
  for (int i = 0; i < strNum; ++i) {
    if (buff[i][0] != '\n') {
      buff[i] = addNumber(buff[i], num);
      num += 1;
    }
  }
  return buff;
}

char **catE(char **buff, int strNum) {
  for (int i = 0; i < strNum; ++i) {
    buff[i] = replaceSigns(buff[i], 2);
  }
  return buff;
}

char **catN(char **buff, int strNum) {
  int num = 1;
  for (int i = 0; i < strNum; ++i) {
    if ((buff[i][0] != '\n') || (i != strNum - 1)) {
      buff[i] = addNumber(buff[i], num);
      num += 1;
    }
  }
  return buff;
}

char **catS(char **buff, int *strNum) {
  for (int i = 0; i < *strNum - 1; ++i) {
    if ((buff[i][0] == '\n') && (buff[i + 1][0] == '\n')) {
      while ((buff[i][0] == '\n') && ((buff[i + 1][0] == '\n'))) {
        buff = copyWithout(buff, strNum, i);
      }
    }
  }
  return buff;
}

char **catT(char **buff, int strNum) {
  for (int i = 0; i < strNum; ++i) {
    buff[i] = replaceSigns(buff[i], 0);
  }
  return buff;
}

char **catV(char **buff, int strNum) {
  for (int i = 0; i < strNum; ++i) {
    buff[i] = replaceSigns(buff[i], 1);
  }
  return buff;
}

void cat(int argc, char **argv) {
  int bFlag = 0, eFlag = 0, EFlag = 0, nFlag = 0, sFlag = 0, tFlag = 0,
      TFlag = 0, vFlag = 0;
  int iter = parcing(argc, argv, &bFlag, &eFlag, &EFlag, &nFlag, &sFlag, &tFlag,
                     &TFlag, &vFlag);
  while (iter < argc) {
    FILE *fl;
    fl = fopen(argv[iter], "r");
    if (fl == NULL) {
      printf("n/a");
    } else {
      char **buff = calloc(BUFFSIZE, sizeof(char *));
      for (int i = 0; i < BUFFSIZE; ++i) {
        buff[i] = calloc(STRSIZE, sizeof(char));
      }
      int strNum = 0;
      fileRead(fl, &buff, &strNum);
      if (sFlag) {
        buff = catS(buff, &strNum);
      }
      if (bFlag) {
        buff = catB(buff, strNum);
      }
      if (EFlag) {
        buff = catE(buff, strNum);
      }
      if (eFlag) {
        buff = catE(buff, strNum);
        buff = catV(buff, strNum);
      }
      if (nFlag) {
        buff = catN(buff, strNum);
      }
      if (TFlag) {
        buff = catT(buff, strNum);
      }
      if (tFlag) {
        buff = catT(buff, strNum);
        buff = catV(buff, strNum);
      }
      if (vFlag) {
        buff = catV(buff, strNum);
      }
      buffPrint(buff, strNum);
      cleaner(buff, BUFFSIZE);
      fclose(fl);
    }
    iter += 1;
  }
}