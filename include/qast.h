#ifndef __QWQC_AST_H__
#define __QWQC_AST_H__

#include <stdio.h>
#include <stdlib.h>

#include "qerr.h"
#include "qlex.h"

// AST节点类型
typedef enum QWQC_AstType {
  Q_A_ADD,
  Q_A_SUBTRACT,
  Q_A_MULTIPLY,
  Q_A_DIVIDE,
  Q_A_INTLIT
} QWQC_AstType;

// 抽象语法树结构
typedef struct QWQC_AstNode {
  int op;                     // "Operation"，即操作
  struct QWQC_AstNode *left;  // 左子节点
  struct QWQC_AstNode *right; // 右子节点
  int intval;                 // 整数类型
} QWQC_AstNode;

// AST运算符映射表
typedef struct QWQC_AstMap {
  QWQC_AstType ast_type;
  QWQC_TokenType token_type;
} QWQC_AstMap;

// AST运算符映射表
extern QWQC_AstMap ast_map[5];

QWQC_AstNode *QWQC_MakeAstNode(); // 创建一个空的AST节点
QWQC_AstNode *QWQC_MakeAstLeaf(int op, int intval); // 创建一个叶子节点
QWQC_AstNode *QWQC_MakeAstUnary(int op, QWQC_AstNode *left,
                                int intval); // 创建一个一元操作节点

#endif
