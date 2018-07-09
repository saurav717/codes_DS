#include<stdio.h>
#include<stdlib.h>
#include <math.h>

// maxheap using arrays
// this can also be implemented for priority queues since the heap is in array form

// say the value of a node is priority of a task
// the root node will always be the node with highest priority



//int arr[1000] ={0},   bottom_cap;

int last_index;
int ROOT, level;



////////////////////////////////////////////////////////////////////////////////////////////////////
//                            Left child function

int left_child(int i) // here i is the index of an element in an array
{
  return (2*i)+1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//                           Right child function

int right_child(int i) // same here, i is the index of an element in the array, say it is parent
{
  return (2*i)+2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//                            Parent function

int parent(int i)
{
  return (i-1)/2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//                            Tree correction

void tree_correction(int arr[],int parent_index, int child_index)
{
  if(arr[parent_index] < arr[child_index])
  {
    int temp;                                  // Tree correction
    temp = arr[parent_index];
    arr[parent_index] = arr[child_index];
    arr[child_index] = temp;

    child_index = parent_index;
    parent_index = parent(child_index);

    tree_correction(arr, parent_index, child_index);
  }

  else
  {
    printf("everything's alright\n");                        // Tree correction
  }

}



/////////////////////////////////////////////////////////////////////////////////////////////////////
//                            Insert function

void insert(int arr[], int num, int index)
{
  if(ROOT == 0)
  {
    arr[0] = num;
    ROOT = arr[0];
  }
                                                             // Insert function
  else
  {
    if(arr[index] !=0)
    {
      if(arr[left_child(index)]==0)
      {
        arr[left_child(index)] = num;
        last_index = left_child(index);
        level = last_index/2;
        tree_correction(arr,index, left_child(index));
      }

      else if(arr[right_child(index)]==0)
      {
        arr[right_child(index)] = num;
        last_index = right_child(index);
        level = last_index/2;
        tree_correction(arr,index,right_child(index));
      }

      else
      {                                                        // Insert function
        index = index + 1;
        insert(arr,num, index);
      }
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
//              power function

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

////////////////////////////////////////////////////////////////////////////////
//              Print function

void print(int arr[])
{
  int index = 0, level = 0, power_index = 0, two_multiple = 1, count = 0;
  level = last_index/2;
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

    printf(" %d ", arr[index]);

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

////////////////////////////////////////////////////////////////////////////////
//              Swap function

void swap(int arr[], int index1, int index2)
{
  int temp;

  temp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = temp;
}
////////////////////////////////////////////////////////////////////////////////
//               Tree correction for deletion function

void tree_correction_deletion(int arr[], int index)// index is our element of interest
{

  int left_child_index = left_child(index);
  int right_child_index = right_child(index);

  if(arr[0] == 0)
  {
    printf("\nthe tree is empty\n\n");
    return;
  }

  if(arr[index] == 0)
  {
    return;
  }

  if(arr[index] > arr[left_child_index] && arr[index] > arr[right_child_index])
  {
    printf("everything is fine\n");
  }

  else if(arr[index]<arr[left_child_index] && arr[index] > arr[right_child_index])
  {
//    int temp;
//    temp = arr[index];
//    arr[index] = arr[left_child_index];
//    arr[left_child_index]=temp;

    swap(arr, index, left_child_index);

    tree_correction_deletion(arr, left_child_index);
  }

  else if(arr[index] > arr[left_child_index] && arr[index] < arr[right_child_index])
  {
//    int temp;

//    temp = arr[index];
//    arr[index] = arr[right_child_index];
//    arr[right_child_index] = temp;

    swap(arr,index, right_child_index);

    tree_correction_deletion(arr,right_child_index);
  }

  else if(arr[index] < arr[left_child_index] && arr[index] < arr[right_child_index])
  {
    if(arr[left_child_index] > arr[right_child_index])
    {
  //    int temp;

//      temp = arr[index];
//      arr[index] = arr[left_child_index];
//      arr[left_child_index] = temp;

      swap(arr, index, left_child_index);

      tree_correction_deletion(arr, left_child_index);
    }

    else if(arr[left_child_index] < arr[right_child_index])
    {
//      int temp;

  //    temp = arr[index];
//      arr[index] = arr[right_child_index];
//      arr[right_child_index] = temp;

      swap(arr, index, right_child_index);

      tree_correction_deletion(arr, right_child_index);
    }

    else
    {
//      int temp;

//      temp = arr[index];
//      arr[index] = arr[left_child_index];
//      arr[left_child_index] = temp;

      swap(arr, index, left_child_index);

      tree_correction_deletion(arr, left_child_index);
    }
  }



}

////////////////////////////////////////////////////////////////////////////////
//               Delete function

void delete(int num, int arr[])
{
  arr[0] = arr[last_index];
  arr[last_index] = 0;
  last_index = last_index -1;

  tree_correction_deletion(arr, 0);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
  int arr[100] = { 0 }, last_ind = 0;
  int num;

  printf("\n\n");

  while(1)
  {
    printf("1 - insert value\n");
    printf("2 - printf the array\n");
    printf("3 - get max\n");
    printf("4 - delete max\n");
    printf("enter your choice\n");
    int choice;
    scanf("%d", &choice);

    switch(choice)
    {
      case 1: printf("enter the value\n");
              scanf("%d", &num); insert(arr,num, 0);break;

      case 2: print(arr);break;

      case 3: printf(" root = %d\n", arr[0]);

      case 4: delete(arr[0], arr);


      default : printf("enter valid option\n");
    }
  }
}
