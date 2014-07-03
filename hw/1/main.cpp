#include "Multiset.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Multiset ms;
    assert(ms.empty());
    string x = "dill";
    assert(ms.get(0, x) == 0  &&  x == "dill");  // x unchanged by get failure
    assert( ! ms.contains("tamarind"));
    ms.insert("tamarind");
    ms.insert("tamarind");
    assert(ms.size() == 2  &&  ms.uniqueSize() == 1);
    assert(ms.get(1, x) == 0  &&  x == "dill");  // x unchanged by get failure
    assert(ms.get(0, x) == 2  &&  x == "tamarind");
    cout << "Passed all tests" << endl;
}
