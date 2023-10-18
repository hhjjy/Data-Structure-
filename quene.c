// C 語言初始設定
#include <stdio.h>
#include <stdlib.h>

// quene 實作 
#define QUENE_SIZE 20 
typedef struct ele{
    int value ; 
}element ;
element quene[QUENE_SIZE] = {0}; 
int rear = -1 ; 
int front = -1 ; 
// quene 是否滿了
int Quene_is_full()
{
    if (rear == QUENE_SIZE - 1)
        return 1 ; 
    return 0;     
}
// quene 是否空了 
int Quene_is_empty()
{
    if (front == rear)
    {
        // 清空空間
        front = -1  ; 
        rear = - 1 ; 
        return 1 ; 
    }
    return 0 ; 
}
// 取出 quene 
element Quene_pop()
{
    element temp = {0}; 
    if (!Quene_is_empty())
    {
        temp = quene[++front] ; 
        return temp ; 
    }
    return  temp;
}
// 加入到quene 
void quene_add(element data)
{
    if (Quene_is_full())
    {
        // 應該要  expand 
        printf("quene is full\n");
        return ; 
    }
    quene[++rear] = data ; 
}
void print_quene(element *arr)
{
    // 怎麼不動quene 的情況下顯示
    if (Quene_is_empty())
    {
        printf("quene is empty\n");
        return ;    
    }
    // printf("Front:%d , rear:%d\n",front,rear) ; 
    for (; !Quene_is_empty() ; )
    {
        printf("%d,",Quene_pop());
    }
    printf("\n");

}
int main()
{
    // element data = {0};
    // data.value = 10 ; 
    // quene_add(data); 
    // data.value = 20 ; 
    // quene_add(data); 
    // data.value = 30 ; 
    // quene_add(data); 
    // Quene_pop() ; 
    // Quene_pop() ; 
    // Quene_pop() ; 

    print_quene(quene);
    return 0  ;
}