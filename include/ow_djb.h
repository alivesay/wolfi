#ifndef OW_DJB_H
#define OW_DJB_H


/* Daniel J. Bernstein's DJBX33A */

#define OW_DJB_DEFAULT_SEED  5381

inline unsigned int
ow_djb_hash_str(const char *p_key,
                const unsigned int p_seed)
{
  unsigned int hash = p_seed;
  
  while (*p_key)
    hash = ((hash << 5) + hash) + *p_key++;

  return hash;
}


inline unsigned int
ow_djb_hash_str_16(const char *p_key,
                   const unsigned int p_seed)
{
  unsigned int hash = ow_djb_hash_str(p_key, p_seed);

  return (hash ^ (hash >> 16));
}


inline unsigned int
ow_djb_hash(const char *p_key,
            const unsigned int p_seed,
            unsigned int p_len)
{
  unsigned int hash = p_seed;

  while (p_len--)
    hash = ((hash << 5) + hash) + p_key[p_len];

  return hash;
}


inline unsigned int
ow_djb_hash_16(const char *p_key,
               const unsigned int p_seed,
               unsigned int p_len)
{
  unsigned int hash = ow_djb_hash(p_key, p_seed, p_len);

  return hash ^ (hash >> 16);
}


inline unsigned int
ow_djb_hash_str_v2(const char *p_key,
                   const unsigned int p_seed)
{
  unsigned int hash = p_seed;

  while (*p_key)
    hash = ((hash << 5) + hash) ^ *p_key++;

  return hash;
}


inline unsigned int
ow_djb_hash_str_16_v2(const char *p_key,
                      const unsigned int p_seed)
{
  unsigned int hash = ow_djb_hash_str_v2(p_key, p_seed);

  return hash ^ (hash >> 16);
}


inline unsigned int
ow_djb_hash_v2(const char *p_key,
               const unsigned int p_seed,
               unsigned int p_len)
{
  unsigned int hash = p_seed;

  while (p_len--)
    hash = ((hash << 5) + hash) ^ p_key[p_len];

  return hash;
}


inline unsigned int
ow_djb_hash_16_v2(const char *p_key,
                  const unsigned int p_seed,
                  unsigned int p_len)
{
  unsigned int hash = ow_djb_hash_v2(p_key, p_seed, p_len);

  return hash ^ (hash >> 16);
}


#endif // OW_DJB_H
