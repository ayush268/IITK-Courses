#include <iostream>
#include <string>
using namespace std;

typedef struct Tree
{
  int size;
  string data;
  struct Tree *left;
  struct Tree *right;
} tree;

tree *newTree(string str)
{
  tree* t = (tree*)malloc(sizeof(tree));
  t->size = 1;
  t->data = str;
  t->left = NULL;
  t->right = NULL;
  return t;
}

tree *insert(tree* head, string str)
{
  if(head == NULL)
    return newTree(str);
  else
  {
    if(str < head->data)
    {
      head->left = insert(head->left, str);
      head->size = head->size + 1;
    }
    else if(str > head->data)
    {
      head->right = insert(head->right, str);
      head->size = head->size + 1;
    }
    return head;
  }
}

int findRank(tree* head, string str)
{
  int rank = 1;
  tree* curr = head;
  while(curr) {
    if(str < curr->data)
      curr = curr->left;
    else if(str > curr->data)
    {
      if(curr->left)
        rank += 1 + curr->left->size;
      else
        rank++;
      curr = curr->right;
    }
    else
    {
      if(curr->left)
        return rank + curr->left->size;
      else
        return rank;
    }
  }
  return -1;
}

tree* getMin(tree* head)
{
  tree* curr = head;
  while(curr->left != NULL)
    curr = curr->left;
  return curr;
}

tree *remove(tree* head, string str)
{
  if(head == NULL)
    return head;
  head->size = head->size - 1;
  if(str < head->data)
  {
    head->left = remove(head->left, str);
  }
  else if(str > head->data)
  {
    head->right = remove(head->right, str);
  }
  else
  {
    if(head->left == NULL)
    {
      tree* tmp = head->right;
      free(head);
      return tmp;
    }
    else if(head->right == NULL)
    {
      tree* tmp = head->left;
      free(head);
      return tmp;
    }
    tree* tmp = getMin(head->right);
    head->data = tmp->data;
    head->right = remove(head->right, tmp->data);
  }
  return head;
}

int main()
{
  ios::sync_with_stdio(false);cin.tie(0);
  int q;
  string str1,str2;
  cin >> q;
  tree* head = NULL;
  while(q--)
  {
    cin >> str1;
    cin >> str2;
    if(str1 == "learn")
      head = insert(head, str2);
    else if(str1 == "forget")
    {
      printf("%d\n", findRank(head, str2));
      head = remove(head, str2);
    }
    else
      printf("%d\n", findRank(head, str2));
  }
}
