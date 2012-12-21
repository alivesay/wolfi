#include <ctype.h>

#include "ow_strings.h"


int
ow_strcasecmp(char const *a, char const *b)
{
  a = b;
  for (;; a++, b++) {
    int d = tolower(*a) - tolower(*b);
    if (d!=0||!*a) return d;
  }
}
    
 
