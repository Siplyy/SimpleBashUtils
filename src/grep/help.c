#include "help.h"

void substringOccurrences(const char *input, const char *substring, int iFlag,
                          int hFlag, int nFlag, int countFilesFlag,
                          char *fileName, int k) {
  regex_t regex;
  regmatch_t match;

  if (iFlag) {
    regcomp(&regex, substring, REG_EXTENDED | REG_ICASE);
  } else {
    regcomp(&regex, substring, REG_EXTENDED);
  }
  int printedNumber = 0;
  int printedFile = 0;

  while (regexec(&regex, input, 1, &match, 0) == 0) {
    int start = match.rm_so;
    int end = match.rm_eo;
    if ((countFilesFlag > 1) && (!hFlag) && (!printedFile)) {
      printf("%s:", fileName);
      printedFile = 1;
    }
    if ((nFlag) && (!printedNumber)) {
      printf("%d:", k + 1);
      printedNumber = 1;
    }
    printf("%.*s\n", end - start, input + start);
    input += match.rm_eo;
  }
  regfree(&regex);
}

char **readRegular(char **strings, char *filename, int *ctr) {
  int counter = *ctr;
  FILE *fl;
  fl = fopen(filename, "r");
  if (fl == NULL) {
    printf("n/a");
  } else {
    int worker = 1;
    while (worker) {
      int sym = fgetc(fl);
      if (sym == EOF) {
        worker = 0;
      }
      int i = 0;
      if (sym == '\n') {
        strings[counter][i] = sym;
        i += 1;
        strings[counter][i] = '\0';
        counter += 1;
      }
      while ((sym != '\n') && (sym != EOF)) {
        strings[counter][i] = sym;
        i += 1;
        sym = fgetc(fl);
        if ((sym == '\n') || (sym == EOF)) {
          if (sym == EOF) {
            strings[counter][i] = '\0';
          }
          counter += 1;
        }
      }
    }
    int close = fclose(fl);
    if (close != 0) {
      printf("n/a");
    }
  }
  if (counter != 0) {
    *ctr = counter;
  } else {
    *ctr = 1;
  }
  return strings;
}

void printer(char *buff) {
  int k = 0;
  while (buff[k] != '\0') {
    printf("%c", buff[k]);
    k += 1;
  }
  if (buff[k - 1] != '\n') {
    printf("\n");
  }
}

char **parcing(int argc, char **argv, int *cFlag, int *eFlag, int *fFlag,
               int *hFlag, int *iFlag, int *lFlag, int *nFlag, int *oFlag,
               int *sFlag, int *vFlag, int *argvNumber, int *stringsLen) {
  char **strings = calloc(STRINGSSIZE, sizeof(char *));
  for (int i = 0; i < STRINGSSIZE; ++i) {
    strings[i] = calloc(STRSIZE, sizeof(char));
  }
  int counter = 0, ch = 0, check = 0;
  while ((check = getopt(argc, argv, "ce:f:hilnosv")) != -1) {
    if (ch == 0) {
      *argvNumber += 1;
      ch = 1;
    }
    if (check == 'c') {
      *cFlag = 1;
    } else if (check == 'e') {
      strcpy(strings[counter], optarg);
      counter += 1;
      *eFlag = 1;
    } else if (check == 'f') {
      strings = readRegular(strings, optarg, &counter);
      *fFlag = 1;
    } else if (check == 'h') {
      *hFlag = 1;
    } else if (check == 'i') {
      *iFlag = 1;
    } else if (check == 'l') {
      *lFlag = 1;
    } else if (check == 'n') {
      *nFlag = 1;
    } else if (check == 'o') {
      *oFlag = 1;
    } else if (check == 's') {
      *sFlag = 1;
    } else if (check == 'v') {
      *vFlag = 1;
    }
  }
  *stringsLen = counter;
  *argvNumber = optind;
  return strings;
}

void finder(char **buff, int buffLen, char **strings, int stringsLen, int cFlag,
            int hFlag, int iFlag, int lFlag, int nFlag, int oFlag, int vFlag,
            char *fileName, int countFilesFlag) {
  int ret = 1;
  int countStrings = 0;
  int countedFiles = 0;
  int printed = 0;
  int f = 0;
  for (int k = 0; k < buffLen; ++k) {
    int founded = 0;
    regex_t regex;
    for (int i = 0; i < stringsLen; ++i) {
      if (iFlag) {
        ret = regcomp(&regex, strings[i], REG_EXTENDED | REG_ICASE);
      } else {
        ret = regcomp(&regex, strings[i], REG_EXTENDED);
      }
      size_t nmatch = 1;
      regmatch_t pmatch[1];
      ret = regexec(&regex, buff[k], nmatch, pmatch, 0);
      if (!ret) {
        founded += 1;
        f += 1;
      }
      if ((oFlag) && (!vFlag) && (!ret) && (!lFlag) && (!cFlag)) {
        substringOccurrences(buff[k], strings[i], iFlag, hFlag, nFlag,
                             countFilesFlag, fileName, k);
      }
      regfree(&regex);
    }

    if ((cFlag) && (founded > 0)) {
      countStrings += 1;
    }

    if (lFlag) {
      if (((vFlag) && (founded == 0)) || ((!vFlag) && (founded > 0))) {
        if (!printed) {
          if (!cFlag) {
            printf("%s\n", fileName);
          }
          countedFiles += 1;
          printed = 1;
        }
      }
    }

    if ((oFlag) && (vFlag) && (founded == 0)) {
      if ((!lFlag) && (!cFlag)) {
        if (nFlag) {
          printf("%d:", k + 1);
        }
        printer(buff[k]);
      }
    }
    if ((((founded > 0) && (!vFlag)) || ((founded == 0) && (vFlag))) &&
        (!lFlag) && (!cFlag) && (!oFlag)) {
      if ((countFilesFlag > 1) && (!hFlag)) {
        printf("%s:", fileName);
      }
      if (nFlag) {
        printf("%d:", k + 1);
      }
      printer(buff[k]);
    }
  }

  if (cFlag) {
    if ((vFlag) && (!lFlag)) {
      printf("%d\n", buffLen - countStrings);
    } else if ((!vFlag) && (!lFlag)) {
      printf("%d\n", countStrings);
    } else if ((!vFlag) && (lFlag)) {
      printf("%d\n", countedFiles);
    } else {
      printf("%d\n", countedFiles);
    }
  }

  if ((lFlag) && (cFlag)) {
    if ((vFlag) || (f > 0)) {
      printf("%s\n", fileName);
    }
  }
}