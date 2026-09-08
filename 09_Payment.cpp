// Payment (abstract): the payment contract — pay(amount) — pure virtual
#include <string>
using namespace std;

class Payment {
public:
    virtual bool pay(double amount) = 0;      // pure virtual -> abstract class
    virtual string getMethodName() = 0;
    virtual ~Payment() {}                      // virtual destructor
};