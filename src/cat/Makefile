CC = gcc

CFLAGS = -Wall -Werror -Wextra -std=c11
all: s21_cat
s21_cat: 
	$(CC) $(CFLAGS) main.c cat.c help.c ./../common/common.c -o s21_cat
clean:
	rm -rf *.o s21_cat