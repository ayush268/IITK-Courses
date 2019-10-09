#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<pair<bool, vi>> vbvi; 

#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define pb push_back
#define sz(a) int((a).size())
#define cl(a) a.clear()
#define rsz(a,n) a.resize(n)
#define mp(a,b) make_pair(a,b)
#define erase(vec,a) vec.erase(remove(vec.begin(), vec.end(), a), vec.end())

vvi city;
vb visited, ap;
vi parent, low, disc;
int t = 0;

void findBadIslands(int);
void dfs(int);
int min(int,int);

int main()
{
  ios::sync_with_stdio(false);cin.tie(0);
  int n,m,x,y;
  cin >> n >> m;
  rsz(city, n);
  while(m--)
  {
    cin >> x >> y;
    city[x].pb(y);
    city[y].pb(x);
  }

  findBadIslands(n);
  return 0;
}

int min(int a, int b)
{
  if(a > b)
    return b;
  return a;
}

void findBadIslands(int size)
{
  rsz(visited, size);
  rsz(ap, size);
  rsz(parent, size);
  rsz(low, size);
  rsz(disc, size);
  for(int i=0;i<size;i++)
  {
    visited[i] = false;
    ap[i] = false;
    parent[i] = -1;
    low[i] = 0;
  }
  dfs(0);

  for(int i=0;i<size;i++)
  {
    if(ap[i])
      cout << i << endl;
  }
}

void dfs(int u)
{
  visited[u] = true;
  disc[u] = ++t;
  low[u] = disc[u];
  int children = 0;
  for(int i=0;i<sz(city[u]);i++)
  {
    int v = city[u][i];
    if(visited[v] == false)
    {
      children++;
      parent[v] = u;
      dfs(v);

      low[u] = min(low[u], low[v]);
      if((parent[u] != -1) && (low[v] >= disc[u]))
        ap[u] = true;
      if((parent[u] == -1) && (children > 1))
        ap[u] = true;
    }
    else if(v != parent[u])
      low[u] = min(low[u], disc[v]);
  }
}
