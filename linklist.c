#include <stdio.h>
#include <stdlib.h>
/**
 * @brief 實作節點插入 刪除節點 反轉 串接
 */
// linklist 
typedef struct listNode *listPointer ; 
typedef struct listNode
{
    int data;
    listPointer next;
}listNode;
listPointer first = NULL ; 
/**
 * @brief 反轉給予的list
 * 
 * @param first 
 */
void invert(listPointer *first)
{
    listPointer lead , middle ,trail ;
    lead = *first ; 
    if(lead)//代表有指向東西
    {
        middle = NULL ; 
        trail = NULL ; 
        while (lead)
        {
            trail = middle ; // 1 
            middle = lead ;  // 2 
            lead= lead->next;  // 3 
            middle->next = trail ; // 4 
        }
    }
    *first = middle ; 
}
/**
 * 函式描述：插入到節點x後面
 * @param first ：指標指向該節點的第一個指標
 * @param x ：節點x
 * @param data：插入內容
 * @return 
 */
void insert(listPointer *first, listPointer x,  int data )
{
    // 1. assign new spaces
    listPointer new_node ;
    new_node =  malloc(sizeof(*new_node)); 
    new_node->data = data ;

    if(*first)   // *first sotre address is not empty 
    { 
      new_node->next = x->next ;
      x->next = new_node ;
    }else// empty 
    {
        *first = new_node ;
        new_node->next = NULL ;
    }

}
/**
 * 函式描述：刪除節點x
 * @param first ：first指向該第一個節點的指標
 * @param trail ：你希望刪除的前一個節點
 * @param x ：你希望刪除的節點
 * @return 回傳值描述
 */
void delete(listPointer *first, listPointer trail , listPointer x)
{
    if(trail)
    {
        trail->next = x->next;
    }else  // delete first if trail is null 
    {
        *first = (*first)->next ; // *first the first which means store the value of first element . 
                                  // (*first)->next :the address of element saved 
    }
    free(x); 
}
/**
 * 函式描述：顯示LinkList
 * @param first ：first指向該第一個節點的指標
 * @return 
 */void printList(listPointer first)
{
    listPointer current = first ;
    for(; current; current = current->next)
    {
        printf("%d ", current->data) ; 
    }
    printf("\n");
}
int main() {
    // 插入節點
    insert(&first, NULL, 10) ;
    insert(&first, first, 30) ;
    insert(&first, first, 40) ;
    printList(first); 
    invert(&first) ;      
    printList(first); 

    // printList(first);
    //插入第一個節點 
    // insert(&first ,NULL,100);
    // printList(first);

    return 0 ; 
}