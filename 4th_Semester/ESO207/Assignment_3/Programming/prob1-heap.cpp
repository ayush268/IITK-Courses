#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define pb push_back
#define po pop_back

template <typename T>
class minHeap {
  vector<T> data;
  int size;
  public:
    minHeap() { size = 0; }
    int parent(int i) {return (i-1)/2;}
    int child_1(int i) {return 2*i+1;}
    int child_2(int i) {return 2*i+2;}
    T getMin();
    T removeMin();
    void insert(T val);
    void Heapify(int x);
};

template <typename T>
T minHeap<T>::getMin()
{
  if(size == 0)
    printf("Heap underflow!");
  else
    return data[0];
}

template <typename T>
void minHeap<T>::Heapify(int x)
{
  int left = child_1(x);
  int right = child_2(x);
  int min_index = x;
  if(left<size && data[left]<data[min_index])
    min_index = left;
  if(right<size && data[right]<data[min_index])
    min_index = right;
  if(min_index != x)
  {
    T tmp = data[x];
    data[x] = data[min_index];
    data[min_index] = tmp;
    Heapify(min_index);
  }
}

template <typename T>
T minHeap<T>::removeMin()
{
  if(size == 0)
    printf("Heap underflow!");
  else
  {
    T x = data[0];
    data[0] = data[size-1];
    size--;
    data.po();
    Heapify(0);
    return x;
  }
}

template <typename T>
void minHeap<T>::insert(T val)
{
  data.pb(val);
  size++;
  int i = size-1;
  while(i!=0 && data[parent(i)]>data[i])
  {
    T tmp = data[i];
    data[i] = data[parent(i)];
    data[parent(i)] = tmp;
    i = parent(i);
  }
}

int main()
{
  ios::sync_with_stdio(false);cin.tie(0);
  int q;
  string str1,str2;
  cin >> q;
  minHeap<string> memory;
  while(q--)
  {
    cin >> str1;
    if(str1 == "learn")
    {
      cin >> str2;
      memory.insert(str2);
    }
    else if(str1 == "reportsmallest")
      cout << memory.getMin() << endl;
    else
      cout << memory.removeMin() << endl;
  }
  return 0;
}
