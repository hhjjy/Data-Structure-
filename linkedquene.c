#include "useful.h"

// 定義 
#define MAX_QUENE 10 
typedef struct quene *quenePointer ;
typedef struct element 
{
    int data ; 
}element; 
typedef struct quene
{
    element data ; 
    quenePointer next ; 
}quene;
quenePointer front[MAX_QUENE]; 
quenePointer rear[MAX_QUENE]; 
element EMPTY = {.data = -1 } ; 
void quene_init()
{
    for (int i = 0; i < MAX_QUENE; i++)
    {
        front[i] = NULL; 
        rear[i] = NULL ; 
    }
}
/** 函數名稱:addq 
 * @param : i 表示第i組quene
 * @param : e 表示要加入數據
 * @param : rear 指向當前最後quene的最後一筆地址
 * @param : front指向當前quene第一筆地址
*/
void addq(int i, element e)
{
    quenePointer temp ; 
    MALLOC(temp,sizeof(*temp)); 
    temp->data = e ; 
    // link it 
    // 1. 
    if (front[i] == NULL){
        front[i] = temp ; //front 節點指向剛創見的節點
    }else {
        rear[i]->next = temp ; //把上一個rear連接的下一個設定成當前節點  
    }
    rear[i] = temp ;// 指向rear  
}
/** 函數名稱:deleteq 
 * @param : i 表示第i組quene
 * @param : rear 指向當前最後quene的最後一筆地址
 * @param : front指向當前quene第一筆地址
 * @return: e element從quene的front 取出 
*/
element deleteq(int i)
{
    element e ; 
    quenePointer temp  = front[i] ;
    // 從front 取 
    if (temp == NULL){
        return EMPTY ; 
    }
    e = temp->data ; 
    front[i] = temp->next ; 
    free(temp);
    return e ; 
}
void print_quene(int i)
{
    quenePointer temp = front[i]; 
    for(; temp ; temp = temp->next)
    {
        printf("%d ",temp->data); 
    }
    printf("\n");
}
int main ()
{
    /* test */
    quene_init() ; 
    element test= {.data = 1}; addq(0 , test);
    test.data = 2; addq(0 , test);
    test.data = 3; addq(0 , test);
    test.data = 4; addq(0 , test);
    test.data = 5; addq(0 , test);
    deleteq(0); 
    print_quene(0);
    test.data = 5; addq(0 , test);
    test.data = 4; addq(0 , test);
    print_quene(0);

    return 0 ; 
}