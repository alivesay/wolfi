#ifndef OW_DJB_H
#define OW_DJB_H


/* Daniel J. Bernstein's DJBX33/DJBX33A 
 *
 * 'str' functions require NULL-terminated p_key 
 *
 * '16' functions have better distribution for letters w/ tables lengths <= 2^16
 *
 * 'v2' functions use XOR for improved distribution
 */

#define OW_DJB_HASH_SEED  5381

inline uint32_t
ow_djb_hash_str(const char *p_str)
{
  uint32_t hash = OW_DJB_HASH_SEED;
  
  while (*p_str)
    hash = ((hash << 5) + hash) + *p_str++;

  return hash;
}


inline uint32_t
ow_djb_hash_str_16(const char *p_str)
{
  uint32_t hash = ow_djb_hash_str(p_str);

  return (int)(hash ^ (hash >> 16));
}


inline uint32_t
ow_djb_hash(const char *p_str,
            uint32_t p_len)
{
  uint32_t hash = OW_DJB_HASH_SEED;

  while (p_len--)
    hash = ((hash << 5) + hash) + p_str[p_len];

  return hash;
}


inline uint32_t
ow_djb_hash_16(const char *p_str,
               uint32_t p_len)
{
  uint32_t hash = ow_djb_hash(p_str, p_len);

  return (int)(hash ^ (hash >> 16));
}


inline uint32_t
ow_djb_hash_str_v2(const char *p_str)
{
  uint32_t hash = OW_DJB_HASH_SEED;

  while (*p_str)
    hash = ((hash << 5) + hash) ^ *p_str++;

  return hash;
}


inline uint32_t
ow_djb_hash_str_16_v2(const char *p_str)
{
  uint32_t hash = ow_djb_hash_str_v2(p_str);

  return (int)(hash ^ (hash >> 16));
}


inline uint32_t
ow_djb_hash_v2(const char *p_str,
               uint32_t p_len)
{
  uint32_t hash = OW_DJB_HASH_SEED;

  while (p_len--)
    hash = ((hash << 5) + hash) ^ p_str[p_len];

  return hash;
}


inline uint32_t
ow_djb_hash_16_v2(const char *p_str,
                  uint32_t p_len)
{
  uint32_t hash = ow_djb_hash_v2(p_str, p_len);

  return (int)(hash ^ (hash >> 16));
}


#endif // OW_DJB_H
