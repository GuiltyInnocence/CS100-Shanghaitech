#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/****************************Struct declarations*************************************/
//It's generally good to put all your structures at the beginning of a single file.

typedef struct node{
    int value;
    struct node* next;
} Node;

typedef struct{
    Node* head;
    Node* tail;
    int size;
} LinkedList;


/*******************************LinkedList & functions******************************/
void list_init(LinkedList* l)
{
    // TODO: initialize the list `l`, set the head and tail to NULL, and size to 0.
    // YOUR CODE HERE
    l->head=NULL;
    l->tail=NULL;
    l->size=0;
}


void list_insert(LinkedList* l, int value)
{
    // TODO: insert a node that contains `value` into the list `l` immediately after 
    //       the last node (which tail points to).
    // YOUR CODE HERE
    Node* nnew=(Node*)malloc(sizeof(Node));
    nnew->next=NULL;
    nnew->value=value;
    if(l->size==0){
        l->head=nnew;
        l->tail=nnew;
    }
    else{
        (l->tail)->next=nnew;
        l->tail=nnew;
    }
    l->size++;
    return;
}

void list_clear(LinkedList* l)
{
    // TODO: Clear the whole list, set head, tail and size to the initial state.
    // YOUR CODE HERE
    for(Node* i=l->head;i!=NULL;){
        Node* tmp=i->next;
        free(i);
        i=tmp;
    }
    l->head=NULL;
    l->tail=NULL;
    l->size=0;
    return;
}

Node* list_remove(LinkedList* l, Node* target)
{
    // TODO: remove the `target` node, and return the node immediately after it.
    // YOUR CODE HERE
    if(target==NULL)return NULL;
    if(target==l->head){
        Node* tmp=l->head->next;
        free(target);
        l->head=tmp;
        if(l->size==1)l->tail=tmp;
        l->size--;
        return l->head;
    }
    for(Node* i=l->head;i->next!=NULL;i=i->next){
        if(i->next==target){
            Node* tmp=i->next->next;
            if(target==l->tail)l->tail=i;
            free(target);
            i->next=tmp;
            l->size--;
            return tmp;
        }
    }
    return NULL;
}


void enumerate(LinkedList* l){
    for(Node* i=l->head;i!=NULL;i=i->next){
        printf("%d ",i->value);
    }
}
Node* getnode(LinkedList* l,int n){
    int cnt=0;
    for(Node* i=l->head;i!=NULL && cnt<n;i=i->next){
        if(++cnt==n)return i;
    }
}
void removen(LinkedList* l,int n){
    list_remove(l,getnode(l,n));
}
/*****************************Your Main Function*************************************/
// DO NOT submit main function to OJ, or compile error may happen!
int main()
{
    // Add your own test cases here, but DONOT submit it to OJ.
    LinkedList l;
    list_init(&l);
    list_insert(&l,233);
    list_insert(&l,2333);
    list_insert(&l,23333);
    list_insert(&l,233333);
    removen(&l,4);
    enumerate(&l);
    puts("");
    list_insert(&l,666);
    list_insert(&l,6666);
    removen(&l,2);
    enumerate(&l);
    puts("");
    removen(&l,4);
    removen(&l,3);
    removen(&l,2);
    removen(&l,1);
    list_insert(&l,233);
    enumerate(&l);
    list_clear(&l);
    return 0;
}
