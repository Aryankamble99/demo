#include "calculator.h"



float add(float a,float b){
    return a+b;
}
float sub(float a,float b){
    return a-b;
}
float mul(float a,float b){
    return a*b;
}
float div(float a,float b){
    return a/b;
}





int main()
{
    float number1,number2,result;
    char oper;
    printf("\n Enter Operation which you want to Perform");
    scanf(" %c",&oper);
    printf("\n Enter Two Numbers");
    scanf("%f%f", &number1,&number2);

    switch(oper)
    {
        case '+':
        result = add(number1, number2);
        printf("\n %f",result);
        break;
        case '-':
        result = sub(number1, number2);
        printf("\n %f",result);
        break;
        case '*':
        result = mul(number1, number2);
        printf("\n %f",result);
        break;
        case '/':
        result = div(number1, number2);
        printf("\n %f",result);
        break;
        default:
        printf("\n Please enter valid Sign");
    }
    return 0;
}


