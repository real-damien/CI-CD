#ifndef S21_CAT
#define S21_CAT

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} arguments;

void parser(int argc, char **argv, arguments *options);
void cat(FILE *f, arguments *options);

#endif
