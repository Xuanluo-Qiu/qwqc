#include "qexpr.h"
#include "qast.h"
#include "qerr.h"
#include "qlex.h"

// 操作符列表
static char *ASTop[4] = {"+", "-", "*", "/"};
// 每个token的运算优先级
// EOF  +   -   *   /  INTLIT
static int OpPrec[6] = {0, 10, 10, 20, 20, 0};

QWQC_AstMap ast_map[5] = {{Q_A_ADD, Q_T_PLUS},
                          {Q_A_SUBTRACT, Q_T_MINUS},
                          {Q_A_MULTIPLY, Q_T_STAR},
                          {Q_A_DIVIDE, Q_T_SLASH},
                          {5, 5}};

// 将Token转换为AST操作
int QWQC_AstArithOp(QWQC_LexerContext *clx, int tokentype) {
  for (int i = 0; ast_map[i].ast_type != 5; i++) {
    if (ast_map[i].token_type == tokentype) {
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

// 判断运算符优先级
// 检查是否有二进制运算符，并返回其优先级。
static int QWQC_ExperOpPrecedence(int tokentype, int line) {
  int prec = OpPrec[tokentype];
  if (prec == 0) {
    exit(QWQC_GetError(QWQC_ERR_SYNTAX, line));
  }
  return prec;
}

// "Binary Expression" 返回根为二元运算符的 AST 树
// 参数 ptp 是前一个标记的优先级。
QWQC_AstNode *QWQC_AstBinExpr(QWQC_LexerContext *clx, int ptp) {
  QWQC_AstNode *left, *right;
  int tokentype;

  // 获取左边的整数字面，同时获取下一个标记。
  left = QWQC_AstPrimary(clx);

  // 如果没有剩余标记，则只返回左节点
  tokentype = clx->token.token;
  if (clx->token.token == Q_T_EOF) {
    return left;
  }

  // 当此标记的优先级大于前一个标记的优先级
  while (QWQC_ExperOpPrecedence(tokentype, clx->line) > ptp) {
    // 读取下一个整数字面
    QWQC_LexerScan(clx);

    // 递归调用 binexpr()，并使用建立子树的令牌的优先级
    right = QWQC_AstBinExpr(clx, OpPrec[tokentype]);

    // 将该子树与我们的子树连接起来。转换token，同时转化为 AST 操作。
    left = QWQC_MakeAstNode(QWQC_AstArithOp(clx, tokentype), left, right, 0);

    // 更新当前标记的详细信息, 如果没有剩余标记，只返回左侧节点
    tokentype = clx->token.token;
    if (tokentype == Q_T_EOF)
      return left;
  }

  // 返回优先级时我们拥有的树是相同或较低的
  return left;
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
