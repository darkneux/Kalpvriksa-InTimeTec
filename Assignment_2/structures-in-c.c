#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h> 

//Represents an item in the cart
typedef struct item_t
{
	char *item_name;
	int item_cost;
} item;

typedef struct map_t
{
    char *item_name;
    int item_count;
}item_map;

//Store the items in the cart array declared here.
item *cart[100];
item_map map[100];


int main() {
    int n,x=0;
    
    int total_cost=0;
    scanf("%d",&n);
    
     for (int i = 0; i < n; ++i) {
        cart[i] = (item *)malloc(sizeof(item));
        cart[i]->item_name = (char *)malloc(100 * sizeof(char));
        scanf("%[^,],%d", cart[i]->item_name, &cart[i]->item_cost);
        //scanf("%d", &cart[i]->item_cost);
        bool flag = false;
        for (int j = 0; j < x; ++j) {
            if (strcmp(cart[i]->item_name, map[j].item_name)==0) {
                map[j].item_count++;
                flag = true; break;
            }
        }
        if (!flag) {
            map[x].item_name = (char *)malloc((strlen(cart[i]->item_name) + 1) * sizeof(char));
            strcpy(map[x].item_name, cart[i]->item_name);
            map[x++].item_count = 1;
        }

        total_cost += cart[i]->item_cost;
    }
    
    printf("item list");
    for (int i = 0; i < n; ++i) {
        printf("%s,%d", cart[i]->item_name, cart[i]->item_cost);
    }
    printf("\n");
    printf("Total cost %d\n",total_cost);
    printf("item quantities");
    
   for (int i = 0; i < x; ++i) {
        printf("%s - %d", map[i].item_name, map[i].item_count);
       }
    
    for (int i = 0; i < n; ++i) {
        free(cart[i]->item_name);
        free(cart[i]);
       }
    return 0;
}
