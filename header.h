#ifndef header_H
#define header_H
#include "boolean.h"
#include <math.h>

extern char CC;
extern int i;
extern char kalimat[1000];

int KarakterToInteger(char c){
    return(c - '0');
}

void ADV(){
    i++;
    CC = kalimat[i];
}

boolean IsNumber(){
    return ((CC =='1') || (CC == '2') || (CC == '3') || (CC == '4') || (CC == '5') || (CC == '6') || (CC == '7') || (CC == '8') || (CC == '9'));
}

boolean IsZero(){
    return (CC == '0');
}

boolean IsDot(){
    return(CC == '.');
}

boolean IsOpr(){
    return ((CC == '+') || (CC == '-') || (CC == '*') || (CC == '/') || (CC == '^'));
}

int Ekspresi();

int Factor(){
    int number_value;
    int temp;
    
    if(CC == '-'){
        ADV();
        temp = Factor();
        return (-temp);
    }
    else if(IsNumber()){
        temp = KarakterToInteger(CC);
        ADV();
        if(!IsNumber()){
            return temp;
        }
        else{
            while(IsNumber()){
                temp = temp*10 + KarakterToInteger(CC);
                ADV();
            }
        }
        return temp;
    }
    else if(CC == '('){
        ADV();
        number_value = Ekspresi();
        if(CC == ')'){
            ADV();
            return number_value;
        }
        else{
            printf("Syntax error!\n");
        }
    }
}

int Power(){
    int power_value,i,temp,n;

    power_value = Factor();
    if(CC == '^'){
        ADV();
        temp = power_value;
        n = Factor();
        for(i=1;i<n;i++){
            temp *= power_value;
        }
        return(temp);
    }
    else{
        return power_value;
    }
}

int Term(){
    int factor_value;

    factor_value = Power();
    //ADV();
    if(CC == '*'){
        ADV();
        return(factor_value * Factor());
    }
    else if(CC == '/'){
        ADV();
        return(factor_value / Factor());
    }
    else{
        return factor_value;
    }
}

int Ekspresi(){
    int term_value,temp;

    term_value = Term();
    //ADV();
    if(CC == '+'){
        ADV();
        return(term_value + Ekspresi());
    }
    else if(CC == '-'){
        ADV();
        temp = Factor();
        return(term_value - temp + Ekspresi());
    }
    else{
        return term_value;
    }
}

#endif
