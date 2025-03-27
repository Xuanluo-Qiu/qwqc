#include "qerr.h"

QWQC_ErrorMap error_map[QWQC_ERR_MAX + 1] = {
    {QWQC_ERR_OK, "NO Error, OK!\n"},
    {QWQC_ERR_TOKEN_OK, "NO Error, Token OK!\n"},
    {QWQC_ERR_NOT_ENOUGH_ARGV, "Error: Not enough arguments!\n"},
    {QWQC_ERR_UNKNOWN, "Error: Unknown error!\n"},
    {QWQC_ERR_FILE_OPEN_FAILED, "Error: File open failed!\n"},
    {QWQC_ERR_MEMORY_ALLOCATION_FAILED, "From %s.\n Error: Memory allocation failed!\n"},
    {QWQC_ERR_TOKEN_UNKNOWN, "Error: Token unknown!\n"},
    {QWQC_ERR_SYNTAX, "Error: Syntax error on line %d!\n"},
    {QWQC_ERR_UNKNOWN_AST_OP, "Error: Unknown AST operator, line: %d.\n"},
    {QWQC_ERR_MAX, "END"} // 结束标记
};

int QWQC_GetError(QWQC_ErrorCode err, ...) {
  va_list args;
  va_start(args, err);

  for (int i = 0; error_map[i].err != QWQC_ERR_MAX; i++) {
    if (error_map[i].err == err) {
      vprintf(error_map[i].msg, args);
      va_end(args);
      return err;
    }
  }

  vprintf(error_map[QWQC_ERR_MAX].msg, args);

  va_end(args);
  return QWQC_ERR_UNKNOWN;
}
