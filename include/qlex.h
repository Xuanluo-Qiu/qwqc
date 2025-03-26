#ifndef __QWQC_LEX_H__
#define __QWQC_LEX_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "qerr.h"

// Token的类型
enum { Q_T_PLUS, Q_T_MINUS, Q_T_STAR, Q_T_SLASH, Q_T_INTLIT };

// Token的标准结构
struct qwqc_token {
  int token;
  // 我们只需要其中一个，所以使用union
  union {
    int intval;
  };
};

// 封装状态变量
typedef struct QWQC_LexerContext {
    FILE *infile; // File pointer for input file
    int line;     // Line number in the input file
    int putback;  // Putback buffer for tokens
} QWQC_LexerContext;

// 运算符映射表
typedef struct TokenMap {
    char ch;
    int token;
} TokenMap;

extern TokenMap token_map[5];

int QWQC_LexerScan(QWQC_LexerContext *ctx, struct qwqc_token *t);

#endif
