#ifndef _SLIST_H_
#define _SLIST_H_

#include "util.h"

typedef struct _slist
{
    struct _slist *next;
} slist_t;

/**
 * @brief 初始化一个名为name的单链表结构体
 * 
 * @param name 节点名
 */
#define SLIST_HEAD(name) \
    slist_t name = {NULL}

static inline void INIT_SLIST_HEAD(slist_t *list)
{
    list->next = NULL;
}

/**
 * @brief 指定节点后插入节点
 * 
 * @param new  新插入的节点
 * @param node 指定节点
 */
static inline void __slist_add(slist_t *new, slist_t *node)
{
    new->next = node->next;
    node->next = new;
}

/**
 * @brief 头部插入节点
 * 
 * @param new  新插入的节点
 * @param head 头节点
 */
static inline void slist_add(slist_t *new, slist_t *head)
{
    __slist_add(new, head);
}

/**
 * @brief 尾部插入节点
 * 
 * @param new  新插入的节点
 * @param head 头节点
 */
static inline void slist_add_tail(slist_t *new, slist_t *head)
{
    while (head->next) head = head->next;
    __slist_add(new, head);
}

/**
 * @brief 删除指定节点后的节点
 * 
 * @param node  指定节点
 */
static inline void __slist_del(slist_t *node)
{
    if (node->next) node->next = node->next->next;
}

/**
 * @brief 删除指定节点
 * 
 * @param node  指定节点
 * @param head  头节点
 */
static inline void slist_del(slist_t *node, slist_t *head)
{
    while (head->next)
    {
        if (head->next == node) 
        {
            __slist_del(head);
            break;
        }
        head = head->next;
    }

    node->next = NULL;
}

/**
 * @brief 删除尾部节点
 * 
 * @param head 头节点
 */
static inline void slist_del_tail(slist_t *head)
{
    while (head->next) 
    {
        if (head->next->next == NULL)
        {
            __slist_del(head);
            break;
        }
        head = head->next;
    }
}

/**
 * @brief 获取链表长度
 * 
 * @param head 头节点
 */
static inline int slist_len(slist_t *head)
{
    int len = 0;

    while (head->next)
    {
        len++;
        head = head->next;
    }
    
    return len;
}

/**
 * @brief 判断链表是否为空
 * 
 * @param head 头节点
 */
static inline int slist_is_empty(slist_t *head)
{
    return head->next == NULL;
}

/**
 * @brief 遍历单链表
 * 
 * @param pos    循环指针，指向链表
 * @param head   头节点
 */
#define slist_for_each(pos, head) \
    for (pos = (head)->next; pos != NULL; pos = pos->next)

/**
 * @brief 获取type类型结构体的起始地址
 * 
 * @param ptr    成员变量指针
 * @param type   结构体类型
 * @param member 结构体中链表成员的变量名字
 */
#define slist_entry(node, type, member) \
    container_of(node, type, member)

/**
 * @brief 获取链表第一个元素的结构体起始地址
 * 
 * @param ptr    头节点指针
 * @param type   结构体类型
 * @param member 结构体中链表成员的变量名字
 */
#define slist_first_entry(ptr, type, member) \
    slist_entry((ptr)->next, type, member)

/**
 * @brief 获取当前结构体元素下一个结构体起始地址
 * 
 * @param ptr    结构体指针
 * @param member 结构体中链表成员的变量名字
 */
#define slist_next_entry(pos, member) \
    slist_entry((pos)->member.next, typeof(*pos), member)

/**
 * @brief 遍历单链表
 * 
 * @param pos    循环指针，指向元素结构体起始地址
 * @param head   头节点
 * @param member 结构体中链表成员的变量名字
 */
#define slist_for_each_entry(pos, head, member) \
    for (pos = slist_first_entry(head, typeof(*pos), member); \
            &pos->member.next != NULL; \
            pos = slist_next_entry(pos, member))

#endif //_SLIST_H_
