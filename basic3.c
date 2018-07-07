#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<string.h>
//#include<graphics.h>
//#include<dos.h>

int tree_stack[1000];

void gotoxy(int x, int y) {

 char essq[100];  /* String variable to hold the escape sequence */

 char xstr[100];  /* Strings to hold the x and y coordinates */

 char ystr[100];  /* Escape sequences must be built with characters */

 /*

 ** Convert the screen coordinates to strings

 */

 sprintf(xstr, "%d", x);

 sprintf(ystr, "%d", y);

 /*

 ** Build the escape sequence (vertical move)

 */

 essq[0] = '\0';

 strcat(essq, "\033[");

 strcat(essq, ystr);

 /*

 ** Described in man terminfo as vpa=\E[%p1%dd

 ** Vertical position absolute

 */

 strcat(essq, "d");

 /*

 ** Horizontal move

 ** Horizontal position absolute

 */

 strcat(essq, "\033[");

 strcat(essq, xstr);

 /* Described in man terminfo as hpa=\E[%p1%dG */

 strcat(essq, "G");

 /*

 ** Execute the escape sequence

 ** This will move the cursor to x, y

 */

 printf("%s", essq);

}

struct node
{
  int val;
  struct node *left, *right;
  struct node *parent;
};

struct node *ROOT = NULL;

void red() {
  printf("\033[1;31m");
}

void blue()
{
  printf("\033[1;34m");
}
void insert_rp(struct node *p, struct node *q)
{

  if(p->val > q->val)
  {
    if(q->right == NULL)
    {
      q->right = p;
      p->parent = q;
    }

    else if(q->right!=NULL)
    {
      insert_rp(p, q->right);
    }
  }

  else if(p->val < q->val)
  {
    if(q->left == NULL)
    {
      q->left = p;
      p->parent = q;
    }

    else if(q->left!=NULL)
    {
      insert_rp(p, q->left);
    }
  }
}

void insert(int num)
{
  struct node *p;
  p = (struct node *)malloc(sizeof(struct node));
  p->val = num;
  p->left = NULL;
  p->right = NULL;

  if(ROOT == NULL)
  {
    ROOT = p;
  }

  else
  {
    insert_rp(p, ROOT);
  }
}


void find(int num, struct node *q, int count)
{
  count++;
  if(ROOT==NULL)
  {
    printf("tree is empty\n");
  }

  else if(q==NULL)
  {
    printf("number not found\n");
  }

  else if(num == q->val)
  {
    printf("number found in level %d ", count);
  }

  else if(num >= q->val)
  {
    find(num, q->right, count);
  }

  else if(num < q->val)
  {
    find(num, q->left, count);
  }
}

struct node *pl; // parent
int found = 1;

struct node *find_node(int num, struct node *q)
{
  if(q==NULL)
  {
    printf("number not found\n");
    return q;
  }

  else if(num == q->val)
  {
    printf("number found val = %d", pl->val);
    return q;
  }

  else if(num > q->val)
  {
    pl = q;
    find_node(num, q->right);
  }

  else if(num < q->val)
  {
    pl = q;
    find_node(num, q->left);
  }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void delete_root(int num, struct node *q)
{
  struct node *r, *temp, *parent; // q will be the root of the subtree
  parent = pl;


        if(found = 0)
        {
          printf("this works\n");
          return;
        }

  if(q->val==num)
  {
      if(q->right==NULL && q->left==NULL)
      {
        if(ROOT->val==num)
        {
          free(ROOT);
          ROOT = NULL;
          return;
        }

        if(parent->left==q)
        {
          parent->left = NULL;
        }

        else if(parent->right==q)
        {
          parent->right = NULL;
        }

        free(q);
        return;
      }

      else if(q->right!=NULL)
      {
        r = q->right;
        temp = r;
        while(r->left!=NULL)
        {
          r = r->left;
        }
        r->left = q->left;

          if(ROOT->val == num)
          {
            free(ROOT);
            ROOT = temp;
            return;
          }

          if(parent->left==q)
          {
            parent->left = r;
          }

          else if(parent ->right ==q)
          {
            parent->right = r;
          }

          free(q);
          q = temp;

        }

      else if(q->left!=NULL && q->right==NULL)
      {
          r = q->left;

        if(q = ROOT)
        {
          free(ROOT);
          ROOT = r;
          return;
        }

      if(parent->left==q)
      {
        parent->left = r;
      }

      else if(parent ->right ==q)
      {
        parent->right = r;
      }

      free(q);
      q = r;

    }
  }
}


void delete(int num)
{
      struct node *q;

      if(num == ROOT->val)
      {
//        printf("it is a root value\n");
        delete_root(num, ROOT);
        return;
      }

      q = find_node(num, ROOT);
      if(q==NULL)
      {
        return;
      }
      struct node *lt, *rt, *ltl, *ltr, *rtl, *rtr;

      lt = q->left;
      rt = q->right;

      delete_root(num, q);
/*
      if(num==lt->num)
      {
        delete_root(num,);
      }

      else if(num == rt->num)
      {
        delete_root(num,lt);
      }
*/

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void print_tree(struct node *q)
{
  if(ROOT==NULL)
  {
    printf("the tree is empty\n");
  }

  else if(q==NULL)
  {
    return;
  }

  else
  {
    printf("%d ->", q->val);
    print_tree(q->left);
    print_tree(q->right);
  }

}

void delete_tree()
{
  while(ROOT!=NULL)
  {
  //  printf("ROOT = %d\n", ROOT->val);
    delete(ROOT->val);
  }

}

void print_right()
{
  struct node *q;
  q = ROOT;

  while(q!=NULL)
  {
    printf("%d ->", q->val);
    q = q->right;

  }
}

void print_left()
{
  struct node *q;
  q=ROOT;

  while(q!=NULL)
  {
    printf("%d -> ", q->val);
    q = q->left;
  }
}

void horizontal(struct node *t, int level)
{
    int l = level;

    if (t == NULL) return;

    horizontal(t->right, level + 1);
    while (l--) printf("    ");
  //  setcolour(2);
    printf("-> %d\n", t->val);
    horizontal(t->left, level + 1);
}

void print_vertical(struct node *nd, int *x, int y)
{
    if (nd == NULL) return;

    print_vertical(nd->left, x, y + 4);
    gotoxy(*x, y);
    printf("%d", nd->val);
    *x += 4;
    print_vertical(nd->right, x, y + 4);
}

void print_parent(int num, struct node *q)
{
  if(q ->val==num)
  {
    if(q==ROOT)
    {
      printf("this is root value\n");
    }

    else
    {
      struct node *parent = q->parent;
      printf("parent of %d is %d",q->val, parent ->val);
    }
  }

  else if(num > q->val)
  {
    print_parent(num, q->right);
  }

  else if(num < q->val)
  {
    print_parent(num, q->left);
  }

  else
  {
    printf("that number does not exist\n");
  }
}



int main()
{
  int num;
  int x = 0;

//  printf(“\033[0;31m”); //Set the text to the color red
//    printf("\033[1;31m")


  while(1)
  {
    printf("\n\n\n\n");
    printf("1 - insert value\n");
    printf("2 - find value\n");
    printf("3 - print root value\n");
    printf("4 - delete value\n");
    printf("5 - delete tree\n");
    printf("6 - print tree\n");
    printf("7 - print_horizontal\n");
    printf("8 - print vertical\n");
    printf("9 - print parent of a value\n");
    printf("enter your choice\n");

    int choice;
    scanf("%d", &choice);

    switch(choice)
    {
      case 1: printf("enter the value\n");
              scanf("%d", &num);insert(num); break;

      case 2: printf("enter the value to find\n");
              scanf("%d", &num); find(num, ROOT, 1); break;

      case 3: printf("%d", ROOT->val);break;// scanf("%d", &num);
            //  delete(num);break;

      case 4: printf("enter the number\n");
              scanf("%d", &num); delete(num); break;

      case 5: delete_tree();break;

      case 6: print_tree(ROOT);break;

      case 7: horizontal(ROOT, 1);break;

      case 8: print_vertical(ROOT, &x, 0);printf("\n\n");break;

      case 9: printf("enter a value\n");
              scanf("%d", &num); print_parent(num, ROOT);break;

      default: printf("enter valid choice\n");

    }
  }
}
