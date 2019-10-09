#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<pair<bool, vi>> vbvi; 

typedef set<int> si;
typedef vector<si> vsi;

#define ins insert
#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define pb push_back
#define sz(a) int((a).size())
#define cl(a) a.clear()
#define rsz(a,n) a.resize(n)
#define mp(a,b) make_pair(a,b)
#define erase(vec,a) vec.erase(remove(vec.begin(), vec.end(), a), vec.end())

vsi graph;
vsi rev_graph;
vsi scc_graph;
vi scc_label;
vb visited;
si scc;
stack<int> stck;

void findSCCs(int);
void first_dfs(int);
void second_dfs(int);
bool compareSets(si s1, si s2)
{
  int a = *s1.begin();
  int b = *s2.begin();
  return a < b;
}
void printSCCGraph();

int main()
{
  ios::sync_with_stdio(false);cin.tie(0);
  int n,x;
  cin >> n;
  rsz(graph, n);
  rsz(rev_graph, n);
  for(int i=0;i<n;i++)
  {
    cin >> x;
    while(x != -1)
    {
      graph[i].ins(x);
      rev_graph[x].ins(i);
      cin >> x;
    }
  }

  rsz(scc_label, n);
  findSCCs(n);

  printSCCGraph();
  return 0;
}

void first_dfs(int u)
{
  visited[u] = true;
  tr(graph[u], it)
  {
    if(visited[*it] == false)
      first_dfs(*it);
  }
  stck.push(u);
}

void second_dfs(int u)
{
  visited[u] = true;
  scc.ins(u);

  tr(rev_graph[u], it)
  {
    if(visited[*it] == false)
      second_dfs(*it);
  }
}

void findSCCs(int n)
{
  rsz(visited, n);
  for(int i=0;i<n;i++)
    visited[i] = false;

  for(int i=0;i<n;i++)
  {
    if(visited[i] == false)
      first_dfs(i);
  }

  for(int i=0;i<n;i++)
    visited[i] = false;

  while(stck.empty() == false)
  {
    int u = stck.top();
    stck.pop();

    if(visited[u] == false)
    {
      scc.clear();
      second_dfs(u);
      scc_graph.pb(scc);
    }
  }

  sort(scc_graph.begin(), scc_graph.end(), compareSets);

  for(int i=0;i<sz(scc_graph);i++)
    tr(scc_graph[i], it)
      scc_label[*it] = i;
}

void printSCCGraph()
{
  cl(rev_graph);
  rsz(rev_graph, sz(scc_graph));
  for(int i=0;i<sz(scc_graph);i++)
  {
    tr(scc_graph[i], it)
    {
      tr(graph[*it], iit)
      {
        if(scc_label[*iit] != i)
          rev_graph[i].ins(scc_label[*iit]);
      }
    }
  }

  cout << sz(rev_graph) << endl;

  for(int i=0;i<sz(rev_graph);i++)
  {
    tr(rev_graph[i], it)
      cout << *it << " ";
    cout << "-1" << endl;
  }
}
