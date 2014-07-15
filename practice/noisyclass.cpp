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

// Start with a warmup...
struct SoMeta {
    NoisyClass n[2];
    NoisyClass* ptr[2];
};

int main () {
    SoMeta s;
    SoMeta* ptr;
    SoMeta* dynamicYo = new SoMeta();
    delete dynamicYo;
}
