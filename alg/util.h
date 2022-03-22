#ifndef _UTIL_H_
#define _UTIL_H_

/**
 * @brief 计算结构体成员与起始地址之间的偏移量
 * 
 * @param type   结构体类型
 * @param member 成员变量名字
 * 
 * 通过结构体类型和成员变量名字计算出成员变量的偏移地址。
 */
#define offset(type, member) \
    ((size_t)(&((type *)0)->member))

/**
 * @brief 计算结构体起始地址
 * 
 * @param ptr    成员变量指针
 * @param type   结构体类型
 * @param member 成员变量名字
 * 
 * 计算结构体成员与起始地址之间的偏移量，再将实际成员变量指针减去偏移地址，
 * 得到结构体起始地址。
 */
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)(&((type *)0)->member)))

#endif //_UTIL_H_
