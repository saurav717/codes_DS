#include<stdio.h>
#include<stdlib.h>


struct node
{
  int val;
  struct node *next;
  struct node *prev;
};

struct node *HEAD = NULL, *TAIL = NULL;

void insert(int num)
{
  struct node *p, *q;
  p = (struct node*)malloc(sizeof(struct node));
  p->val = num;
  p->next = NULL;
  p->prev = NULL;
  TAIL = p;

  if(HEAD == NULL)
  {
    HEAD = p;
  }

  else
  {
    for(q = HEAD; q->next !=NULL; q=q->next)
    {
    }
    q->next = p;
    p->prev = q;
  }
}

void delete(int num)
{
  struct node *q, *l, *m;

  for(q = HEAD; q!=NULL; q=q->next)
  {
    if(q->val == num)
    {
      if(q==HEAD && q==TAIL)
      {
        HEAD=NULL;
        TAIL=NULL;
        free(q);
        break;
      }
      if(q==TAIL)
      {
        l = q->prev;
        l->next = NULL;
        TAIL = l;
        free(q);
        break;
      }

      else if(q==HEAD)
      {
        HEAD = q->next;
        HEAD->prev = NULL;
        free(q);
        break;
      }

      else
      {
        l->next = q->next;
        m = q->next;
        m->prev = l;
        free(q);
        break;
      }

    }
    l=q;
  }
}

void find(int num)
{
  struct node *q;
  printf("the value is in \n");
  int count = 0;
  for(q = HEAD; q!=NULL; q=q->next)
  {
    count++;
    if(q->val==num)
    {
      printf("%d ", count);
    }
  }
  printf("nodes\n");
}

void delete_list()
{
  struct node *q, *l;

    while(HEAD!=NULL)
    {
      q = HEAD->next;
      free(HEAD);
      HEAD = q;
    }
    printf("this is executed\n");
    HEAD = NULL;
    TAIL = NULL;
}


void print_list()
{
  struct node *q;

  for( q=TAIL; q!=NULL; q=q->prev )
  {
    printf("%d ", q->val );
  }
}



int main()
{
  int num;

  while(1)
  {
    printf("\n\n");
    printf("1 - enter value\n");
    printf("2 - delete value\n");
    printf("3 - find value\n");
    printf("4 - delete list\n");
    printf("5 - print list\n");
    printf("6 - print HEAD\n");
    printf("7 - printf TAIL\n");
    printf("0 - exit\n");

    int choice;
    printf("enter your choice\n");
    scanf("%d", &choice);

    switch(choice)
    {
      case 1: scanf("%d", &num);
              insert(num);
              break;

      case 2: printf("enter number\n");
              scanf("%d", &num); delete(num);
              break;

      case 3: printf("enter the value\n");
              scanf("%d", &num); find(num);
              break;

      case 4: delete_list(); break;

      case 5: print_list();break;

      case 6: printf("%d", HEAD->val); break;

      case 7: printf("%d", TAIL->val); break;

      default: printf("enter valid option\n");break;
    }
  }
}
