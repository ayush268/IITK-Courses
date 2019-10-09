#include <stdio.h>
#include <stdlib.h>

typedef long long ll;
typedef struct Node
{
  int x;
  struct Node *n;
} node;

void enqueue(node** head, int elem)
{
  node* new = (node*)malloc(sizeof(node));
  new->x = elem;
  new->n = NULL;

  if(*head == NULL)
  {
    *head = new;
    return;
  }

  node* curr = *head;

  while(curr->n != NULL)
    curr = curr->n;

  curr->n = new;
}

void dequeue(node** head)
{
  node* curr = *head;
  *head = curr->n;
  free(curr);
}

int main()
{
  int t,q,opcode,elem,count;
  scanf("%d", &t);
  while(t--)
  {
    scanf("%d", &q);
    count = 0;
    node* head = NULL;
    while(q--)
    {
      scanf("%d", &opcode);
      if(opcode == 1)
      {
        ++count;
        scanf("%d",&elem);
        enqueue(&head, elem);
        printf("%d\n",elem);
      }
      else if(opcode == 2)
      {
        if(count)
        {
          --count;
          printf("%d\n", head->x);
          dequeue(&head);
        }
        else
          printf("Empty\n");
      }
      else
      {
        if(count)
          printf("False\n");
        else
          printf("True\n");
      }
    }
  }
  return 0;
}
