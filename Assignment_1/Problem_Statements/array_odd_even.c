#include<stdio.h>
void main(){
  int n,x;
  printf("Enter Number of Values : \n");
  scanf("%d",&n);
  int odd_arr[n], o_inx=-1;
  int even_arr[n], e_inx=-1;
  for(int i = 0;i < n;++i){
     scanf("%d",&x);
     if(x%2)
      odd_arr[++o_inx]= x;
     else
      even_arr[++e_inx]=x;
   }
    printf("Even Array : [ ");
    for (int i = 0; i <= e_inx; ++i)
        printf("%d ", *(even_arr+i));
    printf("]\nOdd Array : [ ");
    for (int i = 0; i <= o_inx; ++i)
        printf("%d ", *(odd_arr+i));
    printf("]\n");
return;
}


