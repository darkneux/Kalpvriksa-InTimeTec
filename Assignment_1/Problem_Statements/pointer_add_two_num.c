#include<stdio.h>
int add(int *a,int *b){
   return (*a + *b);
}
void main(){
 int a,b,sum;
 printf("Enter Two Numbers :\n");
 scanf("%d %d",&a,&b);
 sum = add(&a,&b);
 printf("sum : %d\n",sum);
return;
}
