#include "useful.h"
#define TERM_MAX 100
/**
 * @brief 紀錄稀疏矩陣的matrix
 *
 * @param row 行數
 * @param col 列數
 * @param value 值
 * @note term[0] 存放矩陣的行寬度、列寬度和稀疏矩陣非零的數量
 */
typedef struct terms
{
    int row;
    int col;
    int value;
} terms;
/**
 * @brief 快速翻轉矩陣A把結果存到矩陣B
 *
 * @param A 輸入的矩陣
 * @param B 輸出的矩陣
 * @note 對矩陣A進行掃描 針對col= i(0-col_num)的數值加到矩陣B中！
 */
void FastTranspose(terms A[], terms B[])
{
    int Col_num = A[0].col, Row_num = A[0].row, nums_terms = A[0].value;
    /*set matrix B*/
    B[0].row = A[0].col;
    B[0].col = A[0].row;
    B[0].value = A[0].value;
    int current = 1; // 起始加入的陣列的位置
    int startPos[TERM_MAX] = {0};
    int rowsATerm[TERM_MAX] = {0}; // 紀錄翻轉後的row0...n 到底有幾個
    if (nums_terms > 0)
    {
        // 紀錄有幾項
        for (int i = 1; i <= nums_terms; i++)
        {
            rowsATerm[A[i].col]++;
        }
        // 算出每項的起始位置
        startPos[0] = 1; // 第一項起始一定為1
        for (int i = 1; i < nums_terms; i++)
        {
            startPos[i] = rowsATerm[i - 1] + startPos[i - 1];
        }

        // 根據需要擺放到計算好的位置
        for (int i = 1; i <= nums_terms; i++)
        {
            int where = startPos[A[i].col]; // 通過表格找到要放到B的第幾個
            B[where].col = A[i].row;
            B[where].row = A[i].col;
            B[where].value = A[i].value;
            startPos[A[i].col]++;
        }
    }
}
/**
 * @brief 翻轉矩陣A把結果存到矩陣B
 *
 * @param A 輸入的矩陣
 * @param B 輸出的矩陣
 * @note 對矩陣A進行掃描 針對col= i(0-col_num)的數值加到矩陣B中！
 */
void Transpose(terms A[], terms B[])
{
    int Col_num = A[0].col, Row_num = A[0].row, nums_terms = A[0].value;
    /*set matrix B*/
    B[0].row = A[0].col;
    B[0].col = A[0].row;
    B[0].value = A[0].value;
    int current = 1; // 起始加入的陣列的位置
    if (nums_terms > 0)
    {

        for (int col = 0; col < Col_num; col++)
        {
            for (int j = 1; j <= nums_terms; j++)
            {
                if (A[j].col == col) // 如果掃苗A的第j項發現col是我們要找的 則加入矩陣B內
                {                    // 加到B內
                    B[current].row = A[j].col;
                    B[current].col = A[j].row;
                    B[current].value = A[j].value;
                    current++;
                }
            }
        }
    }
}
void storeSum(terms D[], int row, int col, int *sum)
{
    // 當數值大於0可以存入 會清空
    if (*sum)
    {
        // D[0].value += 1 ; // 多一項存入
        madd_element(D, row, col, *sum);
        *sum = 0; // 歸0
    }
}
/**
 * @brief 矩陣A 與 矩陣B 相乘
 *
 * @param A 輸入A
 * @param B 輸入B
 * @param D 輸出矩陣
 */
void mmult(terms A[], terms B[], terms D[])
{
    // 2*3 *3 *2
    // Fast transpose
    terms newB[TERM_MAX];
    m_init(newB, B[0].col, B[0].row);
    FastTranspose(B, newB);
    int row_begin = 1;
    int totalA = A[0].value, totalB = B[0].value, cols_A = A[0].col, rows_B = newB[0].row;
    if (cols_A != rows_B)
        return; // error
    m_init(D, A[0].row, B[0].col);
    int sum = 0;
    // 需要新增項是讓for迴圈停下！
    //  Row 0 * Row 0
    A[totalA + 1].row = A[0].row; // 5個
    newB[totalB + 1].row = B[0].col;
    newB[totalB + 1].col = 0;
    int row = A[1].row;    // rowA 0 當前正在計算的row
    int col = newB[1].row; // rowB 0 當前正在計算的col

    for (int i = 1; i <= totalA;) // D[]
    {
        col = newB[1].row;
        /* 下面是處理 newB row x*/
        for (int j = 1; j <= totalB + 1;)
        {
            if (A[i].row != row) // 如果不在rowA計算的位置 代表跑完
            {
                storeSum(D, row, col, &sum); // row , col(newB row)
                i = row_begin;               // 重頭跑A[1]開始
                for (; newB[j].row == col; j++)
                    ; // 找到row == column的下一個目標
                col = newB[j].row;
            }
            else if (newB[j].row != col) // 如果不在rowB 當前計算的位置 代表跑完
            {
                storeSum(D,row,col,&sum) ;
                col = newB[j].row ; // 設定成新的j開始掃
                i = row_begin ; 
            }
            else
            {
                switch (COMPARE(A[i].col, newB[j].col))
                {
                case 1:  // 例如當前是 A= 0,1  newB = 0,0
                    j++; // newB要下一項
                    break;
                case 0:
                    sum += A[i].value * newB[j].value;
                    i++;
                    j++;
                    break;
                case -1: // 當前 A = 0,1 newB = 0,2
                    i++;
                    break;
                }
            }
        }
        /*處理下一個rowA*/
        for(;A[i].row == row ; i ++); // 假設當前是 row = 0 ; 它會跳過 row =0 的找到 row = 1 的項
        row_begin = i ; 
        row = A[i].row ; 
        

    }
}
/**
 * @brief 對矩陣A初始化設定
 *
 * @param A 輸入的矩陣
 * @param row_length 設定ROW寬度
 * @param col_length 設定COL寬度
 */
void m_init(terms A[], int row_length, int col_length)
{
    A[0].row = row_length;
    A[0].col = col_length;
    A[0].value = 0; // 初始化沒有任何項
}
/**
 * @brief 把稀疏矩陣的元素加到陣列A中
 *
 * @param A
 * @param value
 */
void madd_element(terms A[], int row, int col, int value)
{
    if (value != 0)
    {
        A[0].value += 1;
        A[A[0].value].row = row;
        A[A[0].value].col = col;
        A[A[0].value].value = value;
    }
}
/**
 * @brief 顯示矩陣A的樣子
 *
 * @param A
 */
void mprint(terms A[])
{
    printf("================================================================\n");
    for (int row = 0; row < A[0].row; row++)
    {
        for (int col = 0; col < A[0].col; col++)
        {
            // row , col 表示當前的數值
            int set = 0;
            // 查詢是否有在A是否這個項
            for (int n = 1; n <= A[0].value; n++)
            {
                if (A[n].row == row && A[n].col == col)
                {
                    set = 1;
                    printf("\t%2d\t", A[n].value);
                }
            }
            if (set == 0)
            {
                printf("\t0\t");
            }
        }
        printf("\n");
    }
}
/**
 * @brief 顯示稀疏矩A陣表 for debug
 * @param A 矩陣
 */
void mprintlist(terms A[])
{
    printf("=====================================================\n");
    printf("\trows\tcols\tvalues\n");
    for (int listith = 1; listith <= A[0].value; listith++)
    { // rows cols value ;
        printf("\t%2d\t%2d\t%2d\n", A[listith].row, A[listith].col, A[listith].value);
    }
}
int main()
{
    terms A[TERM_MAX], B[TERM_MAX],D[TERM_MAX];
    // A設定
    m_init(A, 3, 3);
    m_init(B, 3, 3);

    madd_element(A, 0, 0, 1);
    madd_element(A, 0, 1, 1);
    madd_element(A, 0, 2, 1);
    madd_element(A, 1, 0, 3);
    madd_element(A, 2, 1, 3);
    madd_element(A, 2, 2, 3);
    mprint(A) ; 
    madd_element(B, 0, 0, 2);
    madd_element(B, 1, 1, 2);
    madd_element(B, 2, 2, 2);
    // madd_element(A, 1, 0, 3);
    // madd_element(A, 2, 1, 3);
    // madd_element(A, 2, 2, 3);
    mprint(B);
    mmult(A,B,D);
    mprint(D);
    // FastTranspose(A, B); /* 可能有城市寫錯！*/
    // mprint(B);

    return 0;
}