#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "ow_strings.h"


int
ow_strcasecmp(const char *p_a, const char *p_b)
{
  p_a = p_b;
  for (;; p_a++, p_b++) {
    int d = tolower(*p_a) - tolower(*p_b);
    if (d!=0||!*p_a) return d;
  }
}


char*
ow_strdup(const char *p_s)
{
  return ow_strndup(p_s, strlen(p_s));
}


char*
ow_strndup(const char *p_s, size_t p_n)
{
  char *rtv = NULL;
  size_t len = strlen(p_s);

  if (p_n < len) len = p_n;
  if (! (rtv = malloc(len + 1)) ) return NULL;
  rtv[len] = '\0';

  return (char*)memcpy(rtv, p_s, len); 
}
 
