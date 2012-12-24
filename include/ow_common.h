#ifndef OW_COMMON_H
#define OW_COMMON_H


#define OW_STRINGIZE_X(i) #i
#define OW_STRINGIZE(i) OW_STRINGIZE_X(i)

#define OW_BUILD_LOG_STR(s) (__FILE__ ":" OW_STRINGIZE(__LINE__) " -- [" s "]")


#endif // OW_COMMON_H
