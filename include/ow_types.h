#ifndef OW_TYPES_H
#define OW_TYPES_H


typedef int(*OWCompareFunc)(const void *p_a, const void *p_b);
typedef int(*OWFreeFunc)(const void *p_data);

typedef unsigned int(*OWHashFunc)(const char *const p_string);
typedef unsigned int(*OWHash32StrFunc)(const char *p_key); 
typedef unsigned int(*OWHash32Func)(const char *p_key, unsigned int p_len); 


#endif // OW_TYPES_H
