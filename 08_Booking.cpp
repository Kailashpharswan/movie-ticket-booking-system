// Booking: booking id, which show, which seats, total amount, status
#include <string>
#include <vector>
#include <sstream>
using namespace std;

enum class BookingStatus { PENDING, CONFIRMED, CANCELLED, FAILED };

class Booking {
private:
    string bookingId;
    Show *show;
    Customer *customer;
    vector<ShowSeat*> seats;
    Payment *payment;
    double totalAmount;
    BookingStatus status;

    static int nextBookingId;   // static member -> unique IDs

public:
    Booking(Show *show, Customer *customer, vector<ShowSeat*> seats, double totalAmount) {
        this->show = show;
        this->customer = customer;
        this->seats = seats;
        this->totalAmount = totalAmount;
        this->payment = nullptr;
        this->status = BookingStatus::PENDING;
        this->bookingId = generateId();
    }

    ~Booking() {
        delete payment;
    }

    string getBookingId() { return bookingId; }
    Show* getShow() { return show; }
    Customer* getCustomer() { return customer; }
    vector<ShowSeat*>& getSeats() { return seats; }
    double getTotalAmount() { return totalAmount; }
    BookingStatus getStatus() { return status; }

    void attachPayment(Payment *payment) { this->payment = payment; }
    void confirm() { status = BookingStatus::CONFIRMED; }
    void fail() { status = BookingStatus::FAILED; }

    // F8: cancel — seats become AVAILABLE again
    void cancel() {
        for (ShowSeat *s : seats) s->release();
        status = BookingStatus::CANCELLED;
    }

private:
    static string generateId() {
        nextBookingId++;
        ostringstream oss;
        oss << "BK" << (1000 + nextBookingId);
        return oss.str();
    }
};

int Booking::nextBookingId = 0;