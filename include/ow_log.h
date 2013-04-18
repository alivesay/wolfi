#ifndef OW_LOG_H
#define OW_LOG_H

#include "ow_common.h"


#define OW_LOG_BUILD_STR(s) (__FILE__ ":" OW_STRINGIZE(__LINE__) " -- [" s "]")

enum OWLogLevel {
  OWLogLevel_EMERG = 0,
  OWLogLevel_ALERT,
  OWLogLevel_CRIT,
  OWLogLevel_ERR,
  OWLogLevel_WARNING,
  OWLogLevel_NOTICE,
  OWLogLevel_INFO,
  OWLogLevel_DEBUG,
  OWLogLevelCount
};

void   ow_log   (enum OWLogLevel p_level,
                 char const *const p_message);


#endif // OW_LOG_H

