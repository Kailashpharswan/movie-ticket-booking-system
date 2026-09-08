// UpiPayment, CardPayment, CashPayment — inherit from Payment
#include <string>
#include <iostream>
using namespace std;

class UpiPayment : public Payment {
private:
    string upiId;
public:
    UpiPayment(string upiId) { this->upiId = upiId; }

    bool pay(double amount) override {
        if (upiId.find('@') == string::npos) {
            cout << "  [UPI] Payment FAILED — invalid UPI ID\n";
            return false;
        }
        cout << "  [UPI] Rs." << amount << " paid successfully\n";
        return true;
    }

    string getMethodName() override { return "UPI"; }
};

class CardPayment : public Payment {
private:
    string cardNumber;
public:
    CardPayment(string cardNumber) { this->cardNumber = cardNumber; }

    bool pay(double amount) override {
        if (cardNumber.size() != 16) {
            cout << "  [CARD] Payment FAILED — invalid card number\n";
            return false;
        }
        cout << "  [CARD] Rs." << amount << " paid successfully\n";
        return true;
    }

    string getMethodName() override { return "CARD"; }
};

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "  [CASH] Rs." << amount << " received successfully\n";
        return true;
    }

    string getMethodName() override { return "CASH"; }
};