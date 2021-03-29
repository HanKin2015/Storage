#include <string.h>
#include <assert.h>

typedef struct arr_t {
    int *vals;
    int capacity;
    int cnt;
} arr_t;

static int binary_search(int arr[], int beg, int end, int val)
{
    int pos;
    if (end <= beg)
        return beg;
    pos = beg + (end - beg) / 2;
    if (arr[pos] == val)
        return pos;
    else if (arr[pos] > val)
        return binary_search(arr, beg, pos, val);
    else
        return binary_search(arr, pos + 1, end, val);
}
//  使用二分查找的方法寻找插入点
int insert0(arr_t *arr, int val)
{
    int i;
    assert(arr);

    if (arr->cnt >= arr->capacity)
        return -1;
    i = binary_search(arr->vals, 0, arr->cnt, val);
    if (i < arr->cnt) {
        memmove(&arr->vals[i + 1], &arr->vals[i], sizeof(int) * (arr->cnt - i));
    }
    arr->vals[i] = val;
    ++arr->cnt;
    return 0;
}
//  使用遍历的方法寻找插入点
int insert1(arr_t *arr, int val)
{
    int i;
    assert(arr);

    if (arr->cnt >= arr->capacity)
        return -1;
    for (i = 0; i < arr->cnt; ++i) {
        if (arr->vals[i] >= val)
            break;
    }
    if (i < arr->cnt) {
        memmove(&arr->vals[i + 1], &arr->vals[i], sizeof(int) * (arr->cnt - i));
    }
    arr->vals[i] = val;
    ++arr->cnt;
    return 0;
}
int insert2(arr_t *arr, int val)
{
    return 0;
}
int insert3(arr_t *arr, int val)
{
    return 0;
}
int insert4(arr_t *arr, int val)
{
    return 0;
}

typedef int (*fn_insert)(arr_t *arr, int val);

#define OJ_RUN_ROUND_NUM 5

int insert(arr_t *arr, int val)
{
    static fn_insert funcs[OJ_RUN_ROUND_NUM] = {
        insert0,
        insert1,
        insert2,
        insert3,
        insert4,
    };

    return funcs[s_run_round](arr, val);
}

