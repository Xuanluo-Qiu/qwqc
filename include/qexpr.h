#ifndef __QWQC_EXPR_H__
#define __QWQC_EXPR_H__

#include "qast.h"
#include "qerr.h"
#include "qlex.h"

// "arithmetic operation" 算术操作
int QWQC_AstArithOp(QWQC_LexerContext *clx);
// "Binary Expression" 返回根为二元运算符的 AST 树
QWQC_AstNode *QWQC_AstBinExpr(QWQC_LexerContext *clx);
// 给定 AST，解释其中的运算符，并返回最终值。
int QWQC_ExprInterPretAst(QWQC_AstNode *node);

#endif
