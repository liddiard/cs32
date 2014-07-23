#include <iostream>
using namespace std;

long choose(long n, long k)
{
    if (k == 0 || n == k) return 1;
    else return choose(n-1, k) + choose(n-1, k-1);
}

int main()
{
    cout << choose(6,2);
}
