#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int last_index, level;

struct node
{
  int val;
  struct node *left;
  struct node *right;
  struct node *parent;
};

struct node *ROOT = NULL;

struct node* arr[1000] = {NULL} ;//= {NULL};

int left_child(int index)
{
  return (2*index)+1;
}

int right_child(int index)
{
  return (2*index) + 2;
}

int parent(int index)
{
  return (index-1)/2;
}

void tree_correction(int parent_index, int child_index)
{

  if(arr[parent_index]->val < arr[child_index]->val)
  {
    int temp;
    temp = arr[parent_index]->val;
    arr[parent_index]->val = arr[child_index]->val;
    arr[child_index]->val = temp;

    child_index = parent_index;
    parent_index = parent(child_index);

    tree_correction(parent_index, child_index);
  }

  else
  {
    printf("everything alright\n");
  }

}

struct node * memalloc(int num)
{
  struct node *p;
  p = (struct node*)malloc(sizeof(struct node));
  p->val = num;
  p->left = NULL;
  p->right = NULL;

  return p;
}

int power(int a, int b)
{
  int i = 0;

  while(i<=b)
  {
    a = 2 * a;
    i = i+1;
  }

  return a;
}

void print()
{
  int index = 0, level = 0, power_index = 0, two_multiple = 1, count = 0;
  level = last_index/2;

  if(arr[0]==NULL)
  {
    printf("tree is empty\n");
    return;
  }
  while(index<=last_index)
  {

    if(index == 0)
    {
      for(int i = 0; i<level; i++)
      {
        printf(" ");
      }
      level = level -1;
    }
    for(int i = 0; i<power(2,level)/2; i++)
    {
      printf(" ");
    }

    printf(" %d ", arr[index]->val);

    for(int i = 0; i<power(2,level)/2; i++)
    {
      printf(" ");
    }

    count = count +1;

      index = index+1;
      if(count >= two_multiple)
      {
        for(int i = 0; i<level; i++)
        {
          printf(" ");
        }
        printf("\n");
        for(int i = 0; i<level; i++)
        {
          printf(" ");
        }
        level = level - 1;
        two_multiple = 2*two_multiple;
        count = 0;
      }


  }
  printf("\n\n\n");
}

void insert(int num, int index)
{
  if(ROOT == NULL)
  {
    arr[0] = memalloc(num);//->val = num;
    ROOT = arr[0];
  }

  else
  {
    if(arr[index]!=NULL)
    {
      if(arr[left_child(index)]==NULL)
      {
        arr[left_child(index)] = memalloc(num); //->val = num;
        arr[left_child(index)]->parent = arr[index];
        arr[index]->left = arr[left_child(index)];
        last_index = left_child(index);
        level = last_index/2;
        tree_correction(index ,left_child(index));
      }

      else if(arr[right_child(index)]==NULL)
      {
        arr[right_child(index)]= memalloc(num);//->val = num;
        arr[right_child(index)]->parent = arr[index];
        arr[index]->right = arr[right_child(index)];
        last_index = right_child(index);
        level = last_index/2;
        tree_correction(index,right_child(index));
      }

      else
      {
        index = index + 1;
        insert(num, index);
      }
    }
  }
}


void horizontal(struct node *t, int lev)
{
    int l = lev;

    if (t == NULL) return;

    horizontal(t->right, lev + 1);
    while (l--) printf("    ");

//    if(t->colour == Red)
  //  {
  //    red();
      printf("-> %d\n", t->val);
  //  }

  //  else if(t->colour == Blue)
//    {
//      blue();
      printf("-> %d\n", t->val);
//    }
    horizontal(t->left, lev + 1);
}

void swap(int a, int b)
{
  int temp;
  temp = arr[a]->val;
  arr[a]->val = arr[b]->val;
  arr[b]->val = temp;
}

void tree_correction_deletion(int index)
{
  if(arr[0] == NULL)
  {
    printf("\nthe tree is empty\n");
    printf("this hosuld not work 1\n");
  }

  if(arr[index] == NULL)
  {
    printf("this should not work 2\n");
    return;
  }


    int left_child_index = left_child(index);
    int right_child_index = right_child(index);

  if(arr[left_child_index]==NULL && arr[right_child_index]==NULL)
  {
    printf("everything alright");
    return;
  }

  if(arr[left_child_index]!=NULL && arr[right_child_index]==NULL)
  {
    printf("this should not work 3\n");
    if(arr[left_child_index]->val > arr[index]->val)
    {
      swap(index,left_child_index);
    }
    tree_correction_deletion(left_child_index);
  }



  if(arr[left_child_index]!=NULL && arr[right_child_index]!=NULL)
  {
    printf("this should not work 4\n");
   if((arr[index]->val > arr[left_child_index]->val)  && (arr[index]->val >arr[right_child_index]->val))
    {
      printf("everything is fine\n");
    }

    else if((arr[index]->val <= arr[left_child_index]->val) && (arr[index]->val >arr[right_child_index]->val))
    {
      swap(index,left_child_index);
      tree_correction_deletion(left_child_index);
    }

    else if((arr[index]->val >arr[left_child_index]->val) && (arr[index]->val <arr[right_child_index]->val))
    {
      swap(index, right_child_index);
      tree_correction_deletion(right_child_index);
    }

    else if((arr[index]->val <=arr[left_child_index]->val) && (arr[index]->val < arr[right_child_index]->val))
    {
      if(arr[left_child_index]->val > arr[right_child_index]->val)
      {
        swap(index,left_child_index);
        tree_correction_deletion(left_child_index);
      }

      else if(arr[left_child_index]->val < arr[right_child_index]->val)
      {
        swap(index, right_child_index);
        tree_correction_deletion(right_child_index);
      }

      else
      {
        swap(index, left_child_index);
        tree_correction_deletion(left_child_index);
      }
    }
  }
}

void delete()
{
  printf("last_index =  %d", last_index);

  printf("why is this not working\n");
  arr[0]->val = arr[last_index]->val;
  free(arr[last_index]);
  printf("coming till here\n");
  arr[last_index] = NULL;
  printf("coming till here 2\n");
  if(arr[0]==NULL)
  {
    ROOT = NULL;
  }
//  arr[last_index] = NULL;
  last_index = last_index -1;
  if(last_index == -1)
  {
    last_index = 0;
  }
  printf("coming till here 3\n");
  //printf("arr[0] = %d", arr[0]->val);
  printf("this working\n");
  tree_correction_deletion(0);
}

int main()
{
  int num;

  while(1)
  {
    printf("1 - insert value\n");
    printf("2 - find max\n");
    printf("3 - print tree\n");
    printf("4 - delete root\n");
    printf("5 - print horizontal\n");
    printf("enter your choice\n");

    int choice;
    scanf("%d", &choice);

    switch(choice)
    {
      case 1: printf("enter the value\n");
              scanf("%d", &num); insert(num, 0);break;

      case 2: printf("%d\n", ROOT->val);break;

      case 3: print(ROOT,0);break;

      case 4: delete();break;

      case 5: horizontal(ROOT, 1);

      default : printf("enter valid choice\n");
    }
  }

}
