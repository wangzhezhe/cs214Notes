#include "stdio.h"
#define MAXNUM 10

//test preprocessing
//class 214
void main(){
    int i,j;
    for(i=0;i<MAXNUM;i++){
        for(j=0;j<i;j++){
            printf("*");
        }
        printf("\n");
    }
}
