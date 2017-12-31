#include <stdio.h>

void starp(int l){
    if(l==0){
        return;
    }
    starp(l-1);
    int i;
    for(i=0;i<l;i++){
        printf("*");
    }
    printf("\n");
}

void main(){
    starp(10);
}