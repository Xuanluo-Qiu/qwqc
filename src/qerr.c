#include "qerr.h"

ErrorMap error_map[QWQC_ERR_MAX+1] = {
    {QWQC_ERR_OK, "NO Error, OK!"},
    {QWQC_ERR_TOKEN_OK, "NO Error, Token OK!"},
    {QWQC_ERR_NOT_ENOUGH_ARGV, "Error: Not enough arguments!"},
    {QWQC_ERR_UNKNOWN, "Error: Unknown error!"},
    {QWQC_ERR_FILE_OPEN_FAILED, "Error: File open failed!"},
    {QWQC_ERR_MAX, "END"} // 结束标记
};


int QWQC_GetError(QWQC_ErrorCode err) {
  for (int i = 0; error_map[i].err != QWQC_ERR_MAX; i++) {
    if (error_map[i].err == err) {
      printf("%s\n", error_map[i].msg);
      return err;
    }
  }

  printf("%s\n", error_map[QWQC_ERR_MAX].msg);
  return QWQC_ERR_UNKNOWN;
}
