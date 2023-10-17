#include "useful.h"
typedef struct polyNode *polyPointer; 
typedef struct polyNode
{
    float coef ; 
    int exp ; 
    polyPointer next ; 
}polyNode;
polyPointer a , b; 
/** 函數名稱:attach  
 * @param : poly 指標指向
 * @param : coef 係數 
 * @param : exp 次數
*/
void attach(polyPointer *poly,float coef , int exp)
{
    // initalize a node 
    polyPointer temp ; 
    MALLOC(temp,sizeof(*temp)) ; 
    temp->coef =coef ; 
    temp->exp = exp ; 
    // 


}



int main()
{


    return 0 ; 
}