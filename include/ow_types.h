#ifndef OW_TYPES_H
#define OW_TYPES_H

typedef int(*OWCompareFunc)(void const *p_a, void const *p_b);
typedef int(*OWFreeFunc)(void const *p_data);
typedef unsigned int(*OWHashFunc)(char const *const p_string);

#endif // OW_TYPES_H
