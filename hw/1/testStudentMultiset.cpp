#include <iostream>
#include "StudentMultiset.h"

using namespace std;

int main()
{
    unsigned long id1 = 4304349203;
    unsigned long id2 = 4820283022;
    StudentMultiset hw_1_submissions;
    hw_1_submissions.print();
    cout << hw_1_submissions.size() << endl;
    hw_1_submissions.add(id1);
    cout << hw_1_submissions.size() << endl;
    hw_1_submissions.add(id2);
    cout << hw_1_submissions.size() << endl;
    hw_1_submissions.print();
    hw_1_submissions.add(id1);
    cout << hw_1_submissions.size() << endl;
    hw_1_submissions.print();
    return 0;
}
