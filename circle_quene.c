#include "stdio.h"
#include "stdlib.h"
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
#define MAX_CAPCITY 10
int capcity = MAX_CAPCITY;
typedef struct element *quenePointer;
typedef struct element
{
    int data;
} element_t;

element_t *quene;
element_t EMPTY = {.data = -1};
int front = MAX_CAPCITY -1;
int rear = MAX_CAPCITY -1 ;


/**
 * @brief 把element start 到 end 的所有元素都存到quene[i]後
 *
 * @param i 插入到第i個
 * @param start 插入元素起始
 * @param end
 * @param quene
 */
void copyq(int i, quenePointer start, quenePointer end, quenePointer *quene)
{
    int index = i;
    if (start > end)
    {
        fprintf(stderr, "copy error");
        exit(1);
    }
    while (start <= end)
    {
        *quene[i] = *start;
        i++;
        start++; // 往後指一個
    }
}
void QUENEFULL(element_t *quene)
{
    int start = (front + 1) % capcity; // 資料從哪邊開始
    element_t *newQuene;
    MALLOC(newQuene, 2 * capcity * sizeof(element_t));
    int first_piece = 0;
    int second_piece = 0;
    // start =0 ,1 =>不用分兩段存
    if (start < 2)
    {
        first_piece = 0;
        second_piece = rear - start + 1;
        copyq(0, quene + start, quene + rear, newQuene); // 複製是 從start 存到rear
    }
    else // 分兩段存
    {
        // 1. [start - capcity -1 ]
        // 2. [0 - rear ]
        first_piece = capcity - start;
        second_piece = rear + 1;
        copyq(           0, quene + start, quene + start + first_piece - 1, newQuene);       // 複製是第一段
        copyq(first_piece , quene +     0, quene + rear, newQuene); // 複製是 從start 存到rear
    }
    front = 2 * capcity - 1; // 當前最大值
    rear = first_piece + second_piece - 1;
    capcity *= 2 ; 
    free(quene) ; 
    quene = newQuene; 
}

/**
 * @brief addq 把資料加入到quene中
 *
 * @param quene
 * @param data
 */
void addq(quenePointer quene, element_t data)
{
    rear = (rear + 1) % capcity;
    if (front == rear) // 滿了
        QUENEFULL(quene);
    quene[rear] = data;
}
/**
 * @brief deleteq
 * @return element_t temp 當前的quene ，如果相同就回傳quene EMPTY
 */
element_t deleteq()
{
    if (front == rear)
        return EMPTY;
    front = (front + 1) % capcity;
    return quene[front];
}
/**
 * @brief 
 * 
 * @return int 
 */
void printq(quenePointer quene)
{
    printf("f,r:%d %d\n", front, rear);
    int i = (front + 1) % capcity;
    for (; i != rear; i = (i + 1) % capcity)
    {
        printf("%d ", quene[i].data); // 读取 element_t 类型的变量的 data 成员
    }
    printf("\n");
}
// TODO : BUG 是 data =9 沒有顯示 
// TODO : 要測試整個程式的資料空間需要擴增時的處理方式！

int main()
{
    MALLOC(quene, sizeof(element_t) * capcity);
    element_t temp = {.data =1 }; 
    temp.data = 2 ; addq(&quene,temp) ; 
    temp.data = 3 ; addq(&quene,temp) ; 
    temp.data = 4 ; addq(&quene,temp) ;  
    temp.data = 5 ; addq(&quene,temp) ; 
    temp.data = 6 ; addq(&quene,temp) ; 
    temp.data = 7 ; addq(&quene,temp) ;
    temp.data = 8 ; addq(&quene,temp) ; 
    temp.data = 9 ; addq(&quene,temp) ; 
    printq(&quene) ; 
    return 0;
}