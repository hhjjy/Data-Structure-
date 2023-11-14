#include <stdio.h>

#define SIZE 100
char tree[SIZE] = {0};

void insert(int i, char c)
{
    tree[i] = c;
}

char getparent(int i)
{
    return tree[i / 2];
}

char getleftchild(int i)
{
    return tree[2 * i];
}

char getrightchild(int i)
{
    return tree[2 * i + 1];
}

void printTreeHelper(int i, int depth)
{
    if (tree[i] == 0) {
        return;  // 節點為空，遞迴終止
    }

    printTreeHelper(2 * i + 1, depth + 1);  // 印出右子節點

    // 根據節點深度印出縮排和分支連接
    for (int j = 0; j < depth; j++) {
        if (j == depth - 1) {
            printf("├──");
        } else {
            printf("│  ");
        }
    }

    // 印出節點值
    printf("%c\n", tree[i]);

    printTreeHelper(2 * i, depth + 1);  // 印出左子節點
}

void printTree()
{
    printTreeHelper(1, 0);  // 從根節點開始遞迴印出樹
}

int main()
{
    insert(1, 'A');  
    insert(2, 'B');
    insert(3, 'C');
    insert(4, 'D');
    insert(5, 'E');
    insert(6, 'F');
    insert(7, 'G');

    printTree();  // 印出二元樹的結構

    return 0;
}
