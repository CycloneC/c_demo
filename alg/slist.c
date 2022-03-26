#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "slist.h"

typedef struct _test
{
    slist_t list;
    int value;
} test_t;

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    int len = 0;
    slist_t *pos = NULL;
    test_t *tmp = NULL;

    //初始化链表头结点
    SLIST_HEAD(head);
    
    //插入数据：尾插
    for (int i = 0; i < 3; i++)
    {
        test_t *test = (test_t *)calloc(1, sizeof(test_t));
        test->value = i + 10;
        slist_add_tail(&test->list, &head);
    }

    //遍历数据方式1
    printf("first for each: [ ");
    slist_for_each(pos, &head)
    {
        tmp = slist_entry(pos, test_t, list);
        printf("%d ", tmp->value);
    }
    printf("]\n");
    
    //插入数据：头插
    for (int i = 0; i < 3; i++)
    {
        test_t *test = (test_t *)calloc(1, sizeof(test_t));
        test->value = i + 20;
        slist_add(&test->list, &head);
    }

    //获取链表长度
    len = slist_len(&head);
    printf("list len = %d\n", len);

    //遍历数据方式2
    printf("second for each: [ ");
    slist_for_each_entry(tmp, &head, list)
    {
        printf("%d ", tmp->value);
    }
    printf("]\n");

    //遍历删除所有链表
    while (pos = head.next)
    {
        head.next = head.next->next;

        tmp = container_of(pos, test_t, list);
        free(tmp);
    }

    //判断链表是否为空
    if (slist_is_empty(&head))
    {
        printf("list is empty\n");
    }
    else
    {
        printf("list is not empty\n");
    }
    
    return 0;
}
