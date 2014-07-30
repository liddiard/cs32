#include <iostream>
using namespace std;

void duplicates(inta[], int n, int m)
{
    bool * seen = new bool[m+1];
    for (int i = 0; i <= m; i ++) { seen = false; }
    for (int i = 0; i < n, i++)
    {
        if (seen[a[i]]) cout << a[i];
        else seen[a[i]] = true;
    }
    delete[] seen;
}
