// BookingService: the orchestrator — runs the booking flow end to end
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BookingService {
private:
    Cinema *cinema;
    vector<Booking*> bookings;

public:
    BookingService(Cinema *cinema) { this->cinema = cinema; }

    ~BookingService() {
        for (Booking *b : bookings) delete b;
    }

    Booking* bookSeats(Show *show, Customer *customer, vector<string> seatNumbers, Payment *payment) {
        vector<ShowSeat*> chosenSeats;

        for (string seatNo : seatNumbers) {
            ShowSeat *ss = show->getShowSeat(seatNo);
            if (ss == nullptr) {
                cout << "  ERROR: seat " << seatNo << " does not exist.\n";
                delete payment;
                return nullptr;
            }
            if (!ss->isAvailable()) {
                cout << "  ERROR: seat " << seatNo << " is already BOOKED.\n";
                delete payment;
                return nullptr;
            }
            chosenSeats.push_back(ss);
        }

        double total = PriceCalculator::calculateTotal(chosenSeats);
        Booking *booking = new Booking(show, customer, chosenSeats, total);
        booking->attachPayment(payment);

        bool paid = payment->pay(total);
        if (!paid) {
            booking->fail();
            bookings.push_back(booking);
            cout << "  Payment failed. Booking " << booking->getBookingId() << " NOT confirmed.\n";
            return booking;
        }

        for (ShowSeat *s : chosenSeats) s->book();
        booking->confirm();
        bookings.push_back(booking);

        TicketPrinter::printTicket(*booking);
        return booking;
    }

    bool cancelBooking(string bookingId) {
        for (Booking *b : bookings) {
            if (b->getBookingId() == bookingId) {
                if (b->getStatus() != BookingStatus::CONFIRMED) {
                    cout << "  ERROR: only a CONFIRMED booking can be cancelled.\n";
                    return false;
                }
                b->cancel();
                cout << "  Booking " << bookingId << " cancelled. Seats released.\n";
                return true;
            }
        }
        cout << "  ERROR: no booking found with id " << bookingId << ".\n";
        return false;
    }

    vector<Booking*>& getBookings() { return bookings; }
};