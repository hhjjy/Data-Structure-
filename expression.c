#include "useful.h"

#define STACK_MAX 10 
//解釋：針對typedef struct stack這個結構用一個指標指向
typedef enum {
    lparen ,
    rparen ,
    plus , 
    minus , 
    times , 
    divide, 
    mod , 
    eos, 
    operand,
} precedence ; 
typedef struct stack *stackPointer; 
typedef struct element
{
    precedence c ; 
    /* data */
}element;
//解釋：針對typedef struct stack這個結構定義成一個型態
typedef struct stack
{
    element data ; 
    stackPointer next ;
}stack ;
// element 
element EMPYT ={.c=-1} ; 
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
element stack_get_top(int i)
{
    if (TOP[i] == NULL)
        return EMPYT ;  
    return TOP[i]->data ; 
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
int isEmpty(element e )
{
    return e.c == -1 ; 
}
/**
 * @brief Get the Token object
 * 
 * @param symbol 指向文字串的第一個
 * @param n 取第n個
 */
precedence getToken(char *symbol ,int *n)
{
    char word = symbol[(*n)++] ; 
    switch (word)
    {
    case '(':
        return lparen ;    
    case ')':
        return rparen ;    
    case '+':
        return plus ;    
    case '-':
        return minus ;    
    case '*':
        return times ;    
    case '/':
        return divide ;    
    case '%':
        return mod ;    
    case '\0':
        return eos ;    
    default:
        return operand;
    }
}
char printPop(precedence c)
{

    switch (c)
    {
    case lparen:
        printf("(");
        return '(' ;    
    case rparen:
        printf(")");
        return ')' ;    
    case plus:
        printf("+");
        return '+' ;    
    case minus:
        printf("-");
        return '-' ;    
    case times:
        printf("*");
        return '*' ;    
    case divide:
        printf("/");
        return '/' ;    
    case mod:
        printf('%');
        return '%' ;    
    case eos:
        return '\0' ;    
    }

}
char get_pop_char(precedence c)
{

    switch (c)
    {
    case lparen:
        // printf("(");
        return '(' ;    
    case rparen:
        // printf(")");
        return ')' ;    
    case plus:
        // printf("+");
        return '+' ;    
    case minus:
        // printf("-");
        return '-' ;    
    case times:
        // printf("*");
        return '*' ;    
    case divide:
        // printf("/");
        return '/' ;    
    case mod:
        // printf('%');
        return '%' ;    
    case eos:
        return '\0' ;    
    }

}
int isp(precedence c)
{

    switch (c)
    {
    case lparen:
        return 0 ;    
    case rparen:
        return 19 ;    
    case plus:
        return 12 ;    
    case minus:
        return 12 ;    
    case times:
        return 13 ;    
    case divide:
        return 13 ;    
    case mod:
        return 13 ;    
    case eos:
        return 0 ;    
    }

}
int icp(precedence c)
{

    switch (c)
    {
    case lparen:
        return 20 ;    
    case rparen:
        return 19 ;    
    case plus:
        return 12 ;    
    case minus:
        return 12 ;    
    case times:
        return 13 ;    
    case divide:
        return 13 ;    
    case mod:
        return 13 ;    
    case eos:
        return 0 ;    
    }

}
// TODO 還是有bug 與課本解答不一致
void postToPosfix()
{
    Stack_init() ; 
    int n = 0 ; 
    char words[] = "a*b+c+d*e"; // 
    char now = words[0]; 
    // if (getToken(words,&n)==lparen)
    //     printf("HELLO\n") ; 

    precedence c = getToken(words,&n) ; 
    // printf("%d",n); 
    for(; c != eos ; now = words[n],c = getToken(words,&n))
    {
        if (c == operand)
        {
            printf("%c",now); 
        }
        else if (c == rparen )
        {
            while (stack_get_top(0).c != lparen) // 
            {
                element e = pop(0); 
                printPop(e.c) ; 
            }
            pop(0) ; 
        }
        else // 比較當前的操作符號與stack頂端的大小 如果stack Top * 當前是 + print出來 
        {
            while(isp(stack_get_top(0).c) >= icp(c) )
            {
                element e = pop(0)  ;
                printPop(e.c); 
            }
            element temp = {.c = c}  ; 
            push(0,temp) ; 
        }

    }
    // 最後把剩下的符號打印出來
    while (!isEmpty(stack_get_top(0)))
    {
        element e = pop(0) ; 
        printPop(e.c); 
    } 
    
    
    



}



int main ()
{

    postToPosfix(); 


}