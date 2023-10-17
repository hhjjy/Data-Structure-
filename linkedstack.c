#include "useful.h"
#define STACK_MAX 10 
//解釋：針對typedef struct stack這個結構用一個指標指向
typedef struct stack *stackPointer; 
typedef struct element
{
    int data ; 
    /* data */
}element;
//解釋：針對typedef struct stack這個結構定義成一個型態
typedef struct stack
{
    element data ; 
    stackPointer next ;
}stack ;
// element 
element EMPYT ={.data=-1} ; 
// stack TOP
stackPointer TOP[STACK_MAX] ; 

void Stack_init()
{
    for (int i =0 ; i < STACK_MAX ; i++)
        TOP[i] = NULL ;
}
/**
 * 函數描述：psuh element into ith stack 
 * @param: int i : 存入第i個stack 
 * @param: element e:存入的物件
*/
void push(int i , element e)
{
    // assign a memory 
    stackPointer temp ; 
    MALLOC(temp,sizeof(stack)) ; 
    temp->data = e ; 
    temp->next = TOP[i] ;//指向原本的地址
    TOP[i] = temp ; //TOP指向現在的地址
}
/**
 * 函數描述：pop element from ith stack 
 * @param: int i : 存入第i個stack 
 * @param: element e:存入的物件
*/
element pop(int i)
{
    element e ; 
    stackPointer temp = TOP[i]; 
    // 空的情況
    if (temp == NULL)
        return EMPYT ;  
    e = temp->data ;
    TOP[i] = temp->next ; 
    free(temp); 
    return e ;
}
void stack_print(int i)
{
    stackPointer temp = TOP[i]; 
    for(; temp; temp = temp->next )
    {
        printf("%d ",temp->data) ; 
    }
    printf("\n"); 
}
// TODO :測試把pop 到元素空為止
int main()
{
    Stack_init(); 
    element e = {.data = 1} ;     push(0,e) ;

    e.data = 2 ;     push(0,e) ;

    e.data = 3;     push(0,e) ;

    e.data = 4 ;     push(0,e) ;

    pop(0); 
    pop(0); 
    pop(0); 
    // pop(0); 
    // pop(0); 

    // e.data = 5 ;     push(0,e) ;

    stack_print(0); 
    return  0; 
}