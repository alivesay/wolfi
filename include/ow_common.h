#ifndef OW_COMMON_H
#define OW_COMMON_H

#include <limits.h>
#include <stdlib.h>

#include "ow_log.h"
#include "ow_types.h"


#define OW_MALLOC(var, size)                                         \
  do {                                                               \
    var = malloc(size);                                              \
    if (!var)                                                        \
      ow_log(OWLogLevel_EMERG, OW_LOG_BUILD_STR("malloc() failed")); \
  }  while(0)

#define OW_CALLOC(var, nmemb, size)                                  \
  do {                                                               \
    var = calloc(nmemb, size);                                       \
    if (!var)                                                        \
      ow_log(OWLogLevel_EMERG, OW_LOG_BUILD_STR("calloc() failed")); \
  } while(0)

#define OW_FREE(var) \
  do {               \
    free(var);       \
    var = NULL;      \
  } while(0)

#define OW_ARRAY_SIZE(a)   (sizeof(a) / sizeof(a[0])

#define OW_STRINGIZE_X(i)   #i
#define OW_STRINGIZE(i)     OW_STRINGIZE_X(i)

#define OW_MIN(a, b)   (((a) > (b)) ? (b) : (a))
#define OW_MAX(a, b)   (((a) < (b)) ? (b) : (a))


inline uint32_t
next_power_of_two(uint32_t p_n,
                  bool p_accept_current)
{
  uint32_t i;

  if (p_n < 0) return 0;

  if (!p_accept_current) p_n--;
  
  for (i = 0; i < sizeof(i) << 2; i <<= 1)
    p_n |= (p_n >> i);
  
  return ++p_n;
}


inline uint32_t
prev_power_of_two(uint32_t p_n,
                  bool p_accept_current)
{
  uint32_t i;

  if (p_n < 0) return 0;

  if (!p_accept_current) p_n--;

  for (i = 0; i < sizeof(i) << 2; i <<= 1)
    p_n |= (p_n >> i);

  return p_n - (p_n >> 1);
}


inline bool
is_power_of_two(uint32_t p_n)
{
  return p_n > 0 && (p_n & (p_n - 1)) == 0;
}


#endif // OW_COMMON_H
