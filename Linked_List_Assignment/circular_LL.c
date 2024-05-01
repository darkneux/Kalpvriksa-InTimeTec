#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;
struct Node {
    int data;
    Node* next;
};

Node* createNode(int val){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = val;
    return newNode;
}

Node* insertNodeAtHead(Node* head, int val){
    Node* newNode = createNode(val);
    if(head == NULL){
        newNode->next =newNode;
        head = newNode;
        return head;
    }
    newNode->next = head;
    Node* temp = head;
    while(temp->next !=head){
        temp = temp->next;
    }
    temp->next = newNode;
    head = newNode;
    return head;
}

Node* insertNodeAtTail(Node* head,int val){
    if(head == NULL){
        return insertNodeAtHead(head, val);
    }
    Node* newNode = createNode(val);
    Node* temp = head;
    while(temp->next != head){
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    return head;
}

void printList(Node* head){
    if(head == NULL){
        printf("empty list\n");
        return;
    }
    Node* temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while(temp != head);
    printf("\n");
}

void deleteCompleteList(Node* head){
    if(head == NULL){
        return;
    }
    Node* current = head;
    Node* next = NULL;
    do {
        next = current->next;
        free(current);
        current = next;
    } while(current != head);
}

int main(){
    Node* head = NULL;
    head = insertNodeAtTail(head, 59);
    head = insertNodeAtTail(head, 45);
    head = insertNodeAtTail(head, 32);
    printList(head);
    printf("--- \n");

    deleteCompleteList(head);
    head = NULL;
    

    return 0; 
}
