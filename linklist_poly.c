#include "useful.h"
/**
 * @brief 實作polymial 的 單向 linklist 
 * 
 */
typedef struct polyNode *polyPointer; 
typedef struct polyNode
{
    float coef ; 
    int exp ; 
    polyPointer next ; 
}polyNode;
typedef struct polynomial
{
    polyPointer first ; 
    polyPointer last ; 
}polynomial;

polynomial a, b ; 
/** 函數名稱:attach  
 * @param : polynomial a 指向 多項式a 
 * @param : coef 係數 
 * @param : exp 次數
 * TEST DONE 
*/
void attach(polynomial *a,float coef , int exp)
{
    polyPointer temp ; 
    MALLOC(temp,sizeof(*temp)); 
    if((*a).first == NULL || (*a).last == NULL)
    {
        (*a).first = temp ; 
        (*a).last  = temp ; 
        temp->coef = coef ; 
        temp->exp = exp ; 
        temp->next = NULL; 
    }
    else 
    {

        (*a).last->next = temp ; 
        (*a).last = (*a).last->next ; 
        temp->coef = coef ; 
        temp->exp = exp ; 
        temp->next = NULL ; 
    }
}
/**
 * @brief 相加多項式A & B 
 * 
 * @param a 
 * @param b 
 * @return polynomial* 
 */
polynomial *padd(polynomial *a , polynomial *b)
{
    polynomial *D ; 
    MALLOC(D,sizeof(*D)) ; 
    polyPointer firstA , firstB; 
    firstA = (*a).first ; 
    firstB = (*b).first ; 
    // add 
    while (firstA!=NULL && firstB != NULL)
    {
        switch (COMPARE(firstA->exp,firstB->exp))
        {
        case 1: // a > b 指數
            attach(D,firstA->coef,firstA->exp); 
            firstA = firstA->next ; 
            break;
        case 0 :
            attach(D,firstA->coef+firstB->coef,firstA->exp); 
            firstA = firstA->next ; 
            firstB = firstB->next ; 
            break; 
        case -1 :
            attach(D,firstB->coef,firstB->exp); 
            firstB = firstB->next ; 
            break; 
        }
    }
    // 處理剩下的
    for(;firstA;firstA = firstA->next) attach(D,firstA->coef,firstA->exp);
    for(;firstB;firstB = firstB->next) attach(D,firstB->coef,firstB->exp);


    return D ; 
}
void pprint(polynomial a)
{
    polyPointer temp = a.first ; 
    for(;temp;temp = temp->next) printf("%.2fx^%d + ",temp->coef,temp->exp); 
    printf("\n"); 
}
/**
 * @brief 釋放空間把
 * 
 * @param D 
 */
void erase(polynomial *D)
{
    polyPointer first = (*D).first ; 
    polyPointer temp ; 
    while (first)  
    {
        temp = first ; 
        first = first->next ; 
        free(temp) ; 
    }

}
int main()
{
    polynomial *D ; 
    attach(&a,1.7,1);
    attach(&a,1,0);

    attach(&b,3,5) ; 
    attach(&b,3,1) ; 
    attach(&b,3,0) ; 

    D = padd(&a,&b);
    pprint(*D); 
    erase(&D); 
    return 0 ; 
}