#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pair<int, unsigned int>> vpi;
typedef vector<vpi> vvpi;

#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define pb push_back
#define sz(a) int((a).size())
#define cl(a) a.clear()
#define rsz(a,n) a.resize(n)
#define mp(a,b) make_pair(a,b)
#define erase(vec,a) vec.erase(remove(vec.begin(), vec.end(), a), vec.end())

vvpi city;

void findPath(int, int);
int min_dist(int [], vi);
int mini(int, int);

int main()
{
  int n,m;
  int x,y,wt;
  cin >> n >> m;
  rsz(city,n);
  
  while(m--)
  {
    cin >> x >> y >> wt;
    city[x].pb(mp(y,wt));
    city[y].pb(mp(x,wt));
  }

//  for(int i=0;i<n;i++)
//  {
//    tr(city[i], it)
//    {
//      cout << i << " " << it->first << " " << it->second << endl;
//    }
//  }

  findPath(0, n);
  return 0;
}

int mini(int a, int b)
{
  if(a>b)
    return b;
  return a;
}

int min_dist(int dist[], vi n_done)
{
  int min = INT_MAX;
  int vertex;
  tr(n_done, it)
  {
    if(dist[*it] < min)
    {
      min = dist[*it];
      vertex = *it;
    }
  }
  return vertex;
}

void findPath(int src, int V)
{
  int u = src;
  int dist[V];
  vi n_done;
  for(int i=0; i<V; i++)
  {
    dist[i] = INT_MAX - 1;
    n_done.pb(i);
  }
  dist[u] = 0;

  while(!n_done.empty())
  {
    u = min_dist(dist, n_done);
    erase(n_done, u);
    tr(city[u], it)
    {
      int v = it->first;
      int new_dist = mini(dist[v], dist[u] + it->second);
      if(new_dist < dist[v])
        dist[v] = new_dist;
    }
  }

  if(dist[V-1] == INT_MAX-1)
    cout << -1 << endl;
  else
    cout << dist[V-1] << endl;
}
