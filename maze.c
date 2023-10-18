#include "useful.h"
#define STACK_MAX 10 



//解釋：針對typedef struct stack這個結構用一個指標指向
typedef struct stack *stackPointer; 
typedef struct element
{
    int row ; 
    int col ; 
    int dir ; 
    /* data */
}element;
typedef struct move_
{
    int hor ; 
    int vet ; 
}move_t ; 
move_t move[8] = {
    {0, -1}, // N 
    {1, -1}, // NE
    {1, 0}, // E
    {1, 1}, // ES
    {0, 1}, // S 
    {-1, 1},// WS
    {-1, 0},// W 
    {-1, -1}// NW
};


//解釋：針對typedef struct stack這個結構定義成一個型態
typedef struct stack
{
    element data ; 
    stackPointer next ;
}stack ;
// element 
element EMPYT ={.dir = -1 ,.col = 0 , .row =0} ; 
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
    printf("==========================================================\n"); 
    for(; temp; temp = temp->next )
    {
        printf("%d %d %d",temp->data.row,temp->data.col,temp->data.dir) ; 
        printf("\n"); 
    }
    printf("==========================================================\n"); 
}
/**
 * @brief 
 * 
 */
void path ()
{
    

    // 加入節點 

    while (TOP[0])
    {
        /* code */
    }
    
    
}
int main()
{
    Stack_init(); 
    element e = {.row= 1 ,.col=1,.dir =0} ;
    push(0,e) ;
    e.row = 2 ; e.col = 2 ; e.dir = 0 ; 
    push(0,e) ;
    stack_print(0) ;
    

}