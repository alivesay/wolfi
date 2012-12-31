#ifndef OW_TYPES_H
#define OW_TYPES_H

typedef int(*OWCompareFunc)(void const *p_a, void const *p_b);
typedef int(*OWFreeFunc)(void const *p_data);

typedef unsigned int(*OWHashFunc)(char const *const p_string);
typedef unsigned int(*OWHash32StrFunc)(const char *p_key); 
typedef unsigned int(*OWHash32Func)(const char *p_key, unsigned int p_len); 

#endif // OW_TYPES_H
