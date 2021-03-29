#include <stdarg.h>
#include <string.h>
#include <stdio.h>    
#include <ctype.h>
#include <stdlib.h>

#ifdef SANGFOR_DEBUG
    #define    STRSAFE_ASSERT(expression) do{ \
            if (!(expression)) { \
                fprintf(stderr, \
                    "assertion \"%s\" failed: file \"%s\", line %d\n", \
                    #expression, \
                    __FILE__, __LINE__); \
                abort(); \
            } \
        }while(0)
#else  /* Release version */
    #define    STRSAFE_ASSERT(expression)   do{}while(0)
#endif
    
#ifdef __cplusplus
extern "C" {
#endif

#define SANGFOR_TRUNC ((size_t)-1)

/**
 *    字符串连接。时间复杂度O(m + n), m和n分别为目的串和源串长度
 *    strcat_n保证缓冲区内字符串以0结尾，除非size == 0
 *    @dst:     目的字符串地址
 *    @size:    目的字符串缓冲区总长度
 *    @src:     源字符串地址
 *    @return    < 0 时表示缓冲区长度不够用，已作截断处理
 */
int strcat_n(char *dst, size_t size, const char *src);

#ifdef __cplusplus
}
#endif

static int strcat_n0(char *dst, size_t size, const char *src)
{    
    STRSAFE_ASSERT(dst && src);
    STRSAFE_ASSERT((dst < src && (dst + size) < src) 
        || (dst > src && (src + size) < dst));
        
    size_t dst_len = strlen(dst);
    if (!size || dst_len >= size - 1) {
        return -1;
    }
    
    //由于不同的C库strncat处理空间不足时有不同的行为，这里算出长度后memcpy
    size_t src_len = strlen(src);
    size_t rest = size - dst_len;
    
    if(rest > src_len){
        memcpy(dst + dst_len, src, src_len);
        dst[dst_len + src_len] = '\0';
        return 0;
    }else{
        memcpy(dst + dst_len, src, rest - 1);
        dst[size - 1] = '\0';
        return -1;
    }
   
   //return strcpy_n(dst + dst_len, size - dst_len, src);
}
static int strcat_n1(char *dst, size_t size, const char *src)
{  
    return 0;
}

static int strcat_n2(char *dst, size_t size, const char *src)
{  
    return 0;
}

static int strcat_n3(char *dst, size_t size, const char *src)
{  
    return 0;
}


/**
 *    字符串连接。时间复杂度O(m + n), m和n分别为目的串和源串长度
 *    strcat_n保证缓冲区内字符串以0结尾，除非size == 0
 *    @dst:     目的字符串地址
 *    @size:    目的字符串缓冲区总长度
 *    @src:     源字符串地址
 *    @return    < 0 时表示缓冲区长度不够用，已作截断处理
 */
typedef int (*fn_strcat_n)(char *dst, size_t size, const char *src);

#define OJ_RUN_ROUND_NUM 4

int strcat_n(char *dst, size_t size, const char *src)
{
    static fn_strcat_n funcs[OJ_RUN_ROUND_NUM] = {
        strcat_n0,
        strcat_n1,
        strcat_n2,
        strcat_n3,
    };

    return funcs[s_run_round](dst, size, src);
}

