#include<stdio.h>
typedef struct node{
    struct node* prev;
    int data;
    struct node* next;
}Dlist;

void createList(char* input,Dlist** head, Dlist** tail);
void insertAtend(Dlist**head,Dlist**tail,int data);
void print_list(Dlist** head);
void addition(Dlist** head1, Dlist** tail1,Dlist** head2, Dlist** tail2);
void insertAtFirst(Dlist** resH,Dlist** resT,int data);
int carry_ret(int* data);
void subtraction(Dlist** head1, Dlist** tail1,Dlist** head2, Dlist** tail2);
void multiplication(Dlist** head1, Dlist** tail1,Dlist** head2, Dlist** tail2);
void division(Dlist** head1, Dlist** tail1, Dlist** head2, Dlist** tail2);
void free_list(Dlist* head);
void add_lists(Dlist* head1, Dlist* tail1,Dlist* head2, Dlist* tail2,Dlist** resH, Dlist** resT);