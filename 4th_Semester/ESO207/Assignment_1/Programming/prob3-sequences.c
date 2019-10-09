#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int x;
  struct Node *n;
} node;

void enqueue(node** head, int elem)
{
  node* new = (node*)malloc(sizeof(node));
  new->x = elem;

  new->n = *head;
  *head = new;
}

void dequeue(node** head)
{
  node* curr = *head;
  if(curr->n == NULL)
  {
    printf("%d\n", curr->x);
    *head = NULL;
    free(curr);
    return;
  }

  while(curr->n->n != NULL)
    curr = curr->n;
  printf("%d\n",curr->n->x);

  free(curr->n);
  curr->n = NULL;
}

int main()
{
  int t,q,opcode,elem,n,i;
  scanf("%d", &t);
  while(t--)
  {
    scanf("%d %d", &n, &q);
    int count[n];
    node* head[n];
    for(int j=0;j<n;j++)
    {
      count[j]=0;
      head[j] = NULL;
    }
    while(q--)
    {
      scanf("%d", &opcode);
      if(opcode == 1)
      {
        scanf("%d %d",&elem, &i);
        ++count[i-1];
        enqueue(&head[i-1], elem);
        printf("%d\n",head[i-1]->x);
      }
      else if(opcode == 2)
      {
        scanf("%d",&i);
        if(count[i-1])
        {
          --count[i-1];
          dequeue(&head[i-1]);
        }
        else
          printf("Empty\n");
      }
      else
      {
        scanf("%d",&i);
        if(count[i-1])
          printf("False\n");
        else
          printf("True\n");
      }
    }
  }
  return 0;
}
