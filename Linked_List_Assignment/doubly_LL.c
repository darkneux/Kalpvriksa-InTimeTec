#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;
struct Node{
    int data;
    Node* next;
    Node* prev;
};

Node* createNode(int val){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->prev = NULL;
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
    head->prev = newNode;
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
    newNode->prev = temp;
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
    temp->next->prev = newNode;
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

Node* deleteNodeAtHead(Node* head){
    if(head == NULL){
        return NULL;
    }
    Node* deletedNode = head;
    head = head->next;
    if(head){
        head->prev = NULL;
    }
    free(deletedNode);
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
    if(temp->next){
        temp->next->prev = temp;
    }
    free(deletedNode);
    return head;
}

void printList(Node* head){
    while(head){
        printf("%d ", head->data);
        head = head->next;
    }
}

void printReverseList(Node* head){
    if(!head){
        return;
    }
    while(head->next){
        head = head->next;
    }
    while(head){
        printf("%d ", head->data);
        head = head->prev;
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
    head = insertNodeAtTail(head, 124);
    head = insertNodeAtHead(head, 38);
    head = insertNodeAtPosition(head, 2, 1);
    head = insertNodeAtHead(head,53);
    printList(head);

    printf("--- \n");
    printReverseList(head);
    head = deleteNodeAtPosition(head, 3);
    printf("--- \n");
    printList(head);
    deletecompleteList(head);
    return 0; 
}
