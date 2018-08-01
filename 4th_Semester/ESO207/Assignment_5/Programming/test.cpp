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
typedef vector<pair<int, unsigned int>> vpi;

typedef set<int> si;
typedef map<int, si> misi;

#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define pb push_back
#define sz(a) int((a).size())
#define cl(a) a.clear()
#define rsz(a,n) a.resize(n)
#define mp(a,b) make_pair(a,b)
#define erase(vec,a) vec.erase(remove(vec.begin(), vec.end(), a), vec.end())

int main()
{
  vi a;
  a.pb(3);
  a.pb(2);
  a.pb(4);
  a.pb(1);
  tr(a, it)
  {
    cout << *it << endl;
    cout << sz(a) << endl;
  }

  erase(a, 2);
  cout << "--------------------------" << endl;

  tr(a, it)
  {
    cout << *it << endl;
    cout << sz(a) << endl;
  }

  cout << "--------------------------" << endl;

  vpi b;
  b.pb(mp(1,2));
  
  edge e;
  e.x = 1;
  e.y = 2;
  e.wt = 3;

  cout << e.x << " " << e.y << " " << e.wt << endl;
  tr(b, it)
  {
    cout << it->first << endl;
  }
//  cout << a.size() << endl;
//  cout << INT_MAX << endl;
  return 0;
}
