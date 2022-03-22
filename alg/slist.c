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
    slist_t *pos = NULL;
    test_t *tmp = NULL;

    //初始化链表头结点
    SLIST_HEAD(head);
    
    //插入数据
    for (int i = 0; i < 10; i++)
    {
        test_t *test = (test_t *)calloc(1, sizeof(test_t));
        test->value = i + 18;
        slist_add_tail(&test->list, &head);
    }
    
    //遍历数据
    slist_for_each(pos, &head)
    {
        tmp = slist_entry(pos, test_t, list);
        printf("111value = %d\n", tmp->value);
    }

    slist_for_each_entry(tmp, &head, list)
    {
        printf("222value = %d\n", tmp->value);
    }

    return 0;
}
