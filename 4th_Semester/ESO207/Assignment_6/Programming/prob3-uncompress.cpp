#include <bits/stdc++.h>
#include <string>

using namespace std;

typedef vector<int> vi;

typedef map<int, string> mis;
typedef vector<string> vs;

#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define pb push_back
#define sz(a) int((a).size())
#define cl(a) a.clear()
#define rsz(a,n) a.resize(n)
#define mp(a,b) make_pair(a,b)
#define erase(vec,a) vec.erase(remove(vec.begin(), vec.end(), a), vec.end())

mis dict;
vi codes;
int size;

void initialize();
void decompress();

int main()
{
  ios::sync_with_stdio(false);cin.tie(0);
  
  int code;
  cin >> code;
  while(code != -1)
  {
    codes.pb(code);
    cin >> code;
  }

  decompress();
  return 0;
}

void ini()
{
  dict.clear();
  char a = 'A';
  char b = 'a';
  char c;
  for(int i = 0; i < 26; i++)
  {
     c = char(a+i);
     string tmp1(1, c);
     dict[i] = tmp1;
     c = char(b+i);
     string tmp2(1, c);
     dict[26+i] = tmp2;
  }

  a = '0';
  for(int i=0; i < 10; i++)
  {
    c = char(a+i);
    string tmp(1, c);
    dict[52+i] = tmp;
  }

  dict[62] = " ";
  dict[63] = "CLEAR";
  size = 64;
}

void decompress()
{
  vs message;

  ini();

  int curr;
  string s, c;
  int i = 0;

  curr = codes[i];
  i++;
  if(dict.find(curr) == dict.end())
  {
    cout << "Archive is corrupted!" << endl;
    return;
  }
  s = dict[curr];
  message.pb(s);
  
  while(i < sz(codes))
  {
    curr = codes[i];

    if(curr == 63)
    {
      ini();
      i++;
      curr = codes[i];
      i++;
      s = dict[curr];
      message.pb(s);
      continue;
    }
    
    //if(dict.find(curr) != dict.end())
    if(curr<size)
    {
      c = s;
      s = dict[curr];
      string tmp(1, s[0]);
      dict[size] = c + tmp;
      size++;
    }
    
    else
    {
      if(size == curr)
      {
        string tmp(1, s[0]);
        dict[size] = s + tmp;
        size++;
        s = dict[curr];
      }
      else
      {
        cout << "Archive is corrupted!" << endl;
        return;
      }
    }

    message.pb(s);
    i++;
  }

  for(int i = 0; i < sz(message); i++)
  {
    cout << message[i];
  }
  cout << endl;
}
