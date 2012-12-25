#ifndef OW_COMMON_H
#define OW_COMMON_H


#define OW_STRINGIZE_X(i)   #i
#define OW_STRINGIZE(i)     OW_STRINGIZE_X(i)

#define OW_MIN(a, b)   (((a) > (b)) ? (b) : (a))
#define OW_MAX(a, b)   (((a) < (b)) ? (b) : (a))


#endif // OW_COMMON_H
