#include <iostream>
#include <ctype.h>
using namespace std;

// Return true if any of the chars in the array is lowercase, false
// otherwise.
bool anyLowercase(const char a[], int n)
{
    if (n <= 0) return false;
    if (islower(a[0])) return true;
    return anyLowercase(a+1, n-1);
}

// Return the number of lowercase chars in the array.
int countLowercase(const char a[], int n)
{
    if (n <=0) return 0;
    int total = countLowercase(a+1, n-1);
    if (islower(a[0]))
        ++total;
    return total;
}

// Return the subscript of the first lowercase char in the array.
// If no element is lowercase, return -1.
int firstLowercase(const char a[], int n)
{
    if (n <=0) return -1;
    if (islower(a[0])) return 0;
    int cur = firstLowercase(a+1, n-1);
    if (cur == -1)
        return -1;
    return ++cur;
}

// Return the subscript of the least char in the array (i.e.,
// the smallest subscript m such that there is no k for which
// a[k] < a[m].)  If the array has no elements to examine, return -1.
int indexOfLeast(const char a[], int n)
{
    if (n <= 0) return -1;
    if (n == 1) return 0;
    int min = indexOfLeast(a, n-1);
    if (a[min] <= a[n-1])
        return min;
    else return n-1;
    return min;
}

int main()
{
    char letters[] = {'A', 'B', 'c', 'd', 'E'};
    cout << anyLowercase(letters, 5) << endl;
    cout << countLowercase(letters, 5) << endl;
    cout << firstLowercase(letters, 5) << endl;
    cout << indexOfLeast(letters, 5) << endl;
}
