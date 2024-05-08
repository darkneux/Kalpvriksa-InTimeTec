#include<stdio.h>
#include<stdlib.h>

typedef enum {
    INT,
    CHAR,
    FLOAT,
} DataType;


typedef struct Node {
    DataType type;
    void *data;
    struct Node *next;
} Node;

Node* createNode(void *val,DataType type){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->type = type;
    
    switch (type) {
        case INT:
            newNode->data = malloc(sizeof(int));
            *((int*)(newNode->data)) =*((int*)val);
            break;
        case CHAR:
            newNode->data = malloc(sizeof(char));
            *((char*)(newNode->data))= *((char*)val);
            break;
        case FLOAT:
            newNode->data = malloc(sizeof(float));
            *((float*)(newNode->data))= *((float*)val);
            break;
    }
    return newNode;
}

Node* insertNodeAtHead(Node* head,void *val, DataType type){
    Node* newNode= createNode(val, type);
    if(head == NULL){
        head = newNode;
        return head;
    }
    newNode->next = head;
    head = newNode;
    return head;
}

Node* insertNodeAtTail(Node* head,void *val,DataType type){
    Node* newNode= createNode(val, type);
    Node* temp = head;
    if(temp == NULL){
        return insertNodeAtHead(head, val, type);
    }
    while(temp->next){
        temp = temp->next;
    }
    temp->next= newNode;
    return head;
}

void printList(Node* head){
    while(head){
        switch (head->type) {
            case INT:
                 printf("%d  ",*((int*)(head->data)));
                break;
            case CHAR:
                printf("%c  ",*((char*)(head->data)));
                 break;
            case FLOAT:
                printf("%.2f  ",*((float*)(head->data)));
                break;
        }
        head = head->next;
    }
}

void deleteCompleteList(Node* head){
    while(head){
        Node* temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

int main(){
    Node* head =NULL;
    int intVal1= 59;
    int intVal2 = 45;
    char charVal= 'A';
    float floatVal =2.6;

    head=insertNodeAtTail(head,&intVal1,INT);
    head=insertNodeAtTail(head,&intVal2,INT);
    head=insertNodeAtHead(head,&charVal,CHAR);
    head=insertNodeAtTail(head,&floatVal,FLOAT);
    
    printList(head);
    printf("\n");
    deleteCompleteList(head);
    return 0; 
}
