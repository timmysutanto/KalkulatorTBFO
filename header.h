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

float Ekspresi();

float Factor(){
    float number_value;
    float temp;
    float desimal;
    float koma;
    float hasil;
    
    if(CC == '-'){
        ADV();
        temp = Factor();
        return (-temp);
    }
    else if(IsNumber() || IsZero()){
        temp = 0;
        while(IsNumber() || IsZero()){
                temp = temp*10 + KarakterToInteger(CC);
                ADV();
            }
            //printf("sekarang %c\n",CC);
            if(IsDot()){
                koma = 0.1;
                hasil = 0;
                ADV();
                while(IsNumber() || IsZero()){
                    hasil = hasil + koma*KarakterToInteger(CC);
                    koma *= 0.1;
                    //printf("%f\n",hasil);
                    ADV();
                }
                temp += hasil;
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
    else if(!IsNumber()){
            return temp;
        }
}

float Power(){
    float power_value,temp,n;
    int i;

    power_value = Factor();
    if(CC == '^'){
        ADV();
        temp = power_value;
        n = Factor();
        //for(i=1;i<n;i++){
          //  temp *= power_value;  
        temp = powf(power_value, n);
        //}
        return(temp);
    }
    else{
        return power_value;
    }
}

float Term(){
    float factor_value;

    factor_value = Power();
    //ADV();
    if(CC == '*'){
        ADV();
        return(factor_value * Ekspresi());
    }
    else if(CC == '/'){
        ADV();
        return(factor_value / Ekspresi());
    }
    else{
        return factor_value;
    }
}

float Ekspresi(){
    float term_value,temp;

    term_value = Term();
    //ADV();
    if(CC == '+'){
        ADV();
        return(term_value + Ekspresi());
    }
    else if(CC == '-'){
        //ADV();
        //temp = Ekspresi();
        return(term_value + Ekspresi());
    }
    else{
        return term_value;
    }
}

#endif