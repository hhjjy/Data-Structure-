#include "useful.h"
#define MAX_CAPCITY 100 
int capcity = MAX_CAPCITY ; 
typedef struct element
{
    int data ; 
}element_t;
element_t *quene  ;
element_t EMPTY = {.data =-1 }; 
int front = -1 ; 
int rear = -1 ; 
void QUENEFULL(element_t *quene)
{
    int start = (front + 1)%capcity ; //資料從哪邊開始     
    element_t *newQuene ; 
    MALLOC (newQuene, 2* capcity * sizeof(element_t)) ; 
    int first_piece = 0 ; 
    int second_piece = 0 ; 
    // start =0 ,1 =>不用分兩段存 
    if (start < 2)
    {
        first_piece = 0 ; 
        second_piece = rear - start +1 ; 
    }
    else//分兩段存 
    {
        // 1. start - capcity -1 
        // 2. 0 - rear 
        first_piece = capcity -start ; 
        second_piece = rear +1  ; 
    }
    front = 2* capcity -1 ; //當前最大值
    rear = rear 
}
void copy()
/**
 * @brief addq 把資料加入到quene中 
 * 
 * @param quene 
 * @param data 
 */
void addq(element_t *quene,element_t data)
{
    rear = (rear + 1 )%capcity ; 
    if (front == rear)//滿了
        QUENEFULL(quene) ; 
    

}
/**
 * @brief deleteq
 * @return element_t temp 當前的quene ，如果相同就回傳quene EMPTY
 */
element_t deleteq()
{
    if (front == rear)
        return EMPTY ; 
    front = (front + 1) % capcity ; 
    return quene[front];
}
int main()
{
    MALLOC(quene,sizeof(element_t) * capcity) ; 

    return 0 ; 
}