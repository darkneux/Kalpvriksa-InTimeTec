#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int key;
    int data;
    int is_o;
    int is_d;
} node;


typedef struct hashmap {
    node* arr;
    int size;
    int cap;
} hashmap;

int getIndex(int key, int size) {
    return key % size;
}

hashmap* initHashmap(int size) {
    hashmap* h = (hashmap*)malloc(sizeof(hashmap));
    h->arr = (node*)calloc(size, sizeof(node));
    for (int i = 0; i < size; i++) {
        (h->arr + i)->is_o = 0;
        (h->arr + i)->is_d = 0;
    }
    h->size = size;
    h->cap = 0;
    return h;
}

void insertInHashmap(hashmap* h, int key, int val) {
    int index = getIndex(key, h->size);
    int i = 0;
    while (((h->arr + ((index + i) % h->size))->is_o == 1) && ((h->arr + ((index + i) % h->size))->is_d == 0)) {
        i++;
    }
    int finalIndex = (index + i) % h->size;
    (h->arr + finalIndex)->key = key;
    (h->arr + finalIndex)->data = val;
    (h->arr + finalIndex)->is_o = 1;
    (h->arr + finalIndex)->is_d = 0;
}

int getInHashamp(hashmap* h, int key) {
    int index = getIndex(key, h->size);
    int i = 0;
    while ((h->arr + ((index + i) % h->size))->is_o != 0) {
        if (((h->arr + ((index + i) % h->size))->is_d == 0) && ((h->arr + ((index + i) % h->size))->key == key)) {
            return (h->arr + ((index + i) % h->size))->data;
        }
        i++;
    }
    return 0; 
}

void removeInHashmap(hashmap* h, int key) {
    int index = getIndex(key, h->size);
    int i = 0;
    while ((h->arr + ((index + i) % h->size))->is_o != 0) {
        if ((h->arr + ((index + i) % h->size))->key == key) {
            (h->arr + ((index + i) % h->size))->is_d = 1;
            return;
        }
        i++;
    }
}

int main() {
    // hashmap* h = initHashmap(10);
    // insertInHashmap(h,2,1);
    // insertInHashmap(h,12,2);
    // printf("%d\n", getInHashamp(h,2));
    // printf("%d\n", getInHashamp(h,12));
    // removeInHashmap(h,12);
    // printf("%d\n", getInHashamp(h,12));
    // insertInHashmap(h,22,3);
    // printf("%d\n", getInHashamp(h,22));
    // char *a = (char *)calloc(2,sizeof(char));
    // fgets(a,1,stdin);
    // printf("%s\n",a);
    initializedeleted();
    printf("%p",deleted);
    return 0;
}
