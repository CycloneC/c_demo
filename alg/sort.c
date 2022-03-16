#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"

#define SWAP(a, b) {(a) = (a) ^ (b); (b) = (a) ^ (b); (a) = (a) ^ (b);}

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
} sort_type_t;

void print_nums(int *nums, int numsSize)
{
    printf("\n\t[ ");
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

int main(int argc, char const *argv[])
{
    int nums[] = {5, 3, 6, 7, 9, 5, 5, 2, 8, 1, 4, 5};
    int numsSize = sizeof(nums) / sizeof(int);
    sort_type_t type = SORT_HAEP;

    print_nums(nums, numsSize);

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
    default:
        break;
    }

    print_nums(nums, numsSize);
    return 0;
}

