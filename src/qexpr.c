#include "qexpr.h"
#include "qast.h"
#include "qerr.h"
#include "qlex.h"
#include <_stdlib.h>

// 操作符列表
static char *ASTop[4] = {"+", "-", "*", "/"};

QWQC_AstMap ast_map[5] = {{Q_A_ADD, Q_T_PLUS},
                          {Q_A_SUBTRACT, Q_T_MINUS},
                          {Q_A_MULTIPLY, Q_T_STAR},
                          {Q_A_DIVIDE, Q_T_SLASH},
                          {5, 5}};

// 将Token转换为AST操作
int QWQC_AstArithOp(QWQC_LexerContext *clx) {
  for (int i = 0; ast_map[i].ast_type != 5; i++) {
    if (ast_map[i].token_type == clx->token.token) {
      return ast_map[i].ast_type;
    }
  }

  exit(QWQC_GetError(QWQC_ERR_UNKNOWN_AST_OP, clx->line));
}

// 解析主因子并返回一个AST节点
static QWQC_AstNode *QWQC_AstPrimary(QWQC_LexerContext *clx) {
  QWQC_AstNode *node;

  // 对于INTLIT token，为其创建一个AST叶节点并扫描下一个标记。
  // 否则，语法错误对于任何其他标记类型。
  switch (clx->token.token) {
  case Q_T_INTLIT:
    node = QWQC_MakeAstLeaf(Q_A_INTLIT, clx->token.intval);
    QWQC_LexerScan(clx);
    return node;
  default:
    exit(QWQC_GetError(QWQC_ERR_SYNTAX, clx->line));
  }
}

// "Binary Expression" 返回根为二元运算符的 AST 树
QWQC_AstNode *QWQC_AstBinExpr(QWQC_LexerContext *clx) {
  QWQC_AstNode *node, *left, *right;
  int nodetype;

  // 获取左边的整数字面，同时获取下一个标记。
  left = QWQC_AstPrimary(clx);

  // 如果没有剩余标记，则只返回左节点
  if (clx->token.token == Q_T_EOF) {
    return left;
  }

  // 将标记转换为节点类型
  nodetype = QWQC_AstArithOp(clx);

  // 获取下一个令牌
  QWQC_LexerScan(clx);

  // 递归获取右侧树
  right = QWQC_AstBinExpr(clx);

  // 现在用这两个子树构建一棵树
  node = QWQC_MakeAstNode();
  node->op = nodetype;
  node->left = left;
  node->right = right;

  return node;
}

// 给定 AST，解释其中的运算符，并返回最终值。
int QWQC_ExprInterPretAst(QWQC_AstNode *node) {
  int leftval, rightval;

  // 获取左右子树的值
  if (node->left) {
    leftval = QWQC_ExprInterPretAst(node->left);
  }
  if (node->right) {
    rightval = QWQC_ExprInterPretAst(node->right);
  }

  // Debug: Print what we are about to do
  if (node->op == Q_A_INTLIT)
    printf("int %d\n", node->intval);
  else
    printf("%d %s %d\n", leftval, ASTop[node->op], rightval);

  switch (node->op) {
  case Q_A_ADD:
    return (leftval + rightval);
  case Q_A_SUBTRACT:
    return (leftval - rightval);
  case Q_A_MULTIPLY:
    return (leftval * rightval);
  case Q_A_DIVIDE:
    return (leftval / rightval);
  case Q_A_INTLIT:
    return (node->intval);
  default:
    exit(QWQC_GetError(QWQC_ERR_UNKNOWN_AST_OP, node->op));
  }
}
