#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int key;
    int data;
    struct node * next;
}node;

int hashmapkeyGen(int key, int capacity){
    return key%capacity;
}


typedef struct hashmap{
    int size;
    int  capacity;
    node* (*arr); 
}hashmap;


hashmap* initHashmap(int capacity){
    hashmap *mp = (hashmap *)malloc(sizeof(hashmap));
    mp->arr = (node **)calloc(sizeof(node*),capacity); 
    mp->capacity = capacity;
    mp->size = 0;
    return mp;
}

int insertinll( node** mpindx,int key, int val){
   node * temp =  *mpindx;
   while(temp){
    if(temp->key == key){
        temp->data = val;
        return 0;
    }
    temp = temp->next;
   }
   node *newnode = (node *)malloc(sizeof(node));
   if(!newnode)return 1;
   newnode->key = key;
   newnode->data = val;
   newnode->next =  *mpindx;
   *mpindx = newnode;

   return 0;
}

int checkloadfactor(hashmap *mp){
     int size = mp->size;
    int cap = mp->capacity;
    float loadfactor= (size+1)/(cap*1.0);
    printf("%d %d \n",size,cap);
    printf("%f\n",loadfactor);
    if(loadfactor < .7){
        return 0;
    }
    return 1;
}


int refactorHashmap(hashmap *mp){
    if(!checkloadfactor(mp))return 0;
    return 0;
    
    node* (*nwarr) = NULL;
    nwarr = (node**) calloc(sizeof(node*),(mp->capacity)*2);
    int cap = mp->capacity*2;
    mp->capacity = cap;
    for(int i = 0;i < mp->capacity;i++){
        node* temp = *(mp->arr+i);
        while(temp){
            int index = hashmapkeyGen(temp->key,cap);
            insertinll(nwarr+index,temp->key,temp->data);
            temp = temp->next;
        }
    }
    return 1;
}



int putHashmap(hashmap *mp,int key,int val){
    refactorHashmap(mp);
    int cap = mp->capacity;
    int index = hashmapkeyGen(key,cap);
    node ** mpindx = ((mp->arr)+index);
    if(!insertinll(mpindx,key,val)){
        (mp->size)++;
        return 0;
    }
    return 1;
}

int removeinll(node **mpindx,int key){
    node *temp = *mpindx;
    if(temp->key == key){
        *mpindx = temp->next;
        return 0;
    }
    while(temp->next){
        if(temp->next->key == key){
            temp->next = temp->next->next;
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}



int removeHashmap(hashmap *mp,int key){
    int cap = mp->capacity;
    int index = hashmapkeyGen(key,cap);
    node ** mpindx = (mp->arr+index);

    if(!removeinll(mpindx,key)){
        (mp->size)--;
        return 0;
    }
    return 1;
}

int getHashmap(hashmap *mp, int key){
    int cap = mp->capacity;
    int index = hashmapkeyGen(key,cap);
    node ** mpindx = (mp->arr+index);
    node *temp = *mpindx;
    while(temp){
        if(temp->key == key){
            return temp->data;
        }
        temp = temp->next;
    }
    insertinll(mpindx,key,0);
    return 0;
}



int main(){
    hashmap * mp = initHashmap(1);
    // printf("%p\n",mp->arr);
    // printf("%d\n",mp->size);
    // printf("%d\n",mp->capacity);
    putHashmap(mp,2,10);
    putHashmap(mp,3,11);
    printf("%d\n",mp->size);
    // removeHashmap(mp,2);
    // printf("%d\n",mp->size);
    int a = getHashmap(mp,3);
    printf("%d\n",a);
}


