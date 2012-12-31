#ifndef OW_TYPES_H
#define OW_TYPES_H

#include <stdint.h>
#include <stdbool.h>


typedef int(*OWCompareFunc)(const void *p_a, const void *p_b);
typedef void(*OWFreeFunc)(const void *p_data);

typedef uint32_t(*OWHashFunc)(const char *const p_string);
typedef uint32_t(*OWHash32StrFunc)(const char *p_key); 
typedef uint32_t(*OWHash32Func)(const char *p_key, uint32_t p_len); 


#endif // OW_TYPES_H
