#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int ch;
    char key;
    struct node* next;
}node;

typedef struct stack{
    node *head;
}stack;

typedef struct hashmap{
    stack *stk;
    int size;
}hashmap;

hashmap* initHashmap(int size){
    hashmap* h = (hashmap*)malloc(sizeof(hashmap));
    stack *stk = (stack*)calloc(sizeof(stack*),size);
    for(int i = 0;i < size;i++){
        (stk+i)->head = NULL;
        // printf("as\n");
    }
    h->stk = stk;
    h->size = size;
    return h;
}

int genKey(char key,int size){
    return key%size;
}

void pushInStack(stack *s,char key, int c){
    node* n = (node *)malloc(sizeof(node));
    n->ch = c;
    n->key=key;
    n->next = NULL;
     if(!s->head){
        s->head = n;
        return;
     }
     n->next = s->head;
     s->head = n;
}

void putInHashmap(hashmap* h,char key,int c){
    int index = genKey(key,h->size);
    pushInStack(h->stk+index,key,c);
}   

char getInHashmap(hashmap* h,char key){
    int index = genKey(key,h->size);
    stack* s = h->stk+index;
    node *temp = s->head;
    while(temp){
        if(temp->key==key)return temp->ch;
        temp = temp->next;
    }
    return 0; 
}

void printStack(stack * s){
    node * temp = s->head;
    while(temp){
        printf("%c ",temp->ch);
        temp = temp->next;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    // // Allocate memory for n characters
    // char *arr = (char *)calloc(n + 1, sizeof(char));
    // if (arr == NULL) {
    //     fprintf(stderr, "Memory allocation failed\n");
    //     return 1;
    // }
    // getchar();

    // fgets(arr, n + 1, stdin);
    // printf("%s\n", arr);
    // free(arr);
    hashmap* h = initHashmap(n);
    putInHashmap(h,'c',1);
    printf("%d \n",getInHashmap(h,'s'));
    return 0;
}
