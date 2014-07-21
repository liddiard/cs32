#include <string>
#include <iostream>
using namespace std;

class NoisyClass {
  private:
      string s;

  public:
      NoisyClass () {
          cout << "[C] Default constructor" << endl;
      }

      NoisyClass (string stuff) {
          s = stuff;
          cout << "[P] Parameterized constructor" << endl;
      }

      NoisyClass (const NoisyClass& other) {
          s = other.s;
          cout << "[~] Copy constructor" << endl;
      }

      ~NoisyClass () {
          cout << "[D] Destructor" << endl;
      }

      NoisyClass& operator= (const NoisyClass& other) {
          s = other.s;
          cout << "[=] Assignment" << endl;
          return *this;
      }
};

NoisyClass whatsAllThisNoise (NoisyClass* n) {
if (n != nullptr) {
NoisyClass copier("test");
return copier;
} else {
return NoisyClass();
}
}

int main () {
NoisyClass n;
whatsAllThisNoise(&n);
}
