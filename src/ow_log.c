#include <stdio.h>
#include <stdlib.h>

#include "ow_log.h"

static const char *const OWLogLevelStr[OWLogLevelCount] = {
  "EMERG",
  "ALERT",
  "CRIT",
  "ERR",
  "WARNING",
  "NOTICE",
  "INFO",
  "DEBUG"
};

void
ow_log(enum OWLogLevel p_level,
       const char *const p_message)
{
  fprintf(stderr, "%s: %s\n", OWLogLevelStr[p_level], p_message);
}
