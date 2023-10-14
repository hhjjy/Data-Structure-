#ifndef __userful__
#define __userful__

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

// 顯示整個arr
#define PRINT_ARR(ARR, SIZE) \
    do \
    { \
        for (int i = 0; i < SIZE; i++) \
            printf("%d ", ARR[i]); \
        printf("\n"); \
    } while (0)

// 交換
#define SWAP(a, b, t) (t = a, a = b, b = t)

// 比較大小
#define COMPARE(a, b) (a > b ? 1 : (a < b ? -1 : 0))

// 分配記憶體空間
#define MALLOC(arr, size) \
    do \
    { \
        if (!(arr = malloc(size))) \
        { \
            fprintf(stderr, "Malloc error\n"); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#define REMALLOC(arr, size) \
    do \
    { \
        if (!(arr = realloc(arr, size))) \
        { \
            fprintf(stderr, "Realloc error\n"); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

// 顯示執行時間多少 輸入的是void
#define TIME_FUNCTION(func)                                                         \
    do                                                                              \
    {                                                                               \
        clock_t start = clock();                                                    \
        func();                                                                     \
        clock_t end = clock();                                                      \
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;            \
        printf("Function %s takes %f seconds to execute.\n", #func, cpu_time_used); \
    } while (0)

#endif
