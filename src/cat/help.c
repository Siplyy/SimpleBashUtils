#include "help.h"

static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                       {"number", 0, 0, 'n'},
                                       {"squeeze-blank", 0, 0, 's'},
                                       {0, 0, 0, 0}};

void buffPrint(char **buff, int len) {
  for (int i = 0; i < len; ++i) {
    int k = 0;
    while (buff[i][k] != '\0') {
      printf("%c", buff[i][k]);
      k += 1;
    }
  }
}

char *reverse(char *mass, int num) {
  char *result = calloc(STRSIZE, sizeof(char));

  int k = num - 1;

  for (int i = 0; i < num; ++i) {
    result[i] = mass[k];
    k -= 1;
  }

  free(mass);
  return result;
}

char *fromIntToChar(int num) {
  char *result = calloc(STRSIZE, sizeof(char));

  int i = 0;

  while (num > 0) {
    result[i] = num % 10 + '0';
    i += 1;
    num = num / 10;
  }

  for (int k = i; k < 6; ++k) {
    result[k] = ' ';
    ++i;
  }

  result = reverse(result, i);
  result[i] = '\t';
  return result;
}

char *addNumber(char *str, int number) {
  char *newStr = fromIntToChar(number);
  strcat(newStr, str);

  free(str);

  return newStr;
}

char **copyWithout(char **mass, int *len, int num) {
  char **result = calloc(BUFFSIZE, sizeof(char *));
  int j = 0;
  for (int i = 0; i < BUFFSIZE; ++i) {
    if (i != num) {
      result[j] = mass[i];
      j++;
    } else {
      free(mass[i]);
    }
  }
  free(mass);
  *len -= 1;
  return result;
}

char *replaceSigns(char *str, int check) {
  int counterNew = 0;
  int counterOld = 0;
  char *newStr = calloc(STRSIZE, sizeof(char));
  if (str[counterOld] == '\n') {
    newStr[counterNew] = str[counterOld];
  }
  while (str[counterOld] != '\0') {
    if ((str[counterOld] == 9) && (check == 0)) {
      newStr[counterNew] = '^';
      newStr[counterNew + 1] = 'I';
      counterNew += 2;
      counterOld += 1;
    } else if ((str[counterOld] < 32) && (check == 1) &&
               (str[counterOld] != 9) && (str[counterOld] != '\n')) {
      newStr[counterNew] = '^';
      newStr[counterNew + 1] = str[counterOld] + 64;
      counterNew += 2;
      counterOld += 1;
    }
    if ((str[counterOld] == '\n') && (check == 2)) {
      newStr[counterNew] = '$';
      newStr[counterNew + 1] = '\n';
      counterNew += 2;
      counterOld += 1;
    } else {
      newStr[counterNew] = str[counterOld];
      counterNew += 1;
      counterOld += 1;
    }

    if (str[counterOld] == '\0') {
      newStr[counterNew] = str[counterOld];
    }
  }
  free(str);
  return newStr;
}

int parcing(int argc, char **argv, int *bFlag, int *eFlag, int *EFlag,
            int *nFlag, int *sFlag, int *tFlag, int *TFlag, int *vFlag) {
  int check = 0;
  int option_index = 0;
  while ((check = getopt_long(argc, argv, "beEnstTv", long_options,
                              &option_index)) != -1) {
    if (check == 'b') {
      *bFlag = 1;
    } else if (check == 'e') {
      *eFlag = 1;
    } else if (check == 'E') {
      *EFlag = 1;
    } else if (check == 'n') {
      *nFlag = 1;
    } else if (check == 's') {
      *sFlag = 1;
    } else if (check == 't') {
      *tFlag = 1;
    } else if (check == 'T') {
      *TFlag = 1;
    } else if (check == 'v') {
      *vFlag = 1;
    }
  }
  return optind;
}