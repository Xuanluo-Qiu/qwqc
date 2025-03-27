#include "qast.h"

QWQC_AstNode *QWQC_MakeAstNode() {
  QWQC_AstNode *node = (QWQC_AstNode *)malloc(sizeof(QWQC_AstNode));
  if (node == NULL) {
    exit(QWQC_GetError(QWQC_ERR_MEMORY_ALLOCATION_FAILED, "AST node"));
  }

  return node;
}

QWQC_AstNode *QWQC_MakeAstLeaf(int op, int intval) {
  QWQC_AstNode *node = QWQC_MakeAstNode();
  node->op = op;
  node->left = NULL;
  node->right = NULL;
  node->intval = intval;

  return node;
}

QWQC_AstNode *QWQC_MakeAstUnary(int op, QWQC_AstNode *left, int intval) {
  QWQC_AstNode *node = QWQC_MakeAstNode();
  node->op = op;
  node->left = left;
  node->right = NULL;
  node->intval = intval;

  return node;
}
