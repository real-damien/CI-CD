CC = gcc -Wall -Werror -Wextra -std=c11 

all: clean s21_grep

s21_grep: s21_grep.c
	$(CC) s21_grep.c -o s21_grep

test:
	bash tests_grep.sh

clean:
	rm -f s21_grep