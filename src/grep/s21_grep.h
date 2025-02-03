#ifndef S21_GREP
#define S21_GREP

#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  char pattern[2048];
  int len_pattern;

} arguments;
void add_pattern(arguments* arg, char* pattern);
void add_reg_from_file(arguments* arg, char* filepath);
arguments parser(int argc, char* argv[]);
void output_line(char* line, int n);
void print_match(regex_t* reg, char* line);
void file_processing(arguments arg, char* path, regex_t* reg);
void output(arguments arg, int argc, char** argv);

#endif
