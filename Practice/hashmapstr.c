#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    char *key;
    int val;
    struct node* next;
}node;  

typedef struct linkedlist{
    node* head;
    node* tail;
}linkedlist;


int campstr(char* a,char* b){
    int i = 0;
    while(a[i]!='\0'&&b[i]!='\0'){
        if(a[i]!=b[i]){
            return 1;
        }
        i++;
    }
    if(a[i]=='\0' && b[i]=='\0'){
        return 0;
    }
    return 1;
}

int lenstr(char *a){
    int i = 0;
    while(a[i]!='\0'){
        i++;
    }
    return i;
}

linkedlist * initLinkedlist(){
    linkedlist* ll = (linkedlist*)malloc(sizeof(linkedlist));
    ll->head=ll->tail=NULL;
    return ll;
}

node* createNode(char *key,int val){
    node* nn = (node *)malloc(sizeof(node));
    nn->key = key;
    nn->val = val;
    nn->next = NULL;
    return nn;
}


void insertInLL(linkedlist *ll, char *key,int val){
    if(!ll)return;
    node* nn = createNode(key,val);
    if(!ll->head){
        ll->head=ll->tail=nn;
        return;
    }
    ll->tail->next = nn;
    ll->tail = nn;
}

int checkIfExistInLL(linkedlist*ll, char* key){
    if(!ll)return 0;
    node* temp = ll->head;
    while(temp){
        if(campstr(temp->key,key)==0){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void ExistInsertInLL(linkedlist*ll,char *key,int val){
    if(!ll)return;
    node* temp = ll->head;
    while(temp){
        if(campstr(temp->key,key)==0){
            temp->val = val;
            return;
        }
        temp = temp->next;
    }
}

void removeFromLL(linkedlist*ll,char *key){
    if(!ll)return;
    while(ll->head && campstr(ll->head->key,key)==0){
        if(ll->head==ll->tail){
            ll->head=ll->tail=NULL;
            return;
        }
        ll->head = ll->head->next;
    }
    node* temp = ll->head;
    while(temp->next){
        if(campstr(temp->next->key,key)==0){
            if(ll->tail==temp->next){
                temp->next = NULL;
                ll->tail=temp;
                return;
            }
            temp->next = temp->next->next;
        }else{
        temp = temp->next;
        }
    }
    
}

int getFromLL(linkedlist *ll,char *key){
    if(!ll)return -1e9;
    node *temp = ll->head;
    while(temp){
        if(campstr(temp->key,key)==0){
            return temp->val;
        }
        temp = temp->next;
    }
    return -1e9;
}


void printLL(linkedlist*ll){
    if(!ll)return;
    node* temp = ll->head;
    while(temp){
        printf("{%s %d}->",temp->key,temp->val);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeNode(node *n){
    free(n->key);
    free(n);
}

void freeLL(linkedlist *ll){
    if(!ll)return;
    node *temp = ll->head;
    while(temp){
        node* f = temp;
        temp = temp->next;
        freeNode(f);
    }
    free(ll);
}

void copystr(char* a,char *b){
    int i = 0;
    for(;b[i]!='\0';i++){
        a[i]=b[i];
    }
    a[i]='\0';
}

typedef struct hashmap{
    linkedlist** arr;
    int size;
    int cap;
}hashmap;

hashmap* initHashmap(int cap){
    hashmap* nh = (hashmap*)malloc(sizeof(hashmap));
    nh->arr = (linkedlist**)calloc(cap,sizeof(linkedlist*));
    for(int i = 0;i < cap;i++){
        nh->arr[i]=initLinkedlist();
    }
    nh->size = 0;
    nh->cap = cap;
    return nh;
}
int getIndex(char *key,int cap){
    int index = 0;
    for(int i = 0;key[i]!='\0';i++){
        index+=(int)key[i];
    }
    return index%cap;
}

void insertInHashmap(hashmap* h,char *key,int val){
    if(!h)return;
    int index =  getIndex(key,h->cap);
    linkedlist*ll = h->arr[index];
    if(checkIfExistInLL(ll,key)){
        ExistInsertInLL(ll,key,val);
    }
    else insertInLL(ll,key,val);
}

int getInHashmap(hashmap* h,char *key){
    if(!h)return -1e9;
    int index = getIndex(key,h->cap);
    linkedlist *ll = h->arr[index];
    if(checkIfExistInLL(ll,key)){
        return getFromLL(ll,key);
    }
    return -1e9;
}

void removeFromHashmap(hashmap*h,char *key){
    if(!h)return;
    int index = getIndex(key,h->cap);
    linkedlist* ll = h->arr[index];
    removeFromLL(ll,key);
}

void printHashmap(hashmap *h){
    if(!h)return;
    for(int i = 0;i < h->cap;i++){
        printLL(h->arr[i]);
    }
}

void freeHashmap(hashmap *h){
    for(int i = 0;i < h->cap;i++){
        freeLL(h->arr[i]);
    }
    free(h->arr);
    free(h);
}

int main(){
    linkedlist*ll  = initLinkedlist();
    int n;
    scanf("%d",&n);
    char word[100];
    int p = 0;
    hashmap* h = initHashmap(10);
    while(scanf(" %[^' '\n]",word)){
        if(campstr(word,"E")==0)break;
        int len = lenstr(word);
        char* s = (char*)calloc(len+1,sizeof(char));
        copystr(s,word);
        insertInHashmap(h,s,1);
        // insertInLL(ll,s,p++);
    }

    char* s = (char*)calloc(2,sizeof(char));
    s[0]='a';
    s[1]='\0';
    insertInHashmap(h,s,3);
    // removeFromHashmap(h,s);
    printHashmap(h);
    printf("%d \n",getInHashmap(h,s));
    freeHashmap(h);

    // char* j = (char*)calloc(2,sizeof(char));
    // j[0]='j';
    // j[1]='\0';
    // printLL(ll);
    // printf("%d - \n",checkIfExistInLL(ll,j));
    // removeFromLL(ll,j);
    // printLL(ll);
    // insertInLL(ll,j,p++);
    // printLL(ll);

}