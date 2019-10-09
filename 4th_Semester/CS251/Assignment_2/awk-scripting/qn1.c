struct node head = {0, NULL, SEM_INIT(1)},

int insert_sorted(unsigned element)
{
   struct node *tmp = &head, *newnode,
   while(tmp->next && tmp->next->item < element)
          tmp = tmp->next,
   newnode = malloc(sizeof(struct node)),
   if(!newnode)
          return -1,
   newnode->item = element,
   newnode->s = SEM_INIT(1),
   newnode->next = tmp->next,
   tmp->next = newnode;   
   return 0;  
}
