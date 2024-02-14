#include<stdio.h>
int partition(int *arr,int n){
    int pivet = 0 , i = 1 , j = n - 1 ;
    while(i<=j){
        if(*(arr+i)<*(arr)){
            i++;
        }
        else{
            int t = *(arr+i);
            *(arr+i) = *(arr+j);
            *(arr+j) = t;
            j--;
        }
    }
    int t = *(arr);
    *(arr) = *(arr+j);
    *(arr+j) = t;
    return j;
}
void sort(int *arr,int n){
    if(n<=1)return; 
    int point = partition(arr,n);
    sort(arr,point);
    sort(arr+point+1,n-(point+1));
}

int main(){
    int n;
	scanf("%d",&n);
	int arr[n];
	for(int index =0 ;index<n;index++){
	    scanf("%d",arr+index);
	}
	sort(arr,n);
	for(int index =0 ;index<n;index++){
	    printf("%d ",*(arr+index));
	}
	printf("\n");
	return 0;
}