#include "s21_grep.h"

int main(int argc, char** argv) {
  arguments arg = parser(argc, argv);
  output(arg, argc, argv);

  return 0;
}

void add_pattern(arguments* arg, char* pattern) {
  if (arg->len_pattern != 0) {
    strcat(arg->pattern + arg->len_pattern, "|");
    arg->len_pattern++;
  }
  arg->len_pattern += sprintf(arg->pattern + arg->len_pattern, "(%s)", pattern);
}

void add_reg_from_file(arguments* arg, char* filepath) {
  FILE* f = fopen(filepath, "r");
  if (f == NULL) {
    if (!arg->s) perror(filepath);
    exit(1);
  }
  char* line = NULL;
  size_t memlen = 0;
  int read = 0;
  read = getline(&line, &memlen, f);

  while (read != -1) {
    if (line[read - 1] == '\n') line[read - 1] = '\0';
    add_pattern(arg, line);
    read = getline(&line, &memlen, f);
  }
  free(line);
  fclose(f);
}

arguments parser(int argc, char* argv[]) {
  arguments arg = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        add_pattern(&arg, optarg);
        break;

      case 'i':
        arg.i = REG_ICASE;
        break;

      case 'v':
        arg.v = 1;
        break;

      case 'c':
        arg.c = 1;
        break;

      case 'l':
        arg.l = 1;
        // arg.c = 1;
        break;

      case 'n':
        arg.n = 1;
        break;

      case 'h':
        arg.h = 1;
        break;

      case 's':
        arg.s = 1;
        break;
      case 'f':
        arg.f = 1;
        add_reg_from_file(&arg, optarg);
        break;

      case 'o':
        arg.o = 1;
        break;

      default:
        fprintf(stderr, "Wrong Flag");
        exit(1);
    }
  }
  if (arg.len_pattern == 0) {
    add_pattern(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    arg.h = 1;
  }
  if (arg.o && arg.v) arg.o = 0;
  return arg;
}

void output_line(char* line, int n) {
  for (int i = 0; i < n; i++) putchar(line[i]);
  if (line[n - 1] != '\n') putchar('\n');
}

void print_match(regex_t* reg, char* line) {
  regmatch_t match;
  int offset = 0;

  while (1) {
    int result = regexec(reg, line + offset, 1, &match, 0);
    if (result != 0) break;

    int start_index = offset + match.rm_so;
    int end_index = offset + match.rm_eo;
    for (int i = start_index; i < end_index; i++) {
      putchar(line[i]);
    }
    putchar('\n');

    if (match.rm_so == match.rm_eo) {
      offset++;
    } else {
      offset = end_index;
    }
  }
}

void file_processing(arguments arg, char* path, regex_t* reg) {
  FILE* f = fopen(path, "r");
  if (f == NULL) {
    if (!arg.s) perror(path);
    exit(1);
  }
  char* line = NULL;
  size_t memlen = 0;
  int read = 0;
  int line_count = 1;
  int count = 0;
  read = getline(&line, &memlen, f);

  while (read != -1) {
    int result = regexec(reg, line, 0, NULL, 0);
    if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
      if (!arg.c && !arg.l) {
        if (!arg.h) printf("%s:", path);
        if (arg.n) printf("%d:", line_count);
        if (arg.o) {
          print_match(reg, line);
        } else {
          output_line(line, read);
        }
      }
      count++;
    }
    read = getline(&line, &memlen, f);
    line_count++;
  }
  if (arg.l && count > 0) printf("%s\n", path);
  if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", count);
  }

  fclose(f);
  free(line);
}

void output(arguments arg, int argc, char** argv) {
  regex_t re;
  int error = regcomp(&re, arg.pattern, REG_EXTENDED | arg.i);
  if (error) perror("Error");
  for (int i = optind; i < argc; i++) {
    file_processing(arg, argv[i], &re);
  }
  regfree(&re);
}