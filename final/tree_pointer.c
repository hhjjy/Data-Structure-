/**
 * @file tree_pointer.c
 * @author your name (you@domain.com)
 * @brief 針對課本ch5 tree binary tree traversals 例題練習
 * @version 0.1
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "useful.h"
typedef struct node * treePointer;
typedef struct node
{
    char data ;
    treePointer Left , Right ; 
}node;

treePointer equation ;//指到樹的根
treePointer equation2 ;//指到樹的根

treePointer createNode(char c)
{
    treePointer newNode ; 
    MALLOC(newNode,sizeof(*newNode)); 
    newNode->data = c ; 
    newNode->Left = NULL ; 
    newNode->Right = NULL ; 
    return newNode ; 
}
void printTree_preorder(treePointer root)
{
    if(root)
    {// VLR preorder 
        printf("%c",root->data) ; 
        printTree_preorder(root->Left); 
        printTree_preorder(root->Right); 
    }

}
void printTree_inorder(treePointer root)
{
    if(root)
    {// LVR preorder 
        printTree_inorder(root->Left); 
        printf("%c",root->data) ; 
        printTree_inorder(root->Right); 
    }

}
void printTree_postorder(treePointer root)
{
    if(root)
    {// LRV post 
        printTree_postorder(root->Left); 
        printTree_postorder(root->Right); 
        printf("%c",root->data) ; 
    }
}

/**
 * @brief 
 * 
 */
#define MAX_STACK_SIZE 100
treePointer stack[MAX_STACK_SIZE] ={0} ;
int top = -1 ; 
void push(treePointer node)
{
    stack[++top] = node ; // 塞入點 
}
treePointer pop()
{
    if (top != -1)
        return stack[top--] ; 
    else 
        return NULL ; 
}
int front = -1 , rear = -1 ; 
void addq(treePointer node)
{
    stack[++rear] = node ; 
}
treePointer deleteq()
{
    if (front !=  rear)
        return stack[++front] ;
    else 
    {
        rear = -1 ; 
        front = -1 ; 
        return NULL ; 
    }
        
}
void printTree_iterinorder(treePointer root)
{
    treePointer node = root; 
    // LVR 
    for(;;)
    {
        for(;node; node = node->Left)// 往左找到底並加到stack中 
            push(node); // 塞點
        // 兩個可能條件會發生
        // 1. 往左到底停止，回到自己 
        // 2. 右邊沒得塞所以回去一格 => 當右邊是null時會回到上一格 
        node = pop() ;  
        //設定退出條件！
        if (node == NULL) return ;  // root節點退出
        printf("%c",node->data) ; //顯示當前節點  
        node = node->Right ; // 往右邊走看看 
    }
}

void printTree_levelorder(treePointer root)
{//BFS
    treePointer node = root ; 
    addq(node); 
    for (;;)
    {
        //設定當前節點 
        node = deleteq(); 
        if (!node) return ; 
        printf("%c",node->data);
        // 2. 塞左邊 , 塞右邊 
        if (node->Left) addq(node->Left) ; 
        if (node->Right) addq(node->Right) ; 
    }
}

treePointer copy(treePointer root)
{
    treePointer temp;
    if(root)
    {
        MALLOC(temp,sizeof(*temp)) ; 
        temp->Left = copy(root->Left); 
        temp->Right = copy(root->Right) ; 
        temp->data = root->data ; 
        return temp ; 
    }
    return NULL ; 
    

}
int main()
{
    
    equation = createNode('+') ;
    equation->Left = createNode('*') ;
    equation->Right = createNode('E') ;
    equation->Left->Left = createNode('*') ;
    equation->Left->Right = createNode('D') ;
    equation->Left->Left->Left = createNode('/') ;
    equation->Left->Left->Right = createNode('C') ;
    equation->Left->Left->Left->Left = createNode('A') ;
    equation->Left->Left->Left->Right = createNode('B') ;
    printf("preorder:說白了就是先中間左邊最後右邊 \t");printTree_preorder(equation) ;     printf("\n");
    printf("inorder:說白了就是先左邊中間最後右邊（DFS） \t");printTree_inorder(equation) ;  printf("\n");
    printf("postorder:說白了就是先中邊右邊最後中間 \t");printTree_postorder(equation) ;  printf("\n");
    printf("inorder:說白了就是先左邊中間最後右邊 \t");printTree_iterinorder(equation) ;  printf("\n");
    printf("levelorder:說白了就是BFS \t");printTree_levelorder(equation) ;  printf("\n");
    // COPY 
    equation2 = copy(equation) ; 
    printf("inorder copy test \t");printTree_levelorder(equation2) ;  printf("\n");

    return 0 ; 
}