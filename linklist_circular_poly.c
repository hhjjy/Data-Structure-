#include "useful.h"
/**
 * @brief 實作polymial 的 環形linklist 包含avail list 實做
 *
 *
 */
typedef struct polyNode *polyPointer;
typedef struct polyNode
{
    float coef;
    int exp;
    polyPointer next;
} polyNode;
typedef struct polynomial
{
    polyPointer first;
    polyPointer last; // 加了last比較好訪問最後一個
} polynomial;
polynomial a, b;
polyPointer avail = NULL; // free後暫存 不用再存系統拿 先暫時放在這

// 取得長度 測試正常
int plength(polynomial a)
{
    polyPointer temp = a.first;
    int length = 0;
    if (temp)
    {
        do
        {
            length += 1;
            temp = temp->next;
        } while (temp != a.first);
        return length;
    }
    return 0;
}
// 測試後結果正常
polyPointer getNode()
{
    polyPointer temp;
    // 從avail 取得
    if (avail)
    {
        temp = avail;
        avail = avail->next;
    }
    else
    {
        MALLOC(temp, sizeof(*temp));
    }
    return temp;
}
// 測試後結果正常
void retNode(polyPointer rnode)
{
    rnode->next = avail; // 先指到avail上
    avail = rnode;       // 把avail再指到node 上=>node 會被avail指到且是放到第一個
}
// 測試後結果正常
void cearse(polynomial a)
{
    polyPointer temp;
    if (a.first)
    {
        a.last->next = NULL; // 環形段開來!
        avail = a.first;
    }
    // free(a) ;
}

/** 函數名稱:attach
 * @param : polynomial a 指向 多項式a
 * @param : coef 係數
 * @param : exp 次數
 * TEST DONE
 */
void attach(polynomial *a, float coef, int exp)
{
    polyPointer temp = getNode();
    if ((*a).first == NULL || (*a).last == NULL)
    {
        (*a).first = temp;
        (*a).last = temp;
        temp->coef = coef;
        temp->exp = exp;
        temp->next = temp;
    }
    else
    { // 從last加資料
        (*a).last->next = temp;
        (*a).last = (*a).last->next;
        temp->coef = coef;
        temp->exp = exp;
        temp->next = (*a).first;
    }
}
/**
 * @brief 環形相加多項式A & B
 *
 * @param a
 * @param b
 * @return polynomial*
 */
polynomial *cpadd(polynomial a, polynomial b)
{
    polynomial *D;
    MALLOC(D, sizeof(*D));
    polyPointer firstA, firstB;
    firstA = a.first;
    firstB = b.first;
    if (firstA == NULL && firstB == NULL)
    {
        return NULL;
    }
    else if (firstA == NULL)
    {
        do{
            attach(D, firstB->coef, firstB->exp);
            firstB = firstB->next; 
        } while (firstB != b.first);
        return D; 
    }
    else if (firstB == NULL)
    {
        do{
            attach(D, firstA->coef, firstA->exp);
            firstA = firstA->next ; 
        } while (firstA != a.first);
        return D ; 
    }

    // add
    do
    {
        switch (COMPARE(firstA->exp, firstB->exp))
        {
        case 1: // a > b 指數
            attach(D, firstA->coef, firstA->exp);
            firstA = firstA->next;
            break;
        case 0:
            attach(D, firstA->coef + firstB->coef, firstA->exp);
            firstA = firstA->next;
            firstB = firstB->next;
            break;
        case -1:
            attach(D, firstB->coef, firstB->exp);
            firstB = firstB->next;
            break;
        }
    } while (firstA != a.first && firstB != b.first);
    if (firstA == NULL && firstB == NULL)
    {
        return D;
    }
    else if (firstA == NULL)
    {
        do{
            attach(D, firstB->coef, firstB->exp);
            firstB = firstB->next; 
        } while (firstB != b.first);
        return D; 
    }
    else if (firstB == NULL)
    {
        do{
            attach(D, firstA->coef, firstA->exp);
            firstA = firstA->next ; 
        } while (firstA != a.first);
        return D ; 
    }

    return D;
}
void pprint(polynomial a)
{
    polyPointer temp = a.first;
    if (a.first == NULL)
    {
        return ; 
    }

    do{
        printf("%.2fx^%d + ", temp->coef, temp->exp);
        temp = temp->next ; 
    }while (temp!= a.first); 
    printf("\n");
}

int main()
{
    // NOTE test 環形中attach有問題
    polynomial a = {0};
    attach(&a, 8, 9);
    attach(&a, 4, 1);
    attach(&a, 4, 0);
    // cearse(a) ;
    polynomial b = {0};

    attach(&b, 3, 1);
    attach(&b, 4, 0);
    polynomial *D = cpadd(a,b) ; 
    pprint(*D) ; 
    // cearse(b) ;
    // printf("a:%d b:%d\n", plength(a), plength(b));
    return 0;
}