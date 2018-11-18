#include <stdio.h>
#include <string.h>
#include "boolean.h"
#include "stackt.h"
#include "header.h"
//#include "mesinkar.h"
char CC;
int i;
char kalimat[1000];
infotype BB; //buangan pop 
Stack S;

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

int main(){
    //scanf("%s",kalimat);
    gets(kalimat);
    i = 0;
    CC = kalimat[0];
    CreateEmpty(&S);
    Push(&S, 'Z');
    while(i < strlen(kalimat)){
        if(CC == ' '){
            ADV();
        }
        else if (IsNumber() && InfoTop(S) == 'Z'){ // A.Z | XZ
            Push(&S, 'X');
            ADV();
        }
        else if ((CC == '(') && ((InfoTop(S) == 'Z') || (InfoTop(S) == '('))){//(,Z | (XZ atau (,( | (X(
            Push(&S, 'X');
            Push(&S, '(');
            ADV();
        }
        else if ((CC == '-') && (InfoTop(S) == 'Z')){ // -,Z | YX
            Push(&S, 'Y');
            ADV();
        }
        else if (IsNumber() && InfoTop(S) == '('){// A,( | X(
            Push(&S, 'X');
            ADV();
        }
        else if ((CC == '-') && (InfoTop(S) == '(')){ //-,( | Y(
            Push(&S, 'Y');
            ADV();
        }
        else if (IsNumber() && InfoTop(S) == 'Y'){ // A, Y | X 
            Pop(&S, &BB);
            Push(&S, 'X');
            ADV();
        }
        else if (IsNumber() && InfoTop(S) == 'X'){// A,X | X
            ADV();
        }
        else if(IsOpr() && InfoTop(S) == 'X'){// Opr, X | O
            Pop(&S, &BB);
            Push(&S, 'O');
            ADV();
        }
        else if (IsNumber() && InfoTop(S) == 'O'){// A,O | X
            Pop(&S, &BB);
            Push(&S, 'X');
            ADV();
        }
        else if ((CC == '(') && InfoTop(S) == 'O'){//(,O | (X
            Pop(&S, &BB);
            Push(&S, 'X');
            Push(&S, '(');
            ADV();
        }
        else if (CC == ')' && (InfoTop(S) == 'X' || InfoTop(S) == 'D')){//),X | pop 2x
            Pop(&S, &BB);
            Pop(&S, &BB);
            ADV();
        }
        else if(IsZero() && InfoTop(S) == 'Z'){//0,Z | 0Z
            Push(&S, '0');
            ADV();
        }
        else if(IsZero() && InfoTop(S) == 'X'){//0,X | X 
            ADV();
        }
        else if(IsZero() && InfoTop(S) == '('){//0,( | 0(
            Push(&S, '0');
            ADV();
        }
        else if(IsDot() && ((InfoTop(S) == '0') || (InfoTop(S) == 'X'))){//.,0 | . atau .,X | .
            Pop(&S, &BB);
            Push(&S, '.');
            ADV();
        }
        else if((IsNumber() || IsZero()) && InfoTop(S) == '.'){// A,0| X atau 0,. | X
            Pop(&S, &BB);
            Push(&S, 'D');
            ADV();
        }
        else if(IsZero() && InfoTop(S) == 'O'){
            Pop(&S, &BB);
            Push(&S, '0');
            ADV();
        }
        else if(IsOpr() && InfoTop(S) == '0'){
            Pop(&S, &BB);
            Push(&S, 'O');
            ADV();
        }
        else if (IsNumber() && InfoTop(S) == 'D'){// A,X | X
            ADV();
        }
        else if(IsOpr() && InfoTop(S) == 'D'){// Opr, X | O
            Pop(&S, &BB);
            Push(&S, 'O');
            ADV();
        }
        else{
            printf("Syntax Error\n");
            break;
        }
    }
    
    if(i == strlen(kalimat)){
        if(InfoTop(S) == 'X' || InfoTop(S) == 'D'){
            Pop(&S, &BB);
            if(InfoTop(S) == 'Z'){
                printf("Engstap Bosq\n");
            }
        }
    }
}
