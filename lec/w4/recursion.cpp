#include <iostream>
using namespace std;

long fib(long n)
{
    if (n <= 2) return 1; // base case
    else return fib(n-1) + fib(n-2);
}

bool odd(int n)
{
    if (n == 1) return true;
    else if (n == 2) return false;
    else return even(n-1);
}

bool even(int n)
{
    if (n == 1) return false;
    else if (n == 2) return true;
    else return odd(n-1);
}

int main()
{
    int num;
    cin >> num;
    cout << fib(num);
}
