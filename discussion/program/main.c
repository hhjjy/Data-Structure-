#include "useful.h"
#include "string.h"
#define SENTENCE_SIZE 1000
#define MAX_WORD_SIZE 100
typedef struct node *listPointer;
typedef struct node
{
    char *word;
    listPointer next;
} node;
// char words ; 要怎麼給他復職

// void addnodes(node *head, char *word)
// {
//     // strcpy(head->word, word);
//     listPointer temp ;
//     MALLOC(temp, sizeof(*temp)) ;
//     int lens =
//     for(int i = 0 ; i < MAX_WORD_SIZE && word[i]!= 0; i++)
//     {

//     }
// }

listPointer first = NULL;
listPointer last = NULL; // 最後一個

void addnode(listPointer *first, listPointer *last,
             char *word)
{
    // 分配新节点的内存空间
    node *new_node = malloc(sizeof(node));

    // 将分割好的字符串拷贝到新节点的word字段中
    new_node->word = strdup(word);

    // 将新节点插入到链表的末尾
    if (*first == NULL) { // 空的链表
        *first = new_node;
        *last = new_node;
        new_node->next = new_node;
    } else { // 非空的链表
        (*last)->next = new_node;
        new_node->next = *first;
        *last = new_node;
    }

}
void print_node(listPointer *first, listPointer *last)
{
    listPointer temp = *first
    for (; temp != *last; temp = temp->next) {
        printf("%s ", temp->word);
    }
    printf("%s ", (*last)->word);
}
void exchange(listPointer *first, listPointer *last)
{
    if (*first == NULL || (*first)->next == NULL) {
        return; 
    }

    // 交換節點
    listPointer tmp = *first;
    *first = *last;
    *last = tmp;

    // 更新next 
    (*last)->next = (*first)->next;
    (*first)->next = tmp->next;
    tmp->next = *first;
}

int main()
{
    // read
    char sentence[SENTENCE_SIZE] = "I am a student";
    // fgets(sentence,SENTENCE_SIZE + 2, stdin );
    // 创建两个节点
    char *token = strtok(sentence, " ");
    while (token != NULL)
    {
        // printf("%s\n", token);
        addnode(&first, &last, token);
        token = strtok(NULL, " ");
    }
    exchange(&first,&last) ; 
    print_node(&first, &last);

    // node a, b;
    // a.word = strdup("Block");
    // a.next = &b;
    // b.word = strdup("Guy");
    // b.next = NULL;

    // // 交换两个节点的word值
    // char *tmp = strdup(a.word);
    // free(a.word);
    // a.word = strdup(b.word);
    // free(b.word);
    // b.word = strdup(tmp);
    // free(tmp);

    // // 输出两个节点的word值
    // printf("%s %s\n", a.word, b.word);

    // // 释放两个节点的word值和节点本身的内存空间
    // free(a.word);
    // free(b.word);

    return 0;
}
