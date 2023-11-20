CC = gcc

CFLAGS = -Wall -Werror -Wextra -std=c11
all: s21_grep
s21_grep: 
	$(CC) $(CFLAGS) main.c grep.c help.c ./../common/common.c -o s21_grep
clean:
	rm -rf *.o s21_grep
