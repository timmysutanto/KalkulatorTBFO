#ifndef header_H
#define header_H
#include "boolean.h"

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
    
    if(IsNumber()){
        //printf("AHayy\n");
        return KarakterToInteger(CC);
    }
    else if(CC == ')'){
        ADV();
        number_value = Ekspresi();
        if(CC == '('){
            ADV();
            return number_value;
        }
        else{
            printf("Syntax error!\n");
        }
    }
}

int Term(){
    int factor_value;

    factor_value = Factor();
    ADV();
    if(CC == '*'){
        return(Factor() * factor_value);
    }
    else if(CC == '/'){
        return(Factor() / factor_value);
    }
    else{
        return factor_value;
    }
}

int Ekspresi(){
    int term_value;

    term_value = Term();
    //ADV();
    //printf("%c\n",kalimat[i]);
    if(CC == '+'){
        //printf("Masukk\n");
        ADV();
        return(Ekspresi() + term_value);
    }
    else if(CC == '-'){
        ADV();
        return(Ekspresi() - term_value);
    }
    else{
        return term_value;
    }
}

#endif
