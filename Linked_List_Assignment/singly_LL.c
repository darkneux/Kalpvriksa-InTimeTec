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
        head = newNode;
        return head;
    }
    newNode->next = head;
    head = newNode;
    return head;
}

Node* insertNodeAtTail(Node* head, int val){
    Node* newNode = createNode(val);
    Node* temp = head;
    if(temp == NULL){
        return insertNodeAtHead(head, val);
    }
    while(temp->next){
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

Node* insertNodeAtPosition(Node* head, int val, int position){
    if(position == 1){
        return insertNodeAtHead(head, val);
    }
    Node* temp = head;
    Node* newNode = createNode(val);
    int i = 1;
    while(i != position - 1){
        i++;
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

Node* deleteNodeAtHead(Node* head){
    if(head == NULL){
        return NULL;
    }
    Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

Node* deleteNodeAtTail(Node* head){
    if(!head){
        return NULL;
    }
    if(!(head->next)){
        free(head);
        head = NULL;
        return head;
    }
    Node* temp = head;
    while(temp->next->next){
        temp = temp->next;
    }
    Node* deletedNode = temp->next;
    temp->next = NULL;
    free(deletedNode);
    return head;
}

Node* deleteNodeAtPosition(Node* head, int position){
    if(position == 1){
        return deleteNodeAtHead(head);
    }
    Node* temp = head;
    int i = 1; 
    while(i != position - 1){
        temp = temp->next;
        i++;
    }
    Node* deletedNode = temp->next;
    temp->next = temp->next->next;
    free(deletedNode);
    return head;
}

void printList(Node* head){
    while(head){
        printf("%d ", head->data);
        head = head->next;
    }
}

void deletecompleteList(Node* head){
    while(head){
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main(){
    Node* head = NULL;
    head = insertNodeAtTail(head, 59);
    head = insertNodeAtTail(head, 45);
    printList(head);
    head = deleteNodeAtHead(head);

    printf("--- \n");
    printList(head);
    deletecompleteList(head);
    return 0; 
}
