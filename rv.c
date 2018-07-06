#include<stdio.h>
#include<stdlib.h>


//tree size will be 2(log(n+1))
// n is number of nodes
enum colour{Red , Blue};
enum colouring_required{no, yes};

struct node
{
  int val;
  int colour;
  struct node *left;
  struct node *right;
  struct node *parent;
};

void red () {
  printf("\033[1;31m");
}

void blue()
{
  printf("\033[1;34m");
}

struct node *ROOT = NULL;

void insert_rp(struct node *p, struct node *q)
{
  if(p->val > q->val)     //q is for traversing, I need to insert the node p at right position
  {
    if(q->right!=NULL)
    {
      insert_rp(p,q->right);
    }

    else
    {
      q->right = p;
      p->parent = q;
    }

  }

  else if(p->val < q->val)
  {
    if(q->left!=NULL)
    {
      insert_rp(p, q->left);
    }

    else
    {
      q->left = p;
      p->parent = q;
    }
  }
}

void left_rot_colour_change(struct node *q) //this might not be correct, change this
{
  struct node *q_lchild = q->left;

  if(q->colour == Blue)
  {
    q ->colour = Red;
  }

  else if(q ->colour == Red)
  {
    q ->colour = Blue;
  }

  if(q_lchild->colour == Blue)
  {
    q_lchild->colour = Red;
  }

  else if(q_lchild->colour == Red)
  {
    q_lchild->colour = Blue;
  }

  if(ROOT ->colour == Red)
  {
    ROOT->colour = Blue;
  }

}

void right_rot_colour_change(struct node *q)
{
  struct node *q_rchild = q->right;

  if(q->colour == Red)
  {
    q->colour = Blue;
  }

  else if(q->colour == Blue)
  {
    q->colour = Red;
  }

  if(q_rchild->colour == Red)
  {
    q_rchild->colour = Blue;
  }

  else if(q->colour == Blue)
  {
    q_rchild->colour = Red;
  }

  if(ROOT->colour == Red)
  {
    ROOT ->colour = Blue;
  }
}


void left_rotation(struct node*q, int exists)   // q here must be the grand parent of the just inserted child
{
  struct node *q_rchild, *q_parent; // child node is the new node inserted generally;
                                    // the rest is as it is
  q_parent = q->parent;             // here q_rchild is the
  q_rchild = q->right;

  printf("\n\n in function left rotation\n\n");

  if(q==ROOT)
  {
    printf("this ROOT thing should work\n");
    ROOT = q_rchild;
    q->right = q_rchild ->left;
    q_rchild ->left = q;
    q->parent = q_rchild;
  //  q_rchild ->parent = NULL;
    printf("this root thing should work\n");
    left_rot_colour_change(q_rchild);
  }


  else if(q_parent -> left == q)
  {
    printf("q = %d, q_parent = %d, q_rchild = %d\n", q->val, q_parent->val, q_rchild->val);

    printf("this should work\n");
    q_parent ->left = q_rchild;
    q->right = q_rchild -> left;
    q_rchild ->left = q;
    q_rchild->parent = q_parent;
    q->parent = q_rchild;

  //  if(q == ROOT)
    //{
  //    printf("this should not work too\n");
    //  ROOT = q_rchild;
  //  }
    if(exists == yes)
    {
      left_rot_colour_change(q_rchild);
    }
  }

  else if(q_parent -> right == q)
  {
    printf("q = %d, q_parent = %d, q_rchild = %d\n", q->val, q_parent->val, q_rchild->val);

    printf("this should now work\n");
    q_parent ->right = q_rchild;
    q->right = q_rchild ->left;
    q_rchild ->left = q;
    q_rchild->parent= q_parent;
    q->parent = q_rchild;

//    if(q_parent == ROOT)
//    {
//      ROOT = q;
//    }
    if(exists==yes)
    {
      left_rot_colour_change(q_rchild);
    }
  }
}


void right_rotation(struct node *q, int exists)  //q is the node that is to be rotated
{                                    // decide where to rotate in a seperate function
  struct node *q_lchild, *q_parent;

  q_parent = q->parent;
  q_lchild = q->left;

  if(q==ROOT)
  {
    ROOT = q_lchild;
    q->left = q_lchild->right;
    q_lchild->right = q;
    q->parent = q_lchild;
    q_lchild->parent = NULL;
  }

  if(q_parent->left == q)
  {
    q_parent->left = q_lchild;
    q->left = q_lchild -> right;
    q_lchild ->right = q;
    q_lchild->parent = q_parent;
    q->parent = q_lchild;

    if(exists == yes)
    {
      right_rot_colour_change(q_lchild);
    }
  }

  else if(q_parent->right == q)
  {
    q_parent ->right = q_lchild;
    q->left = q_lchild->right;
    q_lchild->right = q;
    q_lchild ->parent = q_parent;
    q->parent = q_lchild;

    if(exists == yes)
    {
    right_rot_colour_change(q_lchild);
    }
  }

}

void recolour(struct node *q) // change the colours of both the childs and the node
{
  struct node *q_lchild = q->left, *q_rchild = q->right;

  if(q->colour == Red)
  {
    q->colour = Blue;
  }

  else if(q->colour == Blue)
  {
    q->colour = Red;

    if(q==ROOT)
    {
      printf("colour change of main node should work\n");
      q->colour = Blue;
    }
  }

  if(q_lchild ->colour == Red)
  {
    printf("colour change of left child should work/n");
    q_lchild ->colour = Blue;
  }

  else if(q_lchild ->colour == Blue)
  {
    q_lchild ->colour = Red;
  }

  if(q_rchild->colour == Red)
  {
    printf("colour change of right child should work\n");
    q_rchild ->colour = Blue;
  }

  else if(q_rchild ->colour == Blue)
  {
    q_rchild ->colour = Red;
  }
}


void check_for_cases(struct node *q)
{
  struct node *q_parent = q->parent , *q_grand_parent = q_parent->parent, *q_parent_sibling ;

//////////////////////////////////////////////////////////////////////////////////////////
//                     Case I
// Normal insertion case

  if(q->colour == Red && q_parent->colour == Blue)
  {
    printf("everything is perfect\n");
    return;
  }

//////////////////////////////////////////////////////////////////////////////////////////
//                     Case II
// grand parent has only one child, so rotation takes place at grand parent

  if(q->colour == Red && q_parent->colour == Red)  //here q is the new node that is inserted
  {
//    printf("this function working\n");
      if(q_grand_parent ->right == q_parent)
      {
        printf("grand_parent->right == q_parent working\n");
        printf("q = %d, q_parent = %d, q_grand_parent = %d\n",q->val, q_parent->val, q_grand_parent->val );
      //  printf("this working too\n");
          if(q_grand_parent ->left == NULL)
          {
            printf("grand_parent->left = NULL working\n");
//            printf("this working too\n");
              if(q == q_parent ->left)
              {
                printf("this should not work\n");
                printf("this working too\n");
                right_rotation(q_parent, no);       // no - for colout change not required
                left_rotation(q_grand_parent, yes); // yes - for colour change required
              }

              else if(q == q_parent ->right)
              {
                printf("this should work\n");
                left_rotation(q_grand_parent,yes);
                printf("this worked\n");
                printf("this working\n");
              }
          }

          else if(q_grand_parent ->left !=NULL) //this case is for when the sibliing of parent is red
          {                                     //doing this in a seperate function
            printf("q_grand_parent ! = NULL working\n");
              q_parent_sibling = q_grand_parent->left;

              if(q == q_parent ->left)
              {
                if(q_parent_sibling -> colour == Red)
                {
                  recolour(q_grand_parent); // here we need to keep recursion with this same function so if Red-Red error exists it would shift up
                  check_for_cases(q_grand_parent);
                }

                else if(q_parent_sibling ->colour == Blue)
                {
                  right_rotation(q_parent, no);
                  left_rotation(q_grand_parent, yes);
                }
              }

              else if(q == q_parent ->right)
              {
                printf("q = q_parent ->right should be working\n");
                if(q_parent_sibling ->colour == Red)
                {
                   printf("parent_sibling ->colour = Blue should be working where it should not be\n");
                   printf("q_grand_parent = %d\n", q_grand_parent->val);

                  recolour(q_grand_parent);
                  check_for_cases(q_grand_parent);
                }

                else if(q_parent_sibling ->colour == Blue)
                {
                  printf("parent_sibling ->colour = Blue should be working\n");
                  left_rotation(q_grand_parent, yes);
                  check_for_cases(q_grand_parent);
                }
              }
          }
      }

      else if(q_grand_parent ->left == q_parent)
      {
        if(q_grand_parent -> right==NULL)
        {
            if(q == q_parent->left)
            {
              right_rotation(q_grand_parent, yes);
            }

            else if(q == q_parent ->left)
            {
              left_rotation(q_parent, no);
              right_rotation(q_grand_parent, yes);
            }
        }

        else if(q_grand_parent ->right !=NULL)
        {
            q_parent_sibling = q_grand_parent->right;

            if(q == q_parent-> left)
            {
              if(q_parent_sibling ->colour == Red)
              {
                recolour(q_grand_parent);
                check_for_cases(q_grand_parent);
              }

              else if(q_parent_sibling ->colour == Blue)
              {
                right_rotation(q_grand_parent, yes);
              }
            }

            else if(q == q_parent ->right)
            {
              if(q_parent_sibling == Red)
              {
                recolour(q_grand_parent);
                check_for_cases(q_grand_parent);
              }

              else if(q_parent_sibling->colour == Blue)
              {
                left_rotation(q_parent, no);
                right_rotation(q_grand_parent, yes);
              }
            }
        }

      }
  }
/////////////////////////////////////////////////////////////////////////////////////////

}

// 8867785464 - Nibedit Dey

void insert(int num)
{
  struct node *p, *parent, *grand_parent;
  p = (struct node*)malloc(sizeof(struct node));

  p->val = num;
  p->colour = Red;

  if(ROOT==NULL)
  {
   ROOT = p;
   ROOT ->colour = Blue;
  }

  else
  {
    insert_rp(p, ROOT);

    parent = p->parent;
    grand_parent = parent->parent;
    check_for_cases(p);

  }

}

void horizontal(struct node *t, int level)
{
    int l = level;

    if (t == NULL) return;

    horizontal(t->right, level + 1);
    while (l--) printf("    ");
  //  setcolour(2);

  //  printf("-> %d\n", t->val);
    if(t->colour == Red)
    {
      red();
      printf("-> %d\n", t->val);
    }

    else if(t->colour == Blue)
    {
      blue();
      printf("-> %d\n", t->val);
    }
    horizontal(t->left, level + 1);
}


int main()
{
  int num;


  while(1)
  {
    printf("\033[0m");
    printf("1 - enter value\n");
    printf("2 - print whole tree\n");
    printf("3 - print root\n");
    printf("4 - delete value\n");
    printf("5 - delete tree\n");
    printf("6 - print tree\n");
    printf("7 - print horizontal\n");
    printf("8 - print vertical\n");
    printf("enter your choice\n");
    int choice;
    scanf("%d", &choice);

    switch(choice)
    {
      case 1: printf("enter value\n");
              scanf("%d", &num);insert(num);break;

      case 2: horizontal(ROOT, 1);break;

      default : printf("enter valid option\n");
    }
  }
}
