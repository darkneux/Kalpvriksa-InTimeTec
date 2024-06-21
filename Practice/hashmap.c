#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    int key;
    int data;
    Node* next;
};

typedef struct HashMap {
    Node* arr[100];
} HashMap;

int hashfun(int key) {
    return key % 100;
}

void add(HashMap* hash, int key, int val) {
    int newkey = hashfun(key);
    Node* newnode = malloc(sizeof(Node));
    newnode->key = key;
    newnode->data = val;
    newnode->next = NULL;
    Node *head = hash->arr[newkey];
    while(head){
        if(head->key==key){
            head->data = val;
            return;
        }
        head = head->next;
    }

    if (!hash->arr[newkey]) {
        hash->arr[newkey] = newnode;
    } else {
        newnode->next = hash->arr[newkey];
        hash->arr[newkey] = newnode;
    }
}

int get(HashMap* hash, int key) {
    int newkey = hashfun(key);
    Node* head = hash->arr[newkey];
    while (head) {
        if (head->key == key) {
            return head->data;
        }
        head = head->next;
    }
    printf("Key Does not exist\n");
    return -1;
}

void print(HashMap* hash) {
    Node* head;
    for (int i = 0; i < 100; ++i) {
        head = hash->arr[i];
        while (head) {
            printf("[%d - %d]\n", head->key, head->data);
            head = head->next;
        }
    }
}

void hremove(HashMap* hash,int key){
    int newkey = hashfun(key);
    Node * head = hash->arr[newkey];
    if(!head)return;
    if(head->key==key){
        hash->arr[newkey]=head->next;
        return;
    }
    while(head->next && head->next->key==key){
        Node * temp = head->next->next;
        head->next = temp;
    }
}

int main() {
    HashMap h;
    for (int i = 0; i < 100; ++i) {
        h.arr[i] = NULL;
    }

    add(&h, 5, 9);
    add(&h, 105, 18);
    add(&h, 5,100);
    hremove(&h, 105);
    add(&h,205,1);
    printf("%d \n",get(&h,205));
    printf("%d \n ------- \n",get(&h,15));
    print(&h);

    return 0;
}
