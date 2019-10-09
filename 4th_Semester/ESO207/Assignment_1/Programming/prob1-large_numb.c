#include <stdio.h>

typedef __uint8_t u8i;

int max(int a, int b)
{
  return a>b?a:b;
}

void stringtoint(char str[], u8i arr[], int n)
{
  int i = 0;
  while(str[i] != '\0')
  {
    arr[n-(i+1)] = str[i] - '0';
    i++;
  }
}

void printans(u8i ans[], int n)
{
  int i = n-1;
  while(ans[i]==0 && i >= 0)
    i--;
  if(i<0)
  {
    printf("0\n");
    return;
  }
  while(i >= 0)
  {
    printf("%d", ans[i]);
    i--;
  }
  printf("\n");
}

void add(u8i arr1[], int n1, u8i arr2[], int n2, u8i ans[])
{
  u8i sum, carry = 0;
  int i = 0;
  while(i < max(n1,n2))
  {
    if(i < n1 && i < n2)
      sum = arr1[i] + arr2[i] + carry;
    else if(i < n1)
      sum = arr1[i] + carry;
    else if(i < n2)
      sum = arr2[i] + carry;
    ans[i] = sum % 10;
    carry = sum / 10;
    i++;
  }
  ans[i] = carry;
}

void sub(u8i arr1[], int n1, u8i arr2[], int n2, u8i ans[])
{
  u8i arr1_val,borrow = 0;
  int i = 0;
  while(i < n2)
  {
    arr1_val = arr1[i];
    if(borrow && arr1[i] == 0)
    {
      ans[i] = 9 - arr2[i];
      i++;
      continue;
    }
    if(borrow)
    {
      arr1_val = arr1[i] - 1;
      borrow = 0;
    }
    if(arr1_val < arr2[i])
    {
      ans[i] = 10 + arr1_val - arr2[i];
      borrow = 1;
    }
    else
      ans[i] = arr1_val - arr2[i];
    i++;
  }
  while(i < n1)
  {
    if(borrow && arr1[i] == 0)
    {
      ans[i] = 9;
      i++;
      continue;
    }
    if(borrow)
    {
      ans[i] = arr1[i] - 1;
      borrow = 0;
    }
    else
      ans[i] = arr1[i];
    i++;
  }
}

void unitmult(u8i arr[], int n, u8i unit, u8i ans[], int offset)
{
  u8i mul, carry = 0;
  int i = 0;
  while(i < n)
  {
    mul = arr[i]*unit + carry;
    ans[i+offset] = mul % 10;
    carry = mul / 10;
    i++;
  }
  ans[i+offset] = carry;
}

void mult(u8i arr1[], int n1, u8i arr2[], int n2, u8i ans[])
{
  u8i unit;
  int tmp2 = n2;
  while(tmp2 > 0)
  {
    unit = arr2[n2 - tmp2];
    u8i temp[n1+(n2-tmp2)+1];
    for(int j = n2-tmp2; j > 0; j--)
      temp[j-1] = 0;
    unitmult(arr1, n1, unit, temp, n2-tmp2);
    add(temp,n1+(n2-tmp2)+1,ans,n1+(n2-tmp2)+1,ans);
    tmp2--;
  }
}

void reverse(u8i arr[], int n)
{
  for(int i=0; i<n/2; i++)
  {
    int tmp = arr[i];
    arr[i] = arr[n-i];
    arr[n-i] = tmp;
  }
}

int compare(u8i dvd[], u8i dvr[], int n)
{
  int i = n-1;
  while(dvd[i] == dvr[i])
    i--;
  if(i < 0 || dvd[i] >= dvr[i])
    return 1;
  return -1;
}

void div(u8i arr1[], int n1, u8i arr2[], int n2, u8i ans[])
{
  u8i dvd[n1];
  u8i dvr[n1];
  for(int i=0;i<n1;i++)
    dvd[i]=arr1[i];
  for(int i=0;i<n1-n2;i++)
    dvr[i]=0;
  for(int i=0;i<n2;i++)
    dvr[i+(n1-n2)]=arr2[i];
  for(int i=n1-n2;i>=0;i--)
  {
    if(compare(dvd,dvr,n1) == -1)
      ans[i] = 0;
    else
    {
      int count = 0;
      while(compare(dvd,dvr,n1) != -1)
      {
        ++count;
        sub(dvd,n1,dvr,n1,dvd);
      }
      ans[i]=count;
    }
    if(i != 0)
    {
      int tmp = dvr[0];
      for(int j=0;j<n1-1;j++)
      {
        dvr[j] = dvr[(j+1)%n1];
      }
      dvr[n1-1] = tmp;
    }
  }
}

int main()
{
  int t, n1, n2, opcode;
  char str[1001];
  scanf("%d",&t);
  while(t--)
  {
    scanf("%d %d", &n1, &n2);
    u8i arr1[n1], arr2[n2];
    scanf("%s", str);
    stringtoint(str, arr1, n1);
    scanf("%s", str);
    stringtoint(str, arr2, n2);
    scanf("%d", &opcode);
    if(opcode == 1)
    {
      u8i ans[max(n1,n2)+1];
      add(arr1,n1,arr2,n2,ans);
      printans(ans, max(n1,n2)+1);
    }
    else if(opcode == 2)
    {
      u8i ans[n1];
      sub(arr1,n1,arr2,n2,ans);
      printans(ans, n1);
    }
    else if(opcode == 3)
    {
      u8i ans[n1+n2+1];
      for(int j = 0; j < n1+n2+1; j++)
        ans[j] = 0;
      if(n1 >= n2)
        mult(arr1,n1,arr2,n2,ans);
      else
        mult(arr2,n2,arr1,n1,ans);
      printans(ans, n1+n2+1);
    }
    else if(opcode == 4)
    {
      if(n1 < n2)
        printf("0\n");
      else
      {
        u8i ans[n1-(n2-1)];
        div(arr1,n1,arr2,n2,ans);
        printans(ans, n1-(n2-1));
      }
    }
  }
  return 0;
}
