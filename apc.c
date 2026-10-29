#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "apc.h"
void createList(char* str,Dlist** head, Dlist** tail)
{
    *head = malloc(sizeof(Dlist));
    (*head)->prev = NULL;
    int digit = str[0]-48;
    (*head)->data = digit;
    (*head)->next = NULL;
    *tail = *head;
    for(int i=1;i<strlen(str);i++)
    {
        digit = str[i]-48;
        insertAtend(head,tail,digit);
    }
}
void insertAtend(Dlist**head,Dlist**tail,int data)
{
    Dlist* temp = malloc(sizeof(Dlist));
    temp->prev = NULL;
    temp->data = data;
    temp->next = NULL;
    Dlist* ptr = *head;
    while(ptr->next!=NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = temp;
    temp->prev = ptr;
    *tail = temp;
}
void print_list(Dlist** head)
{
    Dlist* ptr = *head;
    while(ptr!=NULL)
    {
        printf("%d",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}
void addition(Dlist** head1, Dlist** tail1,Dlist** head2, Dlist** tail2)
{
    Dlist* temp1 = *tail1;
    Dlist* temp2 = *tail2;
    Dlist* resH  = NULL;
    Dlist* resT  = NULL;
    Dlist* res   = malloc(sizeof(Dlist));
    int carry=0;
    while(temp1!=NULL||temp2!=NULL)
    {
        if(temp1!=NULL&&temp2!=NULL)
        {
            res->data = temp1->data+temp2->data+carry;
            carry = carry_ret(&(res->data));
            insertAtFirst(&resH,&resT,res->data);
            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }
        if(temp1==NULL&&temp2!=NULL)
        {
            res->data = temp2->data+0+carry;
            carry = carry_ret(&(res->data));
            insertAtFirst(&resH,&resT,res->data);
            temp2 = temp2->prev;
        }
        if(temp2==NULL&&temp1!=NULL)
        {
            res->data = temp1->data+0+carry;
            carry = carry_ret(&(res->data));
            insertAtFirst(&resH,&resT,res->data);
            temp1 = temp1->prev;
        }
    }
    if(carry)
    {
        insertAtFirst(&resH,&resT,carry);
    }
    print_list(&resH);
    free_list(resH);
}
void subtraction(Dlist** head1, Dlist** tail1,Dlist** head2, Dlist** tail2)
{
    Dlist* temp1 = *tail1;
    Dlist* temp2 = *tail2;
    Dlist* resH  = NULL;
    Dlist* resT  = NULL;
    Dlist* res   = malloc(sizeof(Dlist));
    while(temp1!=NULL||temp2!=NULL)
    {
        if(temp1!=NULL&&temp2!=NULL)
            {
                if(temp1->data>temp2->data)
                {
                    res->data = temp1->data-temp2->data;
                    insertAtFirst(&resH,&resT,res->data);
                    temp1 = temp1->prev;
                    temp2 = temp2->prev;
                }
                else if(temp1->data < temp2->data)
                {
                    if(temp1->prev->data != 0)
                    {
                        temp1->data += 10;
                        temp1->prev->data -= 1;
                    }
                    else
                    {
                        Dlist *borrow = temp1->prev;
                        while(borrow->data == 0)
                        {
                            borrow = borrow->prev;
                        }
                        borrow->data -= 1;
                        borrow = borrow->next;
                        while(borrow != temp1)
                        {
                            borrow->data = 9;
                            borrow = borrow->next;
                        }
                        temp1->data += 10;
                    }
                    res->data = temp1->data - temp2->data;
                    insertAtFirst(&resH, &resT, res->data);
                    temp1 = temp1->prev;
                    temp2 = temp2->prev;
                }
                else if((temp1->data==temp2->data))
                {
                    res->data = 0;
                    insertAtFirst(&resH,&resT,res->data);
                    temp1 = temp1->prev;
                    temp2 = temp2->prev;
                }
            }
            if(temp2==NULL&&temp1!=NULL)
            {
                    res->data = temp1->data-0;
                    insertAtFirst(&resH,&resT,res->data);
                    temp1 = temp1->prev;
            }
    }
    print_list(&resH);
    free_list(resH);
}
void free_list(Dlist* head)
{
    Dlist* temp;
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
void add_lists(Dlist* head1, Dlist* tail1,Dlist* head2, Dlist* tail2,Dlist** resH, Dlist** resT)
{
    Dlist* temp1 = tail1;
    Dlist* temp2 = tail2;
    int carry = 0;
    int data;
    while(temp1 != NULL || temp2 != NULL)
    {
        if(temp1 != NULL && temp2 != NULL)
        {
            data = temp1->data + temp2->data + carry;
            carry = carry_ret(&data);
            insertAtFirst(resH, resT, data);
            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }
        else if(temp1 != NULL)
        {
            data = temp1->data + carry;
            carry = carry_ret(&data);
            insertAtFirst(resH, resT, data);
            temp1 = temp1->prev;
        }
        else
        {
            data = temp2->data + carry;
            carry = carry_ret(&data);
            insertAtFirst(resH, resT, data);
            temp2 = temp2->prev;
        }
    }
    if(carry != 0)
    {
        insertAtFirst(resH, resT, carry);
    }
}
void multiplication(Dlist** head1, Dlist** tail1,Dlist** head2, Dlist** tail2)
{
    Dlist* temp2 = *tail2;
    Dlist* resH = NULL;
    Dlist* resT = NULL;
    int zero_count = 0;
    while(temp2 != NULL)
    {
        Dlist* temp1 = *tail1;
        Dlist* res1H = NULL;
        Dlist* res1T = NULL;
        int carry = 0;
        while(temp1 != NULL)
        {
            int data = temp1->data * temp2->data + carry;
            carry = carry_ret(&data);
            insertAtFirst(&res1H, &res1T, data);
            temp1 = temp1->prev;
        }
        if(carry != 0)
        {
            insertAtFirst(&res1H, &res1T, carry);
        }
        for(int i = 0; i < zero_count; i++)
        {
            insertAtend(&res1H, &res1T, 0);
        }
        Dlist* newH = NULL;
        Dlist* newT = NULL;
        add_lists(res1H, res1T,resH,resT,&newH, &newT);
        free_list(res1H);
        free_list(resH);
        resH = newH;
        resT = newT;
        zero_count++;
        temp2 = temp2->prev;
    }
    print_list(&resH);
    free_list(resH);
}
void division(Dlist** head1, Dlist** tail1, Dlist** head2, Dlist** tail2)
{
    int divisor = (*head2)->data;
    Dlist* temp = *head1;
    Dlist* quoH = NULL;
    Dlist* quoT = NULL;
    int rem = 0;
    while(temp != NULL)
    {
        int num = rem * 10 + temp->data;
        int quotient = 0;
        while(num >= divisor)
        {
            num = num - divisor;
            quotient++;
        }
        rem = num;
        if(quoH == NULL)
        {
            insertAtFirst(&quoH, &quoT, quotient);
        }
        else
        {
            insertAtend(&quoH, &quoT, quotient);
        }        temp = temp->next;
    }
    print_list(&quoH);
    free_list(quoH);
}
void insertAtFirst(Dlist** resH, Dlist** resT, int data)
{
    Dlist* temp = malloc(sizeof(Dlist));
    if(*resH == NULL)
    {
        temp->prev = NULL;
        temp->next = NULL;
        temp->data = data;
        *resH  = temp;
        *resT  = temp;
    }
    else
    {   
        temp->next = *resH;
        temp->prev = NULL;
        (*resH)->prev = temp;
        temp->data = data;
        *resH      = temp; 
    }
}
int carry_ret(int* data)
{
    int temp = *data;
    if(temp>9)
    {
        *data = *data%10;
        return (temp-(*data))/10;
    }
    else
    {
        return 0;
    }
}