#include "qerr.h"
#include "qlex.h"
#include <fcntl.h>
#include <unistd.h>

/*
** Run this Test
** cc ../src/qwqc.c ../src/qlex.c ../src/qerr.c -I../include -o test_lexer
** ./test_lexer
** ./test_lexer ./inputs/input01.txt
** ./test_lexer ./inputs/input02.txt
** ./test_lexer ./inputs/input03.txt
*/

char *tokstr[] = {"+", "-", "*", "/", "intlit"};

static void ScanFile(QWQC_LexerContext *clx, char *filename);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return QWQC_GetError(QWQC_ERR_NOT_ENOUGH_ARGV);
  }

  QWQC_LexerContext clx;
  clx.line = 1;
  clx.putback = '\n';

  if ((clx.infile = fopen(argv[1], "r")) == NULL) {
    return QWQC_GetError(QWQC_ERR_FILE_OPEN_FAILED);
  }

  ScanFile(&clx, argv[1]);
}

static void ScanFile(QWQC_LexerContext *clx, char *filename) {
  struct qwqc_token T;

  int fd = open(filename, O_RDONLY);
  char buffer[100];
  ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
  printf("Read %zd bytes: \n%*s\n", bytes_read, (int)bytes_read, buffer);

  while (QWQC_LexerScan(clx, &T)) {
    printf("Token %s", tokstr[T.token]);
    if (T.token == Q_T_INTLIT)
      printf(", value %d", T.intval);
    printf("\n");
  }
}
