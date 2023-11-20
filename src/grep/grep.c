#include "grep.h"

void grep(int argc, char **argv) {
  int eFlag = 0, iFlag = 0, vFlag = 0, cFlag = 0, lFlag = 0, nFlag = 0,
      hFlag = 0, sFlag = 0, fFlag = 0, oFlag = 0;
  int argvNumber = 0;
  int stringsLen;
  FILE *fl;
  char **strings =
      parcing(argc, argv, &cFlag, &eFlag, &fFlag, &hFlag, &iFlag, &lFlag,
              &nFlag, &oFlag, &sFlag, &vFlag, &argvNumber, &stringsLen);
  if ((!eFlag) && (!fFlag) && (argc > 1)) {
    strcpy(strings[0], argv[argvNumber]);
    argvNumber += 1;
    stringsLen = 1;
  }
  int countFilesFlag = argc - argvNumber;
  if (strings[0] != NULL) {
    while (argvNumber < argc) {
      fl = fopen(argv[argvNumber], "r");
      if (fl == NULL) {
        if (!sFlag) {
          printf("n/a");
        }
      } else {
        char **buff = calloc(BUFFSIZE, sizeof(char *));
        for (int i = 0; i < BUFFSIZE; ++i) {
          buff[i] = calloc(STRSIZE, sizeof(char));
        }
        int strNum = 0;
        fileRead(fl, &buff, &strNum);
        finder(buff, strNum, strings, stringsLen, cFlag, hFlag, iFlag, lFlag,
               nFlag, oFlag, vFlag, argv[argvNumber], countFilesFlag);
        for (int i = 0; i < BUFFSIZE; ++i) {
          free(buff[i]);
        }
        free(buff);
        int close = fclose(fl);
        if (close != 0) {
          printf("n/a");
        }
      }
      argvNumber += 1;
    }
  } else {
    printf("n/a");
  }

  for (int i = 0; i < STRINGSSIZE; ++i) {
    free(strings[i]);
  }
  free(strings);
}