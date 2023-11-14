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

treePointer *equation ;//指到樹的根
treePointer createNode(char c)
{
    treePointer newNode ; 
    MALLOC(newNode,sizeof(*newNode)); 
    newNode->data = c ; 
    newNode->Left = NULL ; 
    newNode->Right = NULL ; 
    
}


int main()
{
    

    
}