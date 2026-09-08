// Customer: name and phone
#include <string>
using namespace std;

class Customer {
private:
    string name;
    string phone;

public:
    Customer(string name, string phone) {
        this->name = name;
        this->phone = phone;
    }

    string getName() { return name; }
    string getPhone() { return phone; }
};