#include<stdio.h>
#include<stdlib.h>

typedef struct btnode{
    int data;
    struct btnode* left;
    struct btnode* right;
}btnode;


typedef struct node{
    btnode *ptr;
    struct node * next;
}node;

typedef struct bfsqueue{
    node* front;
    node* back;
    int size;
}bfsqueue;

bfsqueue * initQueue(){
    bfsqueue* newqueue =  (bfsqueue*)malloc(sizeof(bfsqueue));
    newqueue->front = NULL;
    newqueue->back =NULL;
    newqueue->size = 0;
    return newqueue;
}


void addInBFSqueue(bfsqueue *q, btnode * root){
    node * newnode = (node*)malloc(sizeof(node));
    newnode->ptr = root;
    newnode->next = NULL;
    if(!q->front){
        q->front= newnode;
        q->back = newnode;
    }else{
    q->back->next = newnode;
    q->back = newnode;
    }
    (q->size)++;
}

node* removeInBFSqueue(bfsqueue *q){
    if(!q || !q->front) return NULL;
    node * temp = NULL;
    if(q->front == q->back){
        temp = q->front;
        q->front=NULL;
        q->back=NULL;
    }else{
    temp = q->front;
    q->front = q->front->next;
    }
    (q->size)--;
    return temp;
}


btnode* insertInBST(btnode* root, int val){
    if(!root){
        btnode* newnode = (btnode*)malloc(sizeof(btnode));
        if(!newnode){
            printf("Memory Allocation failed"); //Error Handling
            return NULL;
        }
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        return newnode;
    }

    if(root->data <= val){
        root->right = insertInBST(root->right,val);
    }else{
        root->left= insertInBST(root->left,val);
    }
    return root;
}


int searchInBST(btnode* root,int val){
    if(!root)return 0;
    if(root->data == val){
        return 1;
    }
    return searchInBST(root->left,val) || searchInBST(root->right,val);
}

int max(int a, int b){
    if (a > b)return a;
    return b;
}
int min(int a, int b){
    if (a > b)return b;
    return a;
}

int heightOfTree(btnode *root){
    if(!root)return 0;
    return max(heightOfTree(root->left),heightOfTree(root->right))+1;
}

void printBST(btnode *root){
    if(!root){
        printf("-1\t ");  // this represent the NULL
        return;
    }
    printf("%d\t ",root->data);
    printBST(root->left);
    printBST(root->right);
}

void printInOrderOfTree(btnode* root){
    if(root){
        printInOrderOfTree(root->left);
        printf("%d\t ",root->data);
        printInOrderOfTree(root->right);
    }
}

void printPreOrderOfTree(btnode* root){
    if(root){
        printf("%d\t ",root->data);
        printPreOrderOfTree(root->left);
        printPreOrderOfTree(root->right);
    }
}

void printPostOrderOfTree(btnode* root){
     if(root){
        printPostOrderOfTree(root->left);
        printPostOrderOfTree(root->right);
        printf("%d\t ",root->data);
    }
}


void printLevelOrderOfTree(btnode*root){
    bfsqueue* q = (bfsqueue*)malloc(sizeof(bfsqueue));
    addInBFSqueue(q,root);
    while(q->size){
        int size = q->size;
        while(size--){
            node * f = removeInBFSqueue(q);
            btnode *fr = f->ptr;
            printf("%d\t",fr->data);
            if(fr->left){
                addInBFSqueue(q,fr->left);
            }
            if(fr->right){
                addInBFSqueue(q,fr->right);
            }
        }
        printf("\n");
    }
}

int rootToNodePath(btnode* root, int *arr, int *ind,int val){
    if(!root)return 0;
    if(root->data== val){
        *(arr+(*ind))=val;
        (*ind)++;
        return 1;
    }
    int l = rootToNodePath(root->left,arr,ind,val);
    int r = rootToNodePath(root->right,arr,ind,val);
    if(l||r){
        *(arr+(*ind))=root->data;
        (*ind)++;
        return 1;
    }
    return 0;
}


void printArray(int *arr,int len){
  for(int i = 0;i < len;i++){
    printf("%d  ",*(arr+i));
  }    
  printf("\n");
}

void printLCA(btnode *root, int v1, int v2){
    int he = heightOfTree(root);
    int *arr = (int*)calloc(sizeof(int),he+1);
    int *ind = (int *)malloc(sizeof(int));
    int r1 = rootToNodePath(root,arr,ind,v1);
    if(!r1){
        printf("%d Does Not Exist in Tree",v1);
        return;
    }
    int *arr2 = (int*)calloc(sizeof(int),he+1);
    int *ind2 = (int *)malloc(sizeof(int));
    int r2 = rootToNodePath(root,arr2,ind2,v2);
    if(!r2){
        printf("%d Does Not Exist in Tree",v2);
        return;
    }
    int *p1 = arr+(*ind-1);
    int *p2 = arr2+(*ind2-1);
    int ans = *p1;
    while(*p1==*p2){
        p1--;
        p2--;
        if(*p1==*p2){
            ans = *p1;
        }
    }

    printf("LCA is : %d\n",ans);

    
}


int helperCheckIfBST(btnode* root, int lrange,int rrange){
    if(!root){
        return 1;
    }
    if(!(lrange < root->data && root->data <= rrange)){
        return 0;
    }
    int l = helperCheckIfBST(root->left,lrange,root->data);
    int r = helperCheckIfBST(root->right,root->data,rrange);
    return l&&r;
}

void  checkIfBST(btnode *root){
     int a  = helperCheckIfBST(root,-1e9,1e9);
     if(!a){
        printf("Not A BST\n");
     }else{
        printf("Is A BST\n");
     }

}

typedef struct pair{
       btnode* p;
       btnode* q;
}pair;

pair * convertToDoubleLL(btnode *root){
    pair *g = (pair*)malloc(sizeof(pair));
    if(!root->left && !root->right){
        g->p=root;
        g->q=root;
        return g;
    }

    if(!root->left && root->right){
        g->p=root;
        pair *rg =convertToDoubleLL(root->right);
        root->right = rg->p;
        rg->p->left = root;
        g->q = rg->q;
        return g;
    }

    if(root->left && !root->right){
        pair*lg = convertToDoubleLL(root->left);
        g->p = lg->p;
        lg->q->right = root;
        root->left = lg->q;
        g->q=root;
        return g;
    }


    pair *lg = convertToDoubleLL(root->left);
    pair *rg = convertToDoubleLL(root->right);

    lg->q->right = root;
    // rg->q->right = root;
    root->right = rg->p;
    rg->p->left = root;
    g->p = lg->p;
    g->q = rg->q;
    return g;

}

btnode* convertToCircularLL(btnode *root){
    pair* g = convertToDoubleLL(root);
    btnode *temp = g->p;
    g->p->left = g->q;
    g->q->right = temp;

    return temp;  
}

void printCircularLL(btnode* pt){
    btnode *temp = pt;
    do{
        printf("%d ",temp->data);
        temp = temp->right;
    }while(temp!=pt);

    printf("\n");
}

void printDoubleLL(pair *pt){
    btnode *temp = pt->p;
    while(temp ){
        printf("%d ",temp->data);
        temp = temp->right;
    }
    printf("\n----------\n");
    temp = pt->q;
    while(temp){
        printf("%d ",temp->data);
        temp = temp->left;
    }
    printf("\n");
}

void printAtLevelK(btnode* root, int k){
    if(!root)return;
    if(k==0){
        printf("%d ",root->data);
        return;
    }
    printAtLevelK(root->left,k-1);
    printAtLevelK(root->right,k-1);
}

int printAtDistanceK(btnode*root,int val,int k){
    if(!root)return -1;
    if(root->data == val){
        printAtLevelK(root,k);
        return k-1;
    }
    int lk = printAtDistanceK(root->left,val,k);
    if(lk != -1){
        if(lk==0){
            printf("%d ",root->data);
        return -1;
        }
        printAtLevelK(root->right,lk);
        return lk-1;
    }
    int rk = printAtDistanceK(root->right,val,k);
    if(rk != -1){
        if(rk==0){
            printf("%d ",root->data);
        return -1;
        }
        printAtLevelK(root->left,rk);
        return rk-1;
    }
}

typedef struct pairint{
    int f;
    int s;
}pairint;

void helpwidthOfTree(btnode* root,int *mi ,int *mx, int p){
    if(!root)return;
    if(p < *mi){
        *mi=p;
    }
    if(p > *mx){
        *mx=p;
    }
    helpwidthOfTree(root->left,mi,mx,p-1);
    helpwidthOfTree(root->right,mi,mx,p+1);
}

pairint* widthOfTree(btnode*root){
    int mia=0,mxa=0;
    int *mi = &mia;
    int *mx = &mxa;

    helpwidthOfTree(root,mi,mx,0);
    pairint* pi = (pairint*)malloc(sizeof(pairint));
    pi->f = mia;
    pi->s = mxa;
    return pi;
}

typedef struct nodeint{
    int data;
    int ex;
    struct nodeint *next;
}nodeint;

typedef struct linkedlistint{
    int data;
    nodeint *head;
    nodeint *tail;
}linkedlistint;

typedef struct nodeL{
    btnode *ptr;
    struct nodeL * next;
    int ex;
}nodeL;

typedef struct bfsqueueL{
    nodeL* front;
    nodeL* back;
    int size;
}bfsqueueL;


void addInBFSqueueL(bfsqueueL *q, btnode * root,int ex){
    nodeL * newnode = (nodeL*)malloc(sizeof(nodeL));
    newnode->ptr = root;
    newnode->next = NULL;
    newnode->ex = ex;
    if(!q->front){
        q->front= newnode;
        q->back = newnode;
    }else{
    q->back->next = newnode;
    q->back = newnode;
    }
    (q->size)++;
}

nodeL* removeInBFSqueueL(bfsqueueL *q){
    if(!q || !q->front) return NULL;
    nodeL * temp = NULL;
    if(q->front == q->back){
        temp = q->front;
        q->front=NULL;
        q->back=NULL;
    }else{
    temp = q->front;
    q->front = q->front->next;
    }
    (q->size)--;
    return temp;
}

void insertInLLextra(linkedlistint *ll, int data,int ex){
    nodeint* temp = (nodeint *)malloc(sizeof(nodeint));
    temp->data = data;
    temp->next = NULL;
    temp->ex = ex;
    if(!ll->head){
        ll->head = ll->tail = temp;
        return;
    }
    ll->tail->next = temp;
    ll->tail = temp;
}

void printlinkedlistLL(btnode * root,linkedlistint **arr,int he){
    pairint* al = widthOfTree(root); 
    int exh = -1*(al->f);
    int he2 = exh+al->s+2;
   
   linkedlistint **brr =  (linkedlistint ** )calloc(sizeof(linkedlistint*),he2);
   for(int i = 0;i < he2;i++){
        *(brr+i) = (linkedlistint *)malloc(sizeof(linkedlistint));
        (*(brr+i))->head = NULL;
        (*(brr+i))->tail = NULL;
    }


    for(int i = 0;i < he;i++){
        nodeint *temp = (*(arr+i))->head;
        while(temp){
            linkedlistint *row = *(brr+(temp->ex+exh));
            insertInLLextra(row,temp->data,temp->ex+exh);
            temp = temp->next;
        }
        
    }
    
    
     for(int i = 0;i < he2-1;i++){
        nodeint *temp = (*(brr+i))->head;
        printf("%d :-> ",i-exh);
        while(temp){
            printf("%d ",temp->data,temp->ex+exh);
            temp = temp->next;
        }
        printf("\n");
        
    }

    printf("\n");

}

void printVerticalOrderTraversal(btnode*root){
    int he = heightOfTree(root);
    linkedlistint **arr = (linkedlistint ** )calloc(sizeof(linkedlistint*),he);
    for(int i = 0;i < he;i++){
        *(arr+i) = (linkedlistint *)malloc(sizeof(linkedlistint));
        (*(arr+i))->head = NULL;
        (*(arr+i))->tail = NULL;
    }

    bfsqueueL* q = (bfsqueueL*)malloc(sizeof(bfsqueueL));
    addInBFSqueueL(q,root,0);
    int level = 0;
    while(q->size){
        int size = q->size;
        while(size--){
            nodeL * f = removeInBFSqueueL(q);
            btnode *fr = f->ptr;
            int ex = f->ex;
            // printf("%d\t",fr->data);
            linkedlistint *row = *(arr+level);
            insertInLLextra(row,fr->data,ex);         
            if(fr->left){
                addInBFSqueueL(q,fr->left,ex-1);
            }
            if(fr->right){
                addInBFSqueueL(q,fr->right,ex+1);
            }
        }
        level++;
    }
    
    printlinkedlistLL(root,arr,he);

}

btnode* initTree(){
    int data;
    scanf("%d",&data);
    if(data == -1){
        return NULL;
    }
    btnode * root = (btnode* )malloc(sizeof(btnode));
    root->data = data;
    root->left = initTree();
    root->right =initTree();
    return root;
}

pairint * helpdiameterOfTree(btnode*root){
    pairint* p = (pairint*)malloc(sizeof(pairint));
    if(!root){
        p->f = 0;
        p->s = 0;
        return p;
    }
    pairint *lp = helpdiameterOfTree(root->left);
    pairint *rp = helpdiameterOfTree(root->right);
    p->f = max(lp->f,rp->f)+1;
    p->s = max(max(lp->s,rp->s),lp->f+rp->f+1);
    return p;
}

int diameterOfTree(btnode* root){
    pairint* p = helpdiameterOfTree(root);
    return p->s;
}

typedef struct quard{
    int a,b,c,d;
}quard;

quard* helptiltOfTree(btnode* root){
    // printf("s\n");
    quard* p = (quard* )malloc(sizeof(quard));
    if(!root){
        p->a = 0;
        p->c = -1e9;
        p->b = 1e9;
        p->d = 1;
        return p;
    }
    quard *lq = (quard* )malloc(sizeof(quard));;
    lq = helptiltOfTree(root->left);
    quard *rq = (quard* )malloc(sizeof(quard));;
    rq = helptiltOfTree(root->right);

    

    if(!(lq->d && rq->d) || !(root->data >lq->c && root->data <= rq->b )){
        p->a = max(lq->a,rq->a);
        p->b = 0;
        p->c = 0;
        p->d = 0;
        return p;
    }
    p->d = 1;
    p->b = min(lq->b,root->data);
    p->c = max(rq->c,root->data);
    p->a = lq->a+rq->a+1;
    return p;
}

int  tiltOfTree(btnode * root){
    
    quard* q = (quard* )malloc(sizeof(quard)); 
    q = helptiltOfTree(root);
    return q->a;
}

int findIndexInInorder(int val, int *inorder,int n){
    for(int i = 0;i < n;i++){
        if(*(inorder+i) == val){
            return i;
        }
    }
    return n;
}

btnode* helpIn_PreToTree(int *p, int sr, int er, int *inorder, int *preorder, int n) {
    if (sr > er) return NULL;

    int val = *(preorder + *p);
    int inx = findIndexInInorder(val,inorder,n);
    printf("%d %d %d %d \n",inx,val,sr,er);
    (*p)++;
    
    btnode* root = (btnode*)malloc(sizeof(btnode));
    root->data = val;

    root->left = helpIn_PreToTree(p,sr,inx-1,inorder,preorder,n);
    root->right = helpIn_PreToTree(p,inx+1,er,inorder,preorder,n);

    
    return root;
}

btnode* In_PreToTree(){
    int n;
    printf("Enter Number of Nodes: ");
    scanf("%d",&n);
    int *inorder = (int *)calloc(sizeof(int),n);
    int *preorder = (int *)calloc(sizeof(int),n);
    printf("Enter Inorder : ");
    for(int i = 0;i < n;i++){
        scanf("%d",inorder+i);
    }
    printf("Enter Preorder : ");
    for(int i = 0;i < n;i++){
        scanf("%d",preorder+i);
    }
    
    int prinx = 0;
    int *ptrpr = &prinx;
    return helpIn_PreToTree(ptrpr,0,n-1,inorder,preorder,n);
}

btnode * helpIn_PostToTree(int *p,int sr,int er,int *inorder, int *postorder,int n){
     if(sr > er)return NULL;
     int val = *(postorder + *p);
    int inx = findIndexInInorder(val,inorder,n);
    printf("%d %d %d %d \n",inx,val,sr,er);
    (*p)--;
    
    btnode* root = (btnode*)malloc(sizeof(btnode));
    root->data = val;
    
    root->right = helpIn_PostToTree(p,inx+1,er,inorder,postorder,n);
    root->left = helpIn_PostToTree(p,sr,inx-1,inorder,postorder,n);
    
    return root;
}

btnode* In_PostToTree(){
    int n;
    printf("Enter Number of Nodes: ");
    scanf("%d",&n);
    int *inorder = (int *)calloc(sizeof(int),n);
    int *postorder = (int *)calloc(sizeof(int),n);
    printf("Enter Inorder : ");
    for(int i = 0;i < n;i++){
        scanf("%d",inorder+i);
    }
    printf("Enter Postorder : ");
    for(int i = 0;i < n;i++){
        scanf("%d",postorder+i);
    }
    
    int prinx = n-1;
    int *ptrpr = &prinx;
    return helpIn_PostToTree(ptrpr,0,n-1,inorder,postorder,n);
}


void helptopViewOfTree(btnode*root,int *arr,int exh){
    bfsqueueL* q = (bfsqueueL*)malloc(sizeof(bfsqueueL));
    addInBFSqueueL(q,root,0);
    int level = 0;
    while(q->size){
        int size = q->size;
        while(size--){
            nodeL * f = removeInBFSqueueL(q);
            btnode *fr = f->ptr;
            int ex = f->ex;
            // printf("%d %d\n",fr->data,ex+exh);
            if(*(arr+ex+exh)== 1e9){
                *(arr+ex+exh) = fr->data;
            }      
            if(fr->left){
                addInBFSqueueL(q,fr->left,ex-1);
            }
            if(fr->right){
                addInBFSqueueL(q,fr->right,ex+1);
            }
        }
        level++;
    }

}


int* topViewOfTree(btnode* root){
    pairint* p = widthOfTree(root);
    int si = (p->f*(-1))+p->s+1;
    int *arr = (int *)calloc(sizeof(int),si);
    for(int i = 0;i < si;i++){
        *(arr+i) = 1e9;
    }
    
    helptopViewOfTree(root,arr,p->f*(-1));


    // for(int i = 0;i < si;i++){
    //     printf("%d ",*(arr+i));
    // }
    return arr;
}

void helpprintLeftSide(btnode* root){
    btnode* temp = root;
    while(1){
        if(!temp->left && !temp->right)return;
        printf("%d ",temp->data);
        if(temp->left){
            temp = temp->left;
        }else{
            temp = temp->right;
        }
    }
}


void helpprintRightSide(btnode* root){
    int he = heightOfTree(root->right);
    int *arr = (int *)calloc(sizeof(int),he);
    int k = 0;
    btnode* temp = root->right;
    while(1){
        if(!temp->left && !temp->right)break;
        // printf("%d \n",temp->data);
        *(arr+k)=temp->data;
        k++;
        if(temp->right){
            temp = temp->right;
        }else{
            temp = temp->left;
        }
    }
    // printf("\n %d\n",k);
    for(int i = k-1;i >= 0;i--){
        printf("%d ",*(arr+i));
    }
}



void printLeafNode(btnode* root){
    if(!root)return;
    if(!root->left && !root->right){
        printf("%d ",root->data);
        return;
    }
    printLeafNode(root->left);
    printLeafNode(root->right);
}

void printLeftSide(btnode *root){
    
    if(root->left && root->right){

        // printf("\n%dll \n",root->data);
        helpprintLeftSide(root);
        printLeafNode(root);
        helpprintRightSide(root);
        printf("%d ",root->data);
        return;
    }
    printf("%d ",root->data);
    printLeftSide(root->left);
    printf("%d ",root->data);
}


void printRightSide(btnode *root){
    if(!root)return;
    if(root->left && root->right){
        helpprintLeftSide(root);
        printLeafNode(root);
        helpprintRightSide(root);
        printf("%d ",root->data);
        return;
    } 
    printf("%d ",root->data);
    printRightSide(root->right);
    printf("%d ",root->data);
}

void boundaryTraversalInTree(btnode* root){
    if(!root);
    if(!root->left){
        printRightSide(root);
        printf("\n");
        return;
    }
    printLeftSide(root);
    printf("\n");

}


void leftViewOfTree(btnode*root){
    bfsqueue* q = (bfsqueue*)malloc(sizeof(bfsqueue));
    addInBFSqueue(q,root);
    while(q->size){
        int size = q->size;
        int flag = 0;
        while(size--){
            node * f = removeInBFSqueue(q);
            btnode *fr = f->ptr;
            if(!flag){
                printf("%d\t",fr->data);
                flag=1;
            }
            if(fr->left){
                addInBFSqueue(q,fr->left);
            }
            if(fr->right){
                addInBFSqueue(q,fr->right);
            }
        }
        printf("\n");
    }
}

void rightViewOfTree(btnode*root){
    int he = heightOfTree(root);
    int *arr = (int *)calloc(sizeof(int),he);
    bfsqueue* q = (bfsqueue*)malloc(sizeof(bfsqueue));
    addInBFSqueue(q,root);
    int level = 0;
    while(q->size){
        int size = q->size;
        while(size--){
            node * f = removeInBFSqueue(q);
            btnode *fr = f->ptr;
            *(arr+level) = fr->data;
            if(fr->left){
                addInBFSqueue(q,fr->left);
            }
            if(fr->right){
                addInBFSqueue(q,fr->right);
            }
        }
        // printf("\n");
        level++;
    }

    for(int i = 0;i < he;i++){
        printf("%d \n",*(arr+i));
    }
}


int leftViewOfTreeboundary(btnode*root){
    bfsqueue* q = (bfsqueue*)malloc(sizeof(bfsqueue));
    addInBFSqueue(q,root);
    int lastlef = 0;
    while(q->size){
        int size = q->size;
        int flag = 0;
        while(size--){
            node * f = removeInBFSqueue(q);
            btnode *fr = f->ptr;
            if(!flag){
                lastlef = fr->data;
                if(!fr->left && !fr->right){
                    return lastlef;
                }
                printf("%d\t",fr->data);
                flag=1;
            }
            if(fr->left){
                addInBFSqueue(q,fr->left);
            }
            if(fr->right){
                addInBFSqueue(q,fr->right);
            }
        }
        printf("\n");
    }
    return lastlef;
}


int rightViewOfTreeboundary(btnode*root,int *arr,int he){
    bfsqueue* q = (bfsqueue*)malloc(sizeof(bfsqueue));
    addInBFSqueue(q,root);
    int level = 0;
    while(q->size){
        int size = q->size;
        while(size--){
            node * f = removeInBFSqueue(q);
            btnode *fr = f->ptr;
            *(arr+level) = fr->data;
            if(fr->left){
                addInBFSqueue(q,fr->left);
            }
            if(fr->right){
                addInBFSqueue(q,fr->right);
            }
        }
        // printf("\n");
        level++;
    }

    return *(arr+(he-1));
}

void printleafinrange(btnode *root, int *f,int a,int b){
    if(!root)return;
     if(b == root->data){
        *f = 0;
    }

    if(*f && (!root->left && !root->right)){

        printf("%d ",root->data);
    }
    if(a == root->data){
        *f = 1;
    }
    printleafinrange(root->left,f,a,b);
    printleafinrange(root->right,f,a,b);


}

void boundary(btnode* root){
    int datal = leftViewOfTreeboundary(root);
    printf("%d \n",datal);
    int he = heightOfTree(root);
    int *arr = (int *)calloc(sizeof(int),he);

    int datar = rightViewOfTreeboundary(root,arr,he);
    int flag = 0;
    int *pt = &flag;
    // printf("---\n");
    printleafinrange(root,pt,datal,datar);

     for(int i = he-1;i >= 0;i--){
        printf("%d \n",*(arr+i));
    }
     
}

void printToRight(btnode *root,bfsqueue *q){
    if(!root)return;
    printf("%d ",root->data);
    if(root->left){
        addInBFSqueue(q,root->left);
    }
    printToRight(root->right,q);

}

void printDiagonalOfTree(btnode* root){
    bfsqueue* q = (bfsqueue *)malloc(sizeof(bfsqueue));
    addInBFSqueue(q,root);
    while(q->size){
        int size = q->size;
        while(size--){
             node*f = removeInBFSqueue(q);
             btnode* fr = f->ptr;
             printToRight(fr,q);
        }
        printf("\n");
    }
}

btnode* insertToLl(btnode* root,btnode *rp){
    if(!rp)return root;
    if(!root)return rp;
    root->left = insertToLl(root->left,rp);
    return root;
}

btnode* removeInBST(btnode *root, int data){
    if(!root)return NULL ;
     if(root->data == data){
          if(root->right)
          return insertToLl(root->right,root->left);
          else
          return root->left;
     }
     if(root->data > data){
        root->left = removeInBST(root->left,data);
     }else{
        root->right = removeInBST(root->right,data);
     }
     return root;
}

void helpnewConvertToDoubleLL(btnode* root, pair* p){
    if(!root)return;
    helpnewConvertToDoubleLL(root->left,p);
    if(!p->p){
        p->p = p->q = root;
        return;
    }
    printf("%d\n",root->data);
    p->q->right = root;
    root->left = p->q;
    p->q = root;
    btnode* ls = root->right;

    helpnewConvertToDoubleLL(ls,p);

}


pair* newConvertToDoubleLL(btnode *root){
    pair *p = (pair *)malloc(sizeof(pair));
    helpnewConvertToDoubleLL(root,p);
    return p;
}

int ceilOfBST(btnode *root,int val){
    btnode* temp = root;
     int pv = -1e9;
    while(temp){
        if(temp->data == val)return val;
        if(temp->data > val){
             temp = temp->left;
        }else{
             pv = temp->data;
            temp = temp->right;
        }
    }
    return pv;
    
}

int floorOfBST(btnode * root,int val){
    btnode* temp = root;
    int ng = -1e9;
    while(temp){
        if(temp->data == val)return val;
        if(temp->data > val){
             temp = temp->left;
        }else{
             ng = temp->data;
            temp = temp->right;
        }
    }
    return ng;
}

void ceilAndFloorOfBST(btnode *root,int val){
    if(!root)return;
    // int ceil = ceilOfBST(root,val);
    printf("+++++++++\n");
    int floor = floorOfBST(root,val);
    printf("%dl\n",floor);
}

int main(){
    btnode* root=NULL;
    root = insertInBST(root,5);
    // root =insertInBST(root,4);
    // root =insertInBST(root,7);
    // root =insertInBST(root,8);
    // root =insertInBST(root,2);
    // root =insertInBST(root,6);

    // printf("%p\n",root);
    int search_value = 8;
    int flag = searchInBST(root,search_value);
    if(flag){
        printf("%d Exist In BST\n",search_value);
    }else{
        printf("%d Does Not Exist In BST\n",search_value);
    }

    int he = heightOfTree(root);
    printf("%d is Height of BST\n",he);
    printf("BST\n");
    printBST(root);
    printf("\n");
    printf("PreOrder Of BST\n");
    printPreOrderOfTree(root);
    printf("\n");
    printf("InOrder of BST\n");
    printInOrderOfTree(root);
    printf("\n");
    printf("PostOrder of BST\n");
    printPostOrderOfTree(root);
    printf("\n");
    printf("LevelOrder Of BST\n");
    printLevelOrderOfTree(root);
    printf("\n");

    int *arr = (int*)calloc(sizeof(int),he+1);
    int *ind = (int *)malloc(sizeof(int));
    rootToNodePath(root,arr,ind,6);
    printArray(arr,he);
    printLCA(root,2,4);
    checkIfBST(root);

    // btnode* rt = (btnode*)malloc(sizeof(btnode));
    // rt->data = 2;
    // btnode* rl = (btnode*)malloc(sizeof(btnode));
    //  rl->data = 1;
    // rl->left = NULL;
    // rl->right = NULL;
    // btnode* rr = (btnode*)malloc(sizeof(btnode));
    //  rr->data = 3;
    // rr->left = NULL;
    // rr->right = NULL;
    // rt->left = rl;
    // rt->right = rr;
    // pair * xd = convertToDoubleLL(rt);
    // printDoubleLL(xd);
    // btnode * ls = convertToCircularLL(root);
    // printCircularLL(ls);
    // printAtLevelK(root,2);
    printf("==========\n");
    // printAtDistanceK(root,2,3);
    // printf("\n");
    // pairint* lls = widthOfTree(root);
    // printf("%d  %d\n",lls->f,lls->s);
    // btnode * nrt = initTree();
    // printVerticalOrderTraversal(nrt);
    // printf("dia:  %d\n",diameterOfTree(root));
    // printf("%d\n",tiltOfTree(nrt));
    // btnode* gt = In_PostToTree();
    // printf("\n++++++++++\n");
    // printLevelOrderOfTree(gt);
    // printf("\n");

    // topViewOfTree(nrt);
    // boundaryTraversalInTree(nrt);
    // leftViewOfTree(nrt);
    // rightViewOfTree(nrt);
    // leftViewOfTreeboundary(nrt);
    // boundary(nrt);
    // printDiagonalOfTree(nrt);
    // root = removeInBST(root,5);
    // printf("LevelOrder Of BST\n");
    // printLevelOrderOfTree(root);
    // printf("\n");
    //    pair* p = newConvertToDoubleLL(root);
    //    printf("--------------\n");
    //    printDoubleLL(p);

    // ceilAndFloorOfBST(nrt,31);
    printf("%d\n",diameterOfTree(root));

}


// 15 10 8 6 -1 -1 9 -1 -1 2 -1 14 13 -1 -1 18 -1 -1 20 16 -1 -1 25 22 -1 -1 30 28 -1 -1 -1

//9 4 2 1 5 7 3 8 6 9 1 2 4 3 5 7 6 8 9
//9 4 2 1 5 7 3 8 6 9 4 2 7 5 8 9 6 3 1
//1 2 -1 4 8 -1 -1 -1 6 7 9 -1 -1 -1 -1
//0 1 2 4 -1 8 -1 -1 5 -1 9 -1 -1 -1 -1
//0 -1 1 -1 2 4 -1 8 -1 -1 5 -1 9 -1 -1
//1 2 4 -1 -1 5 8 10 -1 -1 -1 9 -1 -1 -1

//1 4 8 -1 -1 5 9 -1 -1 7 -1 -1 2 -1 3 6 -1 -1 -1
//11 20 1 -1 -1 15 2 -1 22 -1 -1 17 34 -1 -1 -1 12 -1 13 16 -1 -1 -1
//50 30 23 4 -1 -1 25 -1 -1 35 31 -1 -1 42 -1 -1 70 -1 80  73 -1 -1 85 -1 -1