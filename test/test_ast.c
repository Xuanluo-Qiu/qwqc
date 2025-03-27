#include "qast.h"
#include "qerr.h"
#include "qexpr.h"
#include "qlex.h"

#include <fcntl.h>
#include <unistd.h>

/*
** Run this Test
** cc ../src/qwqc.c ../src/qlex.c ../src/qerr.c ../src/qast.c ../src/qexpr.c -I../include -o test_ast
** ./test_ast
** ./test_ast ./inputs/input01.txt
** ./test_ast ./inputs/input02.txt
*/

int main(int argc, char *argv[]) {
  QWQC_LexerContext clx;
  clx.line = 1;
  clx.putback = '\n';

  QWQC_AstNode *root;

  if (argc != 2) {
    return QWQC_GetError(QWQC_ERR_NOT_ENOUGH_ARGV);
  }

  if ((clx.infile = fopen(argv[1], "r")) == NULL) {
    return QWQC_GetError(QWQC_ERR_FILE_OPEN_FAILED);
  }

  QWQC_LexerScan(&clx);
  root = QWQC_AstBinExpr(&clx);
  printf("%d\n", QWQC_ExprInterPretAst(root));

  return 0;
}
