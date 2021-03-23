#include <stdio.h>
#include "bracketsStack.h"


int main(){
    int count, op;
    char brac;

    bracketsStack bstack;

    scanf("%d",&count);
    while(count--){
        scanf("%d",&op);
        switch(op){
            case 1:{
                scanf(" %c", &brac);  //**********   %c前面的空格可以跳过输入流中的空白字符    ×××××××××××××××××××
                bstack.push(brac);
                break;
            }
            case 2:{
                bstack.pop();
                break;
            }
            case 3:{
                char tmp;
                try{
                    tmp = bstack.top();
                    printf("%c\n",tmp);
                }
                catch(operateEmptyStackError){}
                break;
            }
            case 4:{
                if(bstack.matching())
                    printf("YES\n");
                else printf("NO\n");
                break;
            }
            default:break;
        }
    }
}