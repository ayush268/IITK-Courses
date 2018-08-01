#include <iostream>
#include <string>
#include <typeinfo>
#include <bits/stdc++.h>
using namespace std;

set<int> s;

int main()
{
  char a = 'a';
  cout << char(a+1) << " "<< endl;
  a = char(a+1);
  string tmp(1, a);
  cout << tmp << endl;
  string b = "Hi-lo";
  cout << b[0] << " " << typeid(b).name() << endl;
  s.insert(2);
  s.insert(1);
  cout << *s.begin() << endl;
  return 0;
}
