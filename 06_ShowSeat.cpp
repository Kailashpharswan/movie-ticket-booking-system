// ShowSeat: the status of ONE seat FOR ONE show (AVAILABLE / BOOKED)
#include <string>
using namespace std;

enum class SeatStatus { AVAILABLE, BOOKED };

class ShowSeat {
private:
    Seat *seat;           // Aggregation — points to a Seat, doesn't own it
    SeatStatus status;

public:
    ShowSeat(Seat *seat) {
        this->seat = seat;
        this->status = SeatStatus::AVAILABLE;
    }

    string getSeatNumber() {
        return seat->getSeatNumber();
    }

    SeatType getSeatType() {
        return seat->getType();
    }

    double getPrice() {
        return seat->getPrice();
    }

    SeatStatus getStatus() {
        return status;
    }

    bool isAvailable() {
        return status == SeatStatus::AVAILABLE;
    }

    void book() {
        status = SeatStatus::BOOKED;
    }

    void release() {
        status = SeatStatus::AVAILABLE;
    }
};