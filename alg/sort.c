#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "time.h"

#define SWAP(a, b) {(a) = (a) ^ (b); (b) = (a) ^ (b); (a) = (a) ^ (b);}
#define CHECK(nums, numsSize) {if ((nums == NULL) || numsSize < 2) return;}

typedef enum 
{
    SORT_C_LIB = 0,
    SORT_BUBBLE,
    SORT_SELECT,
    SORT_INSERT,
    SORT_SHELL,
    SORT_MERGE,
    SORT_QUICK,
    SORT_HAEP,
    SORT_COUNT,
    SORT_BUCKET,
    SORT_RADIX,
} sort_type_t;

void print_nums(int *nums, int numsSize)
{
    printf("[ ");
    for (int i = 0; i < numsSize; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("]\n");
}

/**
 * @description: qsort回调函数
 * @param {void*} a
 * @param {void*} b
 * @return {*}  返回值小于0，a排在b左边
 *              返回值等于0，a和b顺序不确定
 *              返回值大于0，a排在b右边
 */
int cmp_int(const void *a , const void *b)
{
    return *(int*)a - *(int*)b; //升序
}

/**
 * @description: 冒泡排序
 * @param {int} *nums
 * @param {int} numsSize
 * @return {*}
 */
void sort_bubble(int *nums, int numsSize)
{
    bool is_swap = false;

    CHECK(nums, numsSize);

    for (int i = 0; i < numsSize - 1; i++)
    {
        is_swap = false;

        for (int j = 1; j < numsSize - i; j++)
        {
            if (nums[j] < nums[j - 1])
            {
                SWAP(nums[j], nums[j - 1]);
                is_swap = true;
            }
        }

        if (!is_swap)
        {
            return;
        }
    }
}

/**
 * @description: 选择排序
 * @param {int} *nums
 * @param {int} numsSize
 * @return {*}
 */
void sort_select(int *nums, int numsSize)
{
    int index;

    CHECK(nums, numsSize);

    for (int i = 0; i < numsSize - 1; i++)
    {
        index = 0;
        for (int j = 1; j < numsSize - i; j++)
        {
            if (nums[j] > nums[index])
            {
                index = j;
            }
        }

        if (index != numsSize - i - 1) //注意此处判断，如果两者相等，则表示同一变量，同一变量不能使用SWAP交互函数，除非使用带参数的交互函数
        {
            SWAP(nums[index], nums[numsSize - i - 1]);
        }
    }
}

/**
 * @description: 插入排序
 * @param {int} *nums
 * @param {int} numsSize
 * @return {*}
 */
void sort_insert(int *nums, int numsSize)
{
    int temp;

    CHECK(nums, numsSize);

    for (int i = 1; i < numsSize; i++)
    {
        temp = nums[i];
        int j = i;
        while (j > 0 && temp < nums[j - 1])
        {
            nums[j] = nums[j - 1];
            j--;
        }
        
        if (j != i)
        {
            nums[j] = temp;
        }
    }
}

/**
 * @description: 希尔排序
 * @param {int} *nums
 * @param {int} numsSize
 * @return {*}
 */
void sort_shell(int *nums, int numsSize)
{
    int temp;
    int gap = numsSize >> 1;

    CHECK(nums, numsSize);
    
    while (gap > 0)
    {
        for (int i = gap; i < numsSize; i++)
        {
            temp = nums[i];
            int j = i;
            while ((j - gap) >= 0 && temp < nums[j - gap])
            {
                nums[j] = nums[j - gap];
                j -= gap;
            }
            
            if(j != i)
            {
                nums[j] = temp;
            }
        }

        gap = gap >> 1;
    }
}

/**
 * @description: 归并排序--递归函数
 * @param {int} *nums
 * @param {int} numsSize
 * @return {*}
 */

void sort_merge_recursion(int *nums, int *temp, int left, int right)
{
    int index, left1, right1, left2, right2;

    if (right <= left)
    {
        return;
    }

    left1 = left;
    right1 = ((right - left) >> 1) + left;
    left2 = right1 + 1;
    right2 = right;
    sort_merge_recursion(nums, temp, left1, right1);
    sort_merge_recursion(nums, temp, left2, right2);

    index = 0;
    while (left1 <= right1 && left2 <= right2)
    {
        temp[index++] = nums[left1] > nums[left2] ? nums[left2++] : nums[left1++];
    }

    while (left1 <= right1)
    {
        temp[index++] = nums[left1++];
    }
        
    while (left2 <= right2)
    {
        temp[index++] = nums[left2++];
    }

    memcpy(nums + left, temp, index * sizeof(int));
}

/**
 * @description: 归并排序--主函数
 * @param {int} *nums
 * @param {int} numsSize
 * @return {*}
 */
void sort_merge(int *nums, int numsSize)
{
    CHECK(nums, numsSize);

    int *temp = (int *)calloc(numsSize, sizeof(int));
    sort_merge_recursion(nums, temp, 0, numsSize - 1);
    free(temp);
}

/**
 * @description: 快速排序--递归函数
 * @param {int} *nums
 * @param {int} numsSize
 * @return {*}
 */
void sort_quick_recursion(int *nums, int start, int end)
{
    int key, left, right;

    if (start < end)
    {
        key = nums[start];
        left = start;
        right = end;
        while (left < right)
        {
            while (nums[right] >= key && left < right)
            {
                right--;
            }
            
            if (left < right)
            {
                nums[left++] = nums[right];
            }
            
            while (nums[left] < key && left < right)
            {
                left++;
            }

            if (left < right)
            {
                nums[right--] = nums[left];
            }
        }

        nums[left] = key;
        sort_quick_recursion(nums, start, left - 1);
        sort_quick_recursion(nums, left + 1, end);
    }
}

/**
 * @description: 快速排序--主函数
 * @param {int} *nums
 * @param {int} numsSize
 * @return {*}
 */
void sort_quick(int *nums, int numsSize)
{
    CHECK(nums, numsSize);

    sort_quick_recursion(nums, 0, numsSize - 1);
}

void sort_heap_adjust(int *nums, int start, int end)
{
    int dad, son;

    dad = start;
    son = dad * 2 + 1;
    while (son <= end)
    {
        if ((son + 1 <= end) && (nums[son] < nums[son + 1])) //取两个子节点最大的一个
        {
            son++;
        }

        if (nums[dad] > nums[son])
        {
            return;
        }

        SWAP(nums[dad], nums[son]);
        dad = son;
        son = dad * 2 + 1;
    }
}

/**
 * @description: 堆排序
 * @param {int} *nums
 * @param {int} numsSize
 * @return {*}
 */
void sort_heap(int *nums, int numsSize)
{
    CHECK(nums, numsSize);

    for (int i = (numsSize / 2 - 1); i >= 0; i--)
    {
        sort_heap_adjust(nums, i, numsSize - 1);
    }

    for (int i = 0; i < numsSize - 1; i++)
    {
        SWAP(nums[numsSize - 1 - i], nums[0]);
        sort_heap_adjust(nums, 0, numsSize - 2 - i);
    }
}

/**
 * @description: 计数排序
 * @param {int} *nums
 * @param {int} numsSize
 * @return {*}
 */
void sort_count(int *nums, int numsSize)
{
    int max = nums[0], min = nums[0];

    CHECK(nums, numsSize);
    
    for (int i = 1; i < numsSize; i++)
    {
        if (nums[i] > max)
        {
            max = nums[i];
        }

        if (nums[i] < min)
        {
            min = nums[i];
        }
    }
    
    int count = max - min + 1;
    int *array = (int *)calloc(count, sizeof(int));

    for (int i = 0; i < numsSize; i++)
    {
        int pos = nums[i] - min;
        array[pos]++;
    }

    int index = 0;
    for (int i = 0; i < count; i++)
    {
        while (array[i] > 0)
        {
            nums[index++] = i + min;
            array[i]--;
        }
    }

    free(array);
}

typedef struct _bucket_item
{
    int data;
    struct _bucket_item *next;
}bucket_item_t;

static void _list_insert(bucket_item_t *head, int value)
{
    bucket_item_t *item = calloc(1, sizeof(bucket_item_t));
    item->data = value;

    while (head->next)
    {
        if (value < head->next->data)
        {
            break;
        }

        head = head->next;
    }

    if (head->next == NULL)
    {
        head->next = item;
        return;
    }

    item->next = head->next;
    head->next = item;
}

/**
 * @description: 桶排序
 * @param {int} *nums
 * @param {int} numsSize
 * @return {*}
 */
void sort_bucket(int *nums, int numsSize)
{
    int max = nums[0], min = nums[0];

    CHECK(nums, numsSize);
    
    //获取最大值和最小值
    for (int i = 1; i < numsSize; i++)
    {
        if (nums[i] > max)
        {
            max = nums[i];
        }

        if (nums[i] < min)
        {
            min = nums[i];
        }
    }

    //计算桶大小和桶个数，初始化桶队列
    int bucket_size = (max - min) / numsSize + 1;
    int bucket_count = (max - min) / bucket_size + 1;
    bucket_item_t *bucket_head = (bucket_item_t *)calloc(bucket_count, sizeof(bucket_item_t));
    
    //将序列分配到桶中
    for (int i = 0; i < numsSize; i++)
    {
        int bucket_index = (nums[i] - min) / bucket_size;

        /* 根据大小插入到链表中 */
        _list_insert(&bucket_head[bucket_index], nums[i]);
    }

    //将桶中的数据还原到序列中
    int index = 0;
    for (int i = 0; i < bucket_count; i++)
    {
        bucket_item_t *head = &bucket_head[i];

        while (head->next)
        {
            nums[index++] = head->next->data;
            head = head->next;
        }
    }

    //释放内存
    for (int i = 0; i < bucket_count; i++)
    {
        bucket_item_t *head = &bucket_head[i];

        head = head->next;
        while (head)
        {
            bucket_item_t *temp = head;
            head = head->next;
            free(temp);
        }
    }
    free(bucket_head);
}

/**
 * @description: 基数排序
 * @param {int} *nums
 * @param {int} numsSize
 * @return {*}
 */
void sort_radix(int *nums, int numsSize)
{
    int max = nums[0];
    int width = 0;

    CHECK(nums, numsSize);
    
    //获取最大值和最小值
    for (int i = 1; i < numsSize; i++)
    {
        if (nums[i] > max)
        {
            max = nums[i];
        }
    }

    //获取位宽
    while (max /= 10)
    {
        width++;
    }

    //初始化10个桶，序号0~9
    bucket_item_t *bucket_head = (bucket_item_t *)calloc(10, sizeof(bucket_item_t));
    
    for (int i = 0; i <= width; i++)
    {
        int pow = 1;
        for (int j = 0; j < i; j++)
        {
            pow *= 10;
        }

        //将数据存放到桶中
        for (int j = 0; j < numsSize; j++)
        {
            int bucket_index = nums[j] / pow % 10;
            _list_insert(&bucket_head[bucket_index], nums[j]);
        }

        //将桶中数据存放到序列中
        int index = 0;
        for (int j = 0; j < 10; j++)
        {
            bucket_item_t *head = &bucket_head[j];

            while (head->next)
            {
                nums[index++] = head->next->data;
                head = head->next;
            }
        }

        //释放内存
        for (int j = 0; j < 10; j++)
        {
            bucket_item_t *head = &bucket_head[j];

            head = head->next;
            while (head)
            {
                bucket_item_t *temp = head;
                head = head->next;
                free(temp);
            }

            bucket_head[j].next = NULL;
        }
    }
    
    free(bucket_head);
}

int main(int argc, char const *argv[])
{
    int numsSize;
    int *nums = NULL;
    int *nums_cmp = NULL;

    //随机初始化测试序列
    srand(time(NULL));
    numsSize = 0;//rand() % 100; //序列长度0 ~ 99
    if (numsSize)
    {
        nums = (int *)calloc(numsSize, sizeof(int));
        nums_cmp = (int *)calloc(numsSize, sizeof(int));
        for (int i = 0; i < numsSize; i++)
        {
            nums[i] = rand() % 10000; //随机数0~9999
            nums_cmp[i] = nums[i];
        }
    }
    printf("src:\n");
    print_nums(nums, numsSize);

    //使用自己写的排序算法
    sort_type_t type = SORT_SELECT;
    switch (type)
    {
    case SORT_C_LIB:    //c库函数排序
        qsort(nums, numsSize, sizeof(int), cmp_int);
        break;
    case SORT_BUBBLE:   //冒泡排序
        sort_bubble(nums, numsSize);
        break;
    case SORT_SELECT:   //选择排序
        sort_select(nums, numsSize);
        break;
    case SORT_INSERT:   //插入排序
        sort_insert(nums, numsSize);
        break;
    case SORT_SHELL:    //希尔排序
        sort_shell(nums, numsSize);
        break;
    case SORT_MERGE:    //归并排序
        sort_merge(nums, numsSize);
        break;
    case SORT_QUICK:    //快速排序
        sort_quick(nums, numsSize);
        break;
    case SORT_HAEP:     //堆排序
        sort_heap(nums, numsSize);
        break;
    case SORT_COUNT:    //计数排序
        sort_count(nums, numsSize);
        break;
    case SORT_BUCKET:   //桶排序
        sort_bucket(nums, numsSize);
        break;
    case SORT_RADIX:   //基数排序
        sort_radix(nums, numsSize);
        break;
    default:
        break;
    }
    
    //使用库排序算法
    qsort(nums_cmp, numsSize, sizeof(int), cmp_int);

    printf("my result:\n");
    print_nums(nums, numsSize);
    printf("standard result:\n");
    print_nums(nums_cmp, numsSize);

    //比较结果
    for (int i = 0; i < numsSize; i++)
    {
        if (nums_cmp[i] != nums[i])
        {
            printf("\n!!!sort err!!! sort alg=%d, err index=%d\n", type, i);
            return -1;
        }
    }
    
    printf("\n!!!sort ok!!!\n");
    return 0;
}

