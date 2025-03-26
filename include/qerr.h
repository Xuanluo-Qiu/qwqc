#ifndef __QWQC_ERR_H__
#define __QWQC_ERR_H__

#include <stdio.h>

#define QWQC_ERR_MAX 5

typedef enum QWQC_ErrorCode {
  QWQC_ERR_OK = 0,
  QWQC_ERR_TOKEN_OK = 1,
  QWQC_ERR_NOT_ENOUGH_ARGV = 2,
  QWQC_ERR_UNKNOWN = 3,
  QWQC_ERR_FILE_OPEN_FAILED = 4,
} QWQC_ErrorCode;

// 错误表
typedef struct ErrorMap {
    QWQC_ErrorCode err;
    char *msg;
} ErrorMap;

extern ErrorMap error_map[QWQC_ERR_MAX+1];

int QWQC_GetError(QWQC_ErrorCode err);

#endif
