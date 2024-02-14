#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<string.h>
#include<unordered_map>
using namespace std;


//Represents an item in the cart
typedef struct item_t
{
	char *item_name;
	int item_cost;
} item;



//Store the items in the cart array declared here.
item *cart[100];

int main() {
    int n,x=0;
    int total_cost=0;
    vector<string> item_vec;
    unordered_map<string, int> item_count;
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) {
        cart[i] = (item *)malloc(sizeof(item));
        cart[i]->item_name = (char *)malloc(100 * sizeof(char));
        scanf("%[^,],%d", cart[i]->item_name, &cart[i]->item_cost);
        if(!item_count.count(cart[i]->item_name)){
            item_vec.push_back(cart[i]->item_name);
            x++;
        }
        item_count[cart[i]->item_name]++;
        total_cost+=cart[i]->item_cost;
    }
    printf("item list");
    for(int i = 0;i < n;++i){
        cout<<cart[i]->item_name<<","<<cart[i]->item_cost;
        if(i==n-1)cout<<endl;
    }
    cout<<"Total cost "<<total_cost<<endl;
    cout<<"item quantities";
    for(int i = 0;i < x;++i){
        cout<<item_vec[i]<<" - "<<item_count[item_vec[i]];
    }
    
    
  
    return 0;
}
