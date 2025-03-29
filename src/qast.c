#include "qast.h"

QWQC_AstNode *QWQC_MakeAstNode(int op, QWQC_AstNode *left, QWQC_AstNode *right,
                               int intval) {
  QWQC_AstNode *node;

  // Malloc a new ASTnode
  node = (QWQC_AstNode *)malloc(sizeof(QWQC_AstNode));
  if (node == NULL) {
    exit(QWQC_GetError(QWQC_ERR_MEMORY_ALLOCATION_FAILED, "AST node"));
  }
  // Copy in the field values and return it
  node->op = op;
  node->left = left;
  node->right = right;
  node->intval = intval;

  return node;
}

QWQC_AstNode *QWQC_MakeAstLeaf(int op, int intval) {
  QWQC_AstNode *node = QWQC_MakeAstNode(op, NULL, NULL, intval);

  return node;
}

QWQC_AstNode *QWQC_MakeAstUnary(int op, QWQC_AstNode *left, int intval) {
  QWQC_AstNode *node = QWQC_MakeAstNode(op, left, NULL, intval);

  return node;
}
