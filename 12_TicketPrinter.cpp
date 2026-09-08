// TicketPrinter: format and print a ticket — printing only
#include <iostream>
#include <string>
using namespace std;

class TicketPrinter {
public:
    static void printTicket(Booking &booking) {
        cout << "\n  ================ TICKET ================\n";
        cout << "  Booking ID : " << booking.getBookingId() << "\n";
        cout << "  Movie      : " << booking.getShow()->getMovie()->getTitle() << "\n";
        cout << "  Screen     : Screen-" << booking.getShow()->getScreen()->getScreenNumber()
             << "   " << booking.getShow()->getStartTime() << "\n";
        cout << "  Seats      : ";
        for (size_t i = 0; i < booking.getSeats().size(); i++) {
            cout << booking.getSeats()[i]->getSeatNumber();
            if (i + 1 < booking.getSeats().size()) cout << ", ";
        }
        cout << "\n";
        cout << "  Amount     : Rs." << booking.getTotalAmount()
             << "\tStatus: " << statusToString(booking.getStatus()) << "\n";
        cout << "  =========================================\n";
    }

private:
    static string statusToString(BookingStatus status) {
        switch (status) {
            case BookingStatus::PENDING:   return "PENDING";
            case BookingStatus::CONFIRMED: return "CONFIRMED";
            case BookingStatus::CANCELLED: return "CANCELLED";
            case BookingStatus::FAILED:    return "FAILED";
        }
        return "UNKNOWN";
    }
};