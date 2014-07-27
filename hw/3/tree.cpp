#include <iostream>
using namespace std;

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    's' 'k' 'c' 'e' 'k' 'c' 'b'
// then for this value of a2            the function must return
//    's' 'e' 'c'                               1
//    's' 'c' 'b'                                 2
//    'e' 's' 'c'                               0
//    'k' 'c' 'b'                                 3
int countIncludes(const char a1[], int n1, const char a2[], int n2)
{
    if (n2 <= 0) return 1; // empty sequnce/match
    if (n1 <= 0) return 0; // end of source array
    if (n2 > n1) return 0; // subset is larger than source 
    if (a1[0] == a2[0]) // match between 1st element in both arrays
        return countIncludes(a1+1, n1-1, a2, n2) + countIncludes(a1+1, n1-1, a2+1, n2-1); // try next element in source vs current in subset and next element in both
    else return countIncludes(a1+1, n1-1, a2, n2); // no match, advance source array
}

int main()
{
    char a1[] = {'s', 'k', 'c', 'e', 'k', 'c', 'b'};
    char a2[] = {'k', 'c', 'b'};
    cout << countIncludes(a1, 7, a2, 3);
}
