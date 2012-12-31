#include "ow_djb.h"


/* Daniel J. Bernstein's DJBX33A */

extern unsigned int   ow_djb_hash_str         (const char *p_key);

extern unsigned int   ow_djb_hash_str_16      (const char *p_key);

extern unsigned int   ow_djb_hash             (const char *p_key,
                                               unsigned int p_len);

extern unsigned int   ow_djb_hash_16          (const char *p_key,
                                               const unsigned int p_len);
 
extern unsigned int   ow_djb_hash_str_v2      (const char *p_key);

extern unsigned int   ow_djb_hash_str_16_v2   (const char *p_key);

extern unsigned int   ow_djb_hash_v2          (const char *p_key,
                                               unsigned int p_len);

extern unsigned int   ow_djb_hash_16_v2       (const char *p_key,
                                               unsigned int p_len);
