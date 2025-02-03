#include "s21_cat.h"

int main(int argc, char **argv) {
  FILE *f;
  arguments flag = {0};
  parser(argc, argv, &flag);
  if (flag.b) flag.n = 0;
  while (optind < argc) {
    char *file_name = argv[optind++];
    f = fopen(file_name, "r");

    if (f == NULL) {
      printf("%s: no such file or directory", file_name);
      printf("\n");
      continue;
    } else {
      cat(f, &flag);
    }

    fclose(f);
  }
  return 0;
}

void parser(int argc, char **argv, arguments *flag) {
  int opt;
  int option_index;
  static struct option long_option[] = {
      {"line_count-nonblank", no_argument, NULL, 'b'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {"line_count", no_argument, NULL, 'n'},
      {0, 0, 0, 0}};
  while ((opt = getopt_long(argc, argv, "+benstvTE", long_option,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        flag->b = 1;
        break;

      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;

      case 'n':
        flag->n = 1;
        break;

      case 's':
        flag->s = 1;
        break;

      case 't':
        flag->t = 1;
        flag->v = 1;
        break;

      case 'v':
        flag->v = 1;
        break;

      case 'E':
        flag->e = 1;
        break;

      case 'T':
        flag->t = 1;
        break;

      default:
        fprintf(stderr, "Wrong flag\n");
        exit(1);
    }
  }
}

void cat(FILE *f, arguments *flag) {
  int current = 0;
  int not_empty = 0;
  int line_count = 0;
  int empty_lines = 0;
  int last_sym = 0;

  for (last_sym = '\n'; (current = fgetc(f)) != EOF; last_sym = current) {
    if (flag->s) {
      if (last_sym == '\n' && current == '\n') {
        if (empty_lines) {
          empty_lines = 2;
          if (empty_lines == 2) {
            continue;
          }

        } else {
          empty_lines = 1;
        }
      } else {
        empty_lines = 0;
      }
    }
    if (flag->b) {
      if (last_sym == '\n' && current != '\n') {
        not_empty++;
        printf("%6d\t", not_empty);
      }
    }
    if (flag->n && !flag->b) {
      if (last_sym == '\n') {
        line_count++;
        printf("%6d\t", line_count);
      }
    }
    if (flag->e) {
      if (current == '\n') {
        printf("$");
      }
    }

    if (flag->t) {
      if (current == '\t') {
        printf("^I");
        continue;
      }
    }
    if (flag->v) {
      if ((current >= 1 && current <= 8) || (current >= 12 && current <= 31)) {
        printf("^%c", current + 64);
        continue;
      } else if (current == 127) {
        printf("^%c", current - 64);
        continue;
      } else if (current >= 128 && current <= 159) {
        printf("M-^%c", current - 64);
        continue;
      } else if (current >= 160) {
        printf("M-%c", current - 128);
        continue;
      }
    }

    printf("%c", current);
  }
}
