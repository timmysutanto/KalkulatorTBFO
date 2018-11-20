#include <stdio.h>
#include <string.h>
#include <math.h>
#include "boolean.h"
#include "stackt.h"
#include "header.h"
char CC,tempchar;
int i,tempint,sum;
char kalimat[1000];
infotype BB; //buangan pop 
Stack S;



/*
int prioritas(char c){
    if((c == '-') || (c == '+')){
        return 1;
    }
    else if((c == '*') || (c == '/')){
        return 2;
    }
    else if(c == '^'){
        return 3;
    }
}
*/


int main(){
    //--------------------------------------------------------------------------------------------------------------------
                                                     /*VALIDASI*/
    //--------------------------------------------------------------------------------------------------------------------

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
            printf("Salah wehh\n");
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

    //--------------------------------------------------------------------------------------------------------------------
                                                     /*PERHITUNGAN*/
    //--------------------------------------------------------------------------------------------------------------------
    /*
    CreateEmptyAngka(&StackNum);
    CreateEmpty(&StackOpr);
    i = 0;
    CC = kalimat[i];
    //printf("%d\n",KarakterToInteger(kalimat[i]));
    while(i<=strlen(kalimat)){
        if(IsNumber()){
            PushAngka(&StackNum,KarakterToInteger(kalimat[i]));
        }
        else{
            if(IsEmpty(StackOpr)){
                Push(&StackOpr,kalimat[i]);
            }
            else if(prioritas(kalimat[i]) >= prioritas(InfoTop(StackOpr))){
                Push(&StackOpr,kalimat[i]);
            }
            else if(prioritas(kalimat[i]) < prioritas(InfoTop(StackOpr))){
                Pop(&StackOpr,&tempchar);
                PopAngka(&StackNum,&tempint);
                sum = tempint;
                PopAngka(&StackNum,&tempint);
                if(tempchar == '+'){
                    sum += tempint;
                }
                else if(tempchar == '-'){
                    sum -= tempint;
                }
                else if(tempchar == '*'){
                    sum *= tempint;
                }
                else if(tempchar == '/'){
                    sum /= tempint;
                }
                PushAngka(&StackNum,sum);
            }
        }\\
        ADV();
    }
    printf("%d\n",InfoTopAngka(StackNum));

    */
    i = 0;
    CC = kalimat[0];
    printf("%f\n",Ekspresi());

    return 0;
}
