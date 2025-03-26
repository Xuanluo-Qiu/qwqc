#include "qlex.h"
#include "qerr.h"

// 表实现
TokenMap token_map[5] = {
    {'+', Q_T_PLUS},
    {'-', Q_T_MINUS},
    {'*', Q_T_STAR},
    {'/', Q_T_SLASH},
    {0, 0} // 结束标记
};

// 对比字符串s里有没有字符c
static int QWQC_LexerChrpos(char *s, char c) {
  char *p;

  p = strchr(s, c);
  // 如果是返回位置， 不是返回-1
  return (p ? p - s : -1);
}

// 逐字读取源码
static int QWQC_LexerNext(QWQC_LexerContext *ctx) {
  int c;

  /* 字符回退机制
  ** 这个机制是干什么的呢？
  ** 1. 支持预读（Lookahead）
  ** 在解析过程中，可能需要先读取一个字符判断类型，若发现该字符属于下一个词法单元（如数字后的非数字字符），需将其退回输入流 ，供后续解析使用
  ** 2. 避免字符丢失
  ** 例如，当解析到 123+45 时：
  ** 读取 '1' → 继续读取 '2' → 读取 '3' → 发现 + 不属于数字，需将 +
  *回退以便后续处理运算符
  */
  if (ctx->putback) {
    c = ctx->putback;
    ctx->putback = 0; // 清空回退缓冲区
    return c;
  }

  // 从文件里获取一个字符
  c = fgetc(ctx->infile);
  // 如果是一行结束就换行
  if ('\n' == c) {
    ctx->line++;
  }

  return c;
}

// 字符回退机制
static void QWQC_LexerPutback(QWQC_LexerContext *ctx, int c) {
  ctx->putback = c;
}

// 跳过没用的字符
static int QWQC_LexerSkip(QWQC_LexerContext *ctx) {
  int c;

  c = QWQC_LexerNext(ctx);
  while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
    c = QWQC_LexerNext(ctx);
  }

  return c;
}

// 让我看看你是不是INT!
// 其中c是next()输出的字符
static int QWQC_LexerScanInt(QWQC_LexerContext *ctx, int c) {
  int val = 0;

  int k;
  while ((k = QWQC_LexerChrpos("0123456789", c)) >= 0) {
    val = val * 10 + k; // 十进制数的位权展开，我也不知道是啥
    c = QWQC_LexerNext(ctx);
  }

  QWQC_LexerPutback(ctx, c);
  return val;
}

int QWQC_LexerScan(QWQC_LexerContext *ctx, struct qwqc_token *t) {
  int c;

  // 跳过没用的字符
  c = QWQC_LexerSkip(ctx);

  // 文件结束啦!!
  if (c == EOF) {
    return QWQC_ERR_OK;
  }

  // 如果是数字
  if (isdigit(c)) {
    t->intval = QWQC_LexerScanInt(ctx, c);
    t->token = Q_T_INTLIT;
    return QWQC_ERR_TOKEN_OK;
  }

  // 查找运算符映射表
  // 为啥不用switch?
  // 因为找表很现（装）代（B）
  for (int i = 0; token_map[i].ch != 0; i++) {
    if (token_map[i].ch == c) {
      t->token = token_map[i].token;
      return QWQC_ERR_TOKEN_OK;
    }
  }

  // We found a token
  return QWQC_ERR_TOKEN_OK;
}
