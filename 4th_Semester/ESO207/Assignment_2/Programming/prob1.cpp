#include <iostream>
using namespace std;

#define MAX 1000

template <typename T>
class Stack {
    int top;
    T a[int(MAX/2)];
  public:
    Stack() { top = -1; }
    void push(T x);
    T pop();
    bool isEmpty();
    T topOfStack();
};

template <typename T>
void Stack<T>::push(T x)
{
  if (top >= int(MAX/2))
    printf("Stack Overflow!");
  else
    a[++top] = x;
}

template <typename T>
bool Stack<T>::isEmpty()
{
  return (top < 0);
}

template <typename T>
T Stack<T>::pop()
{
  if(top < 0)
    printf("Stack Underflow!");
  else
  {
    T x = a[top--];
    return x;
  }
}

template <typename T>
T Stack<T>::topOfStack()
{
  if(top < 0)
    printf("Stack Underflow!");
  else
  {
    T x = a[top];
    return x;
  }
}

int compute(int v1, char op, int v2)
{
  switch(op)
  {
    case '+':
      return v1+v2;
    case '-':
      return v1-v2;
    case '*':
      return v1*v2;
    case '/':
      return int(v1/v2);
  }
}

int main()
{
  int t,x,y,i;
  char ch;
  scanf("%d",&t);
  while(t--)
  {
    i=0;
    char arr[2*MAX];
    ch = getchar();
    ch = getchar();
    int num_flag = 0;
    while(ch != '\n')
    {
      if(ch == ' ')
      {
        num_flag = 0;
        ch = getchar();
        continue;
      }
      arr[i++] = ch;
      ch = getchar();
    }
    arr[i] = '\0';
    scanf("%d %d",&x,&y);

    Stack<int> opn;
    Stack<char> op;
    i=0;
    while(arr[i] != '\0')
    {
      if(arr[i]=='+' || arr[i]=='-' || arr[i]=='*' || arr[i]=='/')
      {
        if(op.isEmpty())
          op.push(arr[i]);
        else
        {
          while(!((arr[i]=='/' || arr[i]=='*') && (op.topOfStack()=='+' || op.topOfStack()=='-')))
          {
            int val2 = opn.pop();
            char tempop = op.pop();
            int val1 = opn.pop();
            opn.push(compute(val1,tempop,val2));
            if(op.isEmpty())
              break;
          }
          op.push(arr[i]);
        }
        i++;
        continue;
      }
      int num=0;
      while((arr[i]<='9' && arr[i]>='0') || arr[i]=='x' || arr[i]=='y')
      {
        if(arr[i]<='9' && arr[i]>='0')
          num = (arr[i]-'0') + 10*num;
        else if(arr[i]=='x')
          num = num*x;
        else if(arr[i]=='y')
          num = num*y;
        i++;
      }
      opn.push(num);
    }
    while(!op.isEmpty())
    {
      int val2 = opn.pop();
      char tempop = op.pop();
      int val1 = opn.pop();
      opn.push(compute(val1,tempop,val2));
    }
    printf("%d\n",opn.pop());
  }
  return 0;
}
