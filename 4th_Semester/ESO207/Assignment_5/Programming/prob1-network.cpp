#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pair<bool, vi>> vbvi; 

#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define pb push_back
#define sz(a) int((a).size())
#define cl(a) a.clear()
#define rsz(a,n) a.resize(n)
#define mp(a,b) make_pair(a,b)
#define erase(vec,a) vec.erase(remove(vec.begin(), vec.end(), a), vec.end())

vbvi network;

int main()
{
  ios::sync_with_stdio(false);cin.tie(0);

  int n,nop,k;
  int x,y;
  string inst;
  cin >> n >> nop;
  cl(network);
  rsz(network, n);
  for(int i=0;i<n;i++)
  {
    vi a;
    network[i] = mp(false, a);
  }

  while(nop--)
  {
    cin >> inst;
    if(inst == "addnode")
    {
      cin >> x;
      network[x-1].first = true;
    }
    else if(inst == "delnode")
    {
      cin >> x;
      tr(network[x-1].second, it)
      {
        erase(network[*it].second, x-1);
      }
      cl(network[x-1].second);
      network[x-1].first = false;
    }
    else if(inst == "addlink")
    {
      cin >> x >> y;
      network[x-1].second.pb(y-1);
      network[y-1].second.pb(x-1);
    }
    else if(inst == "remlink")
    {
      cin >> x >> y;
      erase(network[x-1].second, y-1);
      erase(network[y-1].second, x-1);
    }
    else
    {
      cout << "Invalid Instruction" << endl;
      exit(1);
    }
  }

  cin >> k;
  while(k--)
  {
    cin >> x;
    if(network[x-1].first)
    {
      if(int(network[x-1].second.size()) != 0)
      {
        tr(network[x-1].second, it)
        {
          cout << *it+1 << " ";
        }
        cout << endl;
      }
      else
      {
        cout << "no connections" << endl;
      }
    }
    else
    {
      cout << "not in network" << endl;
    }
  }
  return 0;
}
