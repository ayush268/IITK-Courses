#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define pb push_back
#define sz(a) int((a).size())
#define cl(a) a.clear()
#define rsz(a,n) a.resize(n)

vvi tree;

void printTree(int root)
{
  for(int i=0;i<(sz(tree[root])/2);i++)
  {
    printTree(tree[root][i]);
  }
  printf("%d ",root+1);
  for(int i=(sz(tree[root])/2);i<sz(tree[root]);i++)
  {
    printTree(tree[root][i]);
  }
}

void merge(int x, int l, int m, int r)
{
  int n1 = m-l+1;
  int n2 = r-m;
  int arr1[n1],arr2[n2];
  for(int i=0;i<n1;i++)
    arr1[i] = tree[x][l+i];
  for(int j=0;j<n2;j++)
    arr2[j] = tree[x][m+1+j];
  
  int i=0,j=0,k=l;
  
  while(i<n1 && j<n2)
  {
    if(arr1[i] <= arr2[j])
    {
      tree[x][k] = arr1[i];
      i++;
    }
    else
    {
      tree[x][k] = arr2[j];
      j++;
    }
    k++;
  }

  while(i<n1)
  {
    tree[x][k] = arr1[i];
    i++;
    k++;
  }
  
  while(j<n2)
  {
    tree[x][k] = arr2[j];
    j++;
    k++;
  }
}

void mergeSort(int x, int l, int r)
{
  if(l<r)
  {
    int m = l+(r-l)/2;
    mergeSort(x,l,m);
    mergeSort(x,m+1,r);
    merge(x,l,m,r);
  }
}

int main()
{
  int t,n,a,b;
  scanf("%d",&t);
  while(t--)
  {
    scanf("%d",&n);
    cl(tree);
    rsz(tree,n);
    for(int i=0;i<n-1;i++)
    {
      scanf("%d %d", &a, &b);
      tree[a-1].pb(b-1);
    }
    for(int i=0;i<n;i++)
      mergeSort(i,0,sz(tree[i])-1);
//    for(int i=0;i<n;i++)
//    {
//      printf("%d - ",i+1);
//      for(int j=0;j<sz(tree[i]);j++)
//      {
//        printf("%d ",tree[i][j]+1);
//      }
//      printf("\n");
//    }
    printTree(0);
    printf("\n");
  }
  return 0;
}
