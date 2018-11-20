#include <math.h>
#include "boolean.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char T[101];
    int panjang;
} Kata;

char input[];
char CC;
Kata KataInput;
int i;
int i_simpan;



float OlahPower();


void PrintKata(Kata K){
    int j=1;
    while(j<=K.panjang){
        printf("%c",K.T[j]);
        j++;
    }
    printf("\n");
}
void Prev(){
    i--;
    CC = KataInput.T[i];
}

void Next(){
    i++;
    CC = KataInput.T[i];
}


boolean IsNumber(){
    return 
    (CC=='0')||
    (CC=='1')||
    (CC=='2')||
    (CC=='3')||
    (CC=='4')||
    (CC=='5')||
    (CC=='6')||
    (CC=='7')||
    (CC=='8')||
    (CC=='9');
}

float Expression();


Kata ReverseKata(Kata K){
    Kata Ktemp;
    int j=1; 
    Ktemp.panjang = K.panjang;
    while(j<=K.panjang){
        Ktemp.T[j] = K.T[K.panjang-j+1];
        j++;
    }
    return Ktemp;
}


int KataToInt(Kata K){
    int j=1;
    int sum=0;
    while(j<=K.panjang){
        sum = sum*10 + (K.T[j]-'0');
        j++;
    }
    return sum;
}


float KataToAngka(){
    Kata KTemp;
    int j=1;
    float result_dalam;
    KTemp.panjang=0;
    while (IsNumber()){
        KTemp.T[j] = CC;
        KTemp.panjang++;
        j++;
        Prev();
    } //Not is number
    if(CC == '.'){
        Kata Kdepan;//bagian depan desimal
        Kdepan.panjang =0 ;
        j=1;
        Prev();
        while(IsNumber()){
            Kdepan.T[j] = CC;
            Prev();
            Kdepan.panjang++;
            j++;
        }//not number again
        result_dalam = (float) KataToInt(ReverseKata(Kdepan)) + (float) KataToInt(ReverseKata(KTemp)) * pow(10,(-KTemp.panjang));
    } else {
        Kata KReverse = ReverseKata(KTemp);
        result_dalam = (float)KataToInt(KReverse);
    }

    if((CC=='-')&&((KataInput.T[i-1]=='(')||(i==1))) {
        result_dalam *= -1;
        Prev();
    }
    return result_dalam;

}


float Factor(){
    if (CC==')'){
        Prev();
        float value = Expression();
        if(CC='('){
            Prev();
            if((CC=='-')&&(KataInput.T[i-1]=='(')){
                Prev();
                value*=-1;
            }
            return value;
        } else {
            printf("SYNTAX ERROR.");
            exit(0);
        }
    } else {
        return KataToAngka();
    }



}

float Power(){
    float curr_value = Factor();
    if (CC== '^'){
        float temp_value;
        while((CC== '^')&&(i>0)){
            Prev();
            temp_value = Factor();
            curr_value = pow(temp_value,curr_value);
            if(isnan(curr_value)){
                printf("MATH ERROR\n");
                exit(0);
            }
        }
    } else {
        return curr_value;
    }
}

float Term(){
    float factor_value = Power();
    if (CC == '*'){
        Prev();
        float value = Term();
        return value * factor_value;
    } else if (CC== '/') {
        if (factor_value == 0) {
            printf("MATH ERROR : DIVISION BY ZERO\n");
            exit(0);
        } else {
            Prev();
            float value = Term();
            return value / factor_value;
        }
    } else {
        return factor_value;
    }

}

float Expression() {
    float term_value = Term();
    if(CC=='+'){
        Prev();
        return  Expression() + term_value;
    } else if (CC=='-'){
        Prev();
        return Expression() - term_value;
    } else {
        return term_value; //End of expresion reading
    }

}

int main(){
    scanf("%s",input);
    KataInput.panjang = strlen(input);
    i=0;
    //Pindah string ke kata
    while(i<strlen(input)){
        KataInput.T[i+1] = input[i];
        i++;
    }
    KataInput.T[0] = 'E';
    i = KataInput.panjang;
    CC = KataInput.T[KataInput.panjang];
    float Result = Expression();
    printf("%f\n",Result);
    return 0;
}