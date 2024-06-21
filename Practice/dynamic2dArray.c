#include<stdio.h>
#include<stdlib.h>

int ** allocate2DArray(int size){
    int **ptr;
    ptr = malloc(size * sizeof(int *));
    for(int i = 0;i < size;i++){
        *(ptr + i) = malloc(size * sizeof(int));
    }
   return ptr;
}

void print2DArray(int **ptr,int n){
     for(int i = 0;i < n;i++){
        int *row = *(ptr+i);
        for(int j = 0;j < n; j++){
            printf("%d ", *(row+j));
        }
        printf("\n");
     }
}

void swapXpattern(int **ptr,int n){
    for(int i = 0;i < n;i++){
        int *row = *(ptr+i);
        int *a = row+i;
        int *b = row+n-1-i;
       if(a!=b){
        int t = *a;
        *a = *b;
        *b = t; 
       }
    }
}


int main(){
     int n;
     scanf("%d",&n);
     int **arr = allocate2DArray(n);

     for(int i = 0;i < n;i++){
        int *row = *(arr+i);
        for(int j = 0;j < n; j++){
            scanf("%d", row + j);
        }
     }
     swapXpattern(arr,n);

     print2DArray(arr,n);


    return 0;
}
