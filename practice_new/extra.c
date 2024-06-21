#include<stdio.h>
#include<stdlib.h>


typedef struct node{
    int data;
    struct node* next;
}node;

typedef struct linkedlist{
    node* head;
    node* tail;

}linkedlist;

void addInlinkedlist(linkedlist *ll, int data){
    node* n = (node *)malloc(sizeof(node));
    n->data = data;
    if(!ll->head){
        ll->head=ll->tail = n;
        return;
    }
    ll->tail->next = n;
    ll->tail = n;
}

void printlinkedlist(linkedlist * ll){
    node *temp = ll->head;
    while(temp){
        printf("%d -> ",temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

linkedlist* reverseLL(node* head){
    linkedlist* nll = (linkedlist *)malloc(sizeof(linkedlist));
    node* pre = NULL;
    node *p = head;
    nll->tail = p;
    while(p){
        node *temp = p->next;
        p->next = pre;
        pre = p;
        p = temp;
    }
    nll->head = pre;
    return nll;

}


void reverseKInLinkedlist(linkedlist* ll, int K) {
    if (!ll || K <= 1) return;

    node* temp = ll->head;
    node* rhead = NULL;
    node* rtail = NULL;
    node* ptail = NULL;

    while (temp) {
        node* sh = temp;
        node* st = temp;
        int k = K;
        while (temp->next && k--) {
            temp = temp->next;
        }        
        node* ns = temp->next;
        temp->next = NULL;
        linkedlist* rs = reverseLL(sh);
        if (!rhead) {
            rhead = rs->head;
        }
        if (rtail) {
            rtail->next = rs->head;
        }
        rtail = rs->tail;
        temp = ns;
    }

    ll->head = rhead;
    ll->tail = rtail;
}



int main(){
    linkedlist *ll = (linkedlist *)malloc(sizeof(linkedlist));
    addInlinkedlist(ll,1);
    addInlinkedlist(ll,2);
    addInlinkedlist(ll,3);
    addInlinkedlist(ll,4);
    printlinkedlist(ll);
    // ll = reverseLL(ll->head);
    printlinkedlist(ll);
    reverseKInLinkedlist(ll,2);
   printlinkedlist(ll);
}