#include "ow_djb.h"


/* Daniel J. Bernstein's DJBX33A */

#define OW_DJB_DEFAULT_SEED  5381

extern inline unsigned int   ow_djb_hash_str          (const char *p_key,
                                                       const unsigned int p_seed);

extern inline unsigned int   ow_djb_hash_str_16       (const char *p_key,
                                                       const unsigned int p_seed);

extern inline unsigned int   ow_djb_hash              (const char *p_key,
                                                       const unsigned int p_seed,
                                                       unsigned int p_len);

extern inline unsigned int   ow_djb_hash_16           (const char *p_key,
                                                       const unsigned int p_seed,
                                                       const unsigned int p_len);

extern inline unsigned int   ow_djb2_hash_str_v2      (const char *p_key,
                                                       const unsigned int p_seed);

extern inline unsigned int   ow_djb2_hash_str_16_v2   (const char *p_key,
                                                       const unsigned int p_seed);

extern inline unsigned int   ow_djb2_hash_v2          (const char *p_key,
                                                       const unsigned int p_seed,
                                                       unsigned int p_len);

extern inline unsigned int   ow_djb2_hash_16_v2       (const char *p_key,
                                                       const unsigned int p_seed,
                                                       unsigned int p_len);


