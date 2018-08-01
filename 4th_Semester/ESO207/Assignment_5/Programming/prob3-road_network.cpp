#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

typedef struct Edge {
  int x;
  int y;
  int wt;
} edge;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pair<int, int>> vpi;
typedef vector<vpi> vvpi;
typedef vector<edge> ve;

#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define pb push_back
#define sz(a) int((a).size())
#define cl(a) a.clear()
#define rsz(a,n) a.resize(n)
#define mp(a,b) make_pair(a,b)
#define erase(vec,a) vec.erase(remove(vec.begin(), vec.end(), a), vec.end())

ve city;
ve roads;
vi parents;

void findCost(int);
bool compareEdges(edge, edge);
int find(int);
void combine(int,int);

int main()
{
  ios::sync_with_stdio(false);cin.tie(0);
  int n,m;
  int x,y,wt;
  cin >> n >> m;
  
  while(m--)
  {
    cin >> x >> y >> wt;
    edge e;
    e.x = x;
    e.y = y;
    e.wt = wt;
    city.pb(e);
  }

  sort(city.begin(), city.end(), compareEdges);
  findCost(n);
  return 0;
}

bool compareEdges(edge e1, edge e2)
{
  if(e1.wt < e2.wt)
    return true;
  return false;
}

int find(int x)
{
  if(parents[x] != x)
    parents[x] = find(parents[x]);
  return parents[x];
}

void combine(int x, int y)
{
  int xp = find(x);
  int yp = find(y);
  parents[xp] = yp;
}

void findCost(int V)
{
  int index = 0;
  rsz(parents, V);
  for(int i=0;i<V;i++)
    parents[i] = i;
  while(sz(roads) < V-1)
  {
    edge e = city[index];
    index++;
    int x = find(e.x);
    int y = find(e.y);

    if(x != y)
    {
      roads.pb(e);
      combine(x,y);
    }
  }

  int totalcost = 0;

  tr(roads, it)
  {
    totalcost += it->wt;
  }
  
  cout << totalcost << endl;
}
