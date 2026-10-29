#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "apc.h"
int main(int argc, char* argv[])
{
    if(argc==4)
    {
        if(argv[2][0]=='+'||argv[2][0]=='-'||argv[2][0]=='x'||argv[2][0]=='X'||argv[2][0]=='/')
        {
            Dlist* head1=NULL, *head2=NULL, *tail1=NULL, *tail2=NULL; 
            Dlist* reshead = NULL, *restail=NULL;
            createList(argv[1],&head1,&tail1);
            print_list(&head1);
            createList(argv[3],&head2,&tail2);
            print_list(&head2);
            if(argv[2][0]=='+')
            {
                addition(&head1,&tail1,&head2,&tail2);
            }
            else if(argv[2][0]=='-')
            {
                if(strlen(argv[1])>strlen(argv[3]))
                    subtraction(&head1,&tail1,&head2,&tail2);
                else if(strlen(argv[1])<strlen(argv[3]))
                {
                    printf("-");
                    subtraction(&head2,&tail2,&head1,&tail1);
                }
                else if(strlen(argv[1]) == strlen(argv[3]))
                {
                    Dlist *ptr1 = head1;
                    Dlist *ptr2 = head2;
                    while(ptr1 != NULL)
                    {
                        if(ptr1->data > ptr2->data)
                        {
                            subtraction(&head1, &tail1, &head2, &tail2);
                            break;
                        }
                        else if(ptr1->data < ptr2->data)
                        {
                            printf("-");
                            subtraction(&head2, &tail2, &head1, &tail1);
                            break;
                        }
                        else
                        {
                            ptr1 = ptr1->next;
                            ptr2 = ptr2->next;
                        }
                    }
                    if(ptr1==NULL)
                    {
                        printf("0\n");
                    }
                }
            }
            else if(argv[2][0]=='x'||argv[2][0]=='X')
            {
                if(strcmp(argv[1],"0")==0 || strcmp(argv[3],"0")==0)
                {
                    printf("0\n");
                }
                else if(strlen(argv[1]) < strlen(argv[3]))
                {
                    multiplication(&head2,&tail2,&head1,&tail1);
                }
                else
                {
                    multiplication(&head1,&tail1,&head2,&tail2);
                }
            }
            else if(argv[2][0]=='/')
            {
                if(strcmp(argv[3],"0")!=0)
                    division(&head1,&tail1,&head2,&tail2);
                else
                {
                    printf("Invalid\n");
                    return 0;
                }
            }
        }
        else{
            printf("Please enter  valid arguments\n");
            return -1;
        }
    }
    else
    {
        printf("Enter valid number of arguments\n");
        return -1;
    }
}

