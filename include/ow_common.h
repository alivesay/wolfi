#ifndef OW_COMMON_H
#define OW_COMMON_H

#include <limits.h>
#include <stdint.h>


#define OW_ARRAY_SIZE(a)   (sizeof(a) / sizeof(a[0])

#define OW_STRINGIZE_X(i)   #i
#define OW_STRINGIZE(i)     OW_STRINGIZE_X(i)

#define OW_MIN(a, b)   (((a) > (b)) ? (b) : (a))
#define OW_MAX(a, b)   (((a) < (b)) ? (b) : (a))


inline unsigned int
next_power_of_two(unsigned int p_n, _Bool p_accept_current)
{
  unsigned int i;

  if (p_n < 0) return 0;

  if (!p_accept_current) p_n--;
  
  for (i = 0; i < sizeof(i) << 2; i <<= 1)
    p_n |= (p_n >> i);
  
  return ++p_n;
}


inline unsigned int
prev_power_of_two(unsigned int p_n, _Bool p_accept_current)
{
  unsigned int i;

  if (p_n < 0) return 0;

  if (!p_accept_current) p_n--;

  for (i = 0; i < sizeof(i) << 2; i <<= 1)
    p_n |= (x >> i);

  return p_n - (p_n >> 1);
}


inline _Bool
is_power_of_two(unsigned int p_n)
{
  return p_n > 0 && (p_n & (p_n - 1)) == 0;
}


#endif // OW_COMMON_H
