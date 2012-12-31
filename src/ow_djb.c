#include "ow_djb.h"


/* Daniel J. Bernstein's DJBX33A */

extern uint32_t   ow_djb_hash_str         (const char *p_key);

extern uint32_t   ow_djb_hash_str_16      (const char *p_key);

extern uint32_t   ow_djb_hash             (const char *p_key,
                                           uint32_t p_len);

extern uint32_t   ow_djb_hash_16          (const char *p_key,
                                           const uint32_t p_len);
 
extern uint32_t   ow_djb_hash_str_v2      (const char *p_key);

extern uint32_t   ow_djb_hash_str_16_v2   (const char *p_key);

extern uint32_t   ow_djb_hash_v2          (const char *p_key,
                                           uint32_t p_len);

extern uint32_t   ow_djb_hash_16_v2       (const char *p_key,
                                           uint32_t p_len);
