#include <stdio.h>
#include <stdlib.h>

#include "ow_log.h"

static char const OWLogLevelStr[OWLogLevelCount] = {
  "EMERG",
  "ALERT",
  "CRIT",
  "ERR",
  "WARNING",
  "NOTICE",
  "INFO",
  "DEBUG"
};

inline void
ow_log(char const *const p_message)
{
  fprintf(stderr, "%s: %s\n", OWLogLevelStr[p_level], p_message);
}
