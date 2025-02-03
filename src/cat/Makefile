CC = gcc -Wall -Werror -Wextra -std=c11 

all: clean s21_cat

s21_cat: s21_cat.c
	$(CC) s21_cat.c -o s21_cat

test:
	bash tests_cat.sh

clean:
	rm -f s21_cat