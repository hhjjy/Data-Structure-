#include "useful.h"
#define MAX_TERM 100
typedef struct polynomial_term
{
    float coef;
    int exp;
} polynomial_term;
polynomial_term terms[MAX_TERM];
int avail = 0; // 當前存的

typedef struct polynomial
{
    int start;
    int end;
} polynomial;
polynomial A, B, D;

/**
 * @brief 對多項式A初始化
 *
 * @param A
 */
void p_init(polynomial *A)
{
    A->start = avail;
    A->end = avail - 1;
}
void p_attach(polynomial *A, float coef, int exp)
{
    if (avail >= MAX_TERM)
    {
        fprintf(stderr, "TOO many temrs in polynomial");
        exit(EXIT_FAILURE);
    }
    terms[++A->end].coef = (float)coef;
    terms[A->end].exp = exp;
    avail++;
}
/**
 * @brief 多項式相加
 *
 * @param A 輸入多項式
 * @param B 輸入多項式
 * @param D 輸出結果
 */
void p_add(polynomial *A, polynomial *B, polynomial *D)
{
    int startA = A->start, endA = A->end, startB = B->start, endB = B->end;
    while (startA <= endA && startB <= endB) // 跑直到有多項式跑完
    {
        switch (COMPARE(terms[startA].exp, terms[startB].exp))
        {
        case 1:
            p_attach(D, terms[startA].coef, terms[startA].exp);
            startA++;
            break;
        case 0:
            p_attach(D, terms[startA].coef + terms[startB].coef, terms[startA].exp);
            startA++;
            startB++;
            break;
        case -1:
            p_attach(D, terms[startB].coef, terms[startB].exp);
            startB++;
            break;
        default:
            break;
        }
    }
    //把A,B剩下的多項式插入近來
    for(;startA <=endA; startA ++) p_attach(D,terms[startA].coef,terms[startA].exp) ; 
    for(;startB <=endB; startB ++) p_attach(D,terms[startB].coef,terms[startB].exp) ; 
}
/**
 * @brief 顯示多項式A的每一項
 *
 * @param A
 */
void p_print(polynomial *A)
{
    printf("=============================================\n");
    printf("start,end: %d,%d\n", A->start, A->end);
    printf("=============================================\n");
    for (int i = A->start; i <= A->end; i++)
    {
        if (terms[i].exp != 0)
            printf("%.2fx^%d +", terms[i].coef, terms[i].exp);
        else
            printf("%.2f ", terms[i].coef);
    }
    printf("\n");
}

int main()
{
    // set poly A
    p_init(&A);
    p_attach(&A, 3.7, 2);
    p_attach(&A, 1, 1);
    p_attach(&A, 2, 0);
    p_print(&A);
    // set poly B
    p_init(&B);
    p_attach(&B, 5, 5);
    p_attach(&B, 6, 3);
    p_attach(&B, 2, 1);
    p_print(&B);
    // add to poly D
    p_init(&D);
    p_add(&A,&B,&D) ; 
    p_print(&D) ; 
    return 0;
}