/*
 * main.cpp — Movie Ticket Booking System
 * TCS-504 System Design — Assignment 1
 *
 * BUILD:  g++ -std=c++17 -Wall main.cpp -o ticket_booking
 * RUN:    ./ticket_booking        (or .\ticket_booking.exe on Windows)
 *
 * Only compile main.cpp. It #includes every other .cpp file directly,
 * since header files aren't allowed. Never run g++ *.cpp — that would
 * compile each class twice and cause "multiple definition" errors.
 *
 * Include order follows DEPENDENCY, not file numbering: a class stored
 * BY VALUE inside another must be fully defined first.
 */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

#include "01_Movie.cpp"
#include "02_Seat.cpp"
#include "03_Screen.cpp"
#include "06_ShowSeat.cpp"      // before Show — Show holds vector<ShowSeat>
#include "05_Show.cpp"
#include "04_Cinema.cpp"        // after Show — Cinema stores Show*
#include "07_Customer.cpp"
#include "09_Payment.cpp"
#include "10_PaymentTypes.cpp"
#include "08_Booking.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
#include "13_BookingService.cpp"

// ---------------- input helpers ----------------
int readIntChoice() {
    int choice;
    while (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Please enter a number: ";
    }
    return choice;
}

vector<string> splitSeats(string line) {
    vector<string> result;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        size_t start = token.find_first_not_of(" \t");
        size_t end = token.find_last_not_of(" \t");
        if (start != string::npos) result.push_back(token.substr(start, end - start + 1));
    }
    return result;
}

// ---------------- demo data setup ----------------
void setupCinema(Cinema &cinema) {
    cinema.addScreen(Screen(1));
    cinema.addScreen(Screen(2));

    cinema.addMovie(Movie(1, "3 Idiots", "Hindi", 170));
    cinema.addMovie(Movie(2, "Interstellar", "English", 169));

    Show *show1 = new Show(1, &cinema.getMovies()[0], &cinema.getScreens()[0], "06:00 PM");
    Show *show2 = new Show(2, &cinema.getMovies()[0], &cinema.getScreens()[1], "09:00 PM");
    cinema.addShow(show1);
    cinema.addShow(show2);
}

void handleBrowseAndBook(Cinema &cinema, BookingService &service) {
    cinema.listMovies();
    cout << "Choose movie: ";
    int movieChoice = readIntChoice();
    if (movieChoice < 1 || movieChoice > (int)cinema.getMovies().size()) {
        cout << "  ERROR: invalid movie choice.\n";
        return;
    }
    Movie *movie = &cinema.getMovies()[movieChoice - 1];

    vector<Show*> matching;
    int idx = 1;
    for (Show *s : cinema.getShows()) {
        if (s->getMovie()->getTitle() == movie->getTitle()) {
            cout << "  [" << idx << "] Screen-" << s->getScreen()->getScreenNumber()
                 << "   " << s->getStartTime() << "\n";
            matching.push_back(s);
            idx++;
        }
    }
    if (matching.empty()) {
        cout << "  No shows scheduled for this movie.\n";
        return;
    }
    cout << "Choose show: ";
    int showChoice = readIntChoice();
    if (showChoice < 1 || showChoice > (int)matching.size()) {
        cout << "  ERROR: invalid show choice.\n";
        return;
    }
    Show *show = matching[showChoice - 1];

    show->printSeatLayout();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nSeats (e.g. A1,B2): ";
    string line;
    getline(cin, line);
    vector<string> seatNumbers = splitSeats(line);
    if (seatNumbers.empty()) {
        cout << "  ERROR: no seats entered.\n";
        return;
    }

    vector<ShowSeat*> preview;
    bool allValid = true;
    string badSeat;
    for (string sn : seatNumbers) {
        ShowSeat *ss = show->getShowSeat(sn);
        if (ss == nullptr || !ss->isAvailable()) { allValid = false; badSeat = sn; break; }
        preview.push_back(ss);
    }
    if (!allValid) {
        cout << "  ERROR: seat " << badSeat << " is invalid or already BOOKED.\n";
        return;
    }
    double total = PriceCalculator::calculateTotal(preview);
    for (ShowSeat *ss : preview) {
        cout << "  " << ss->getSeatNumber() << " " << seatTypeToString(ss->getSeatType())
             << " Rs." << ss->getPrice() << "\n";
    }
    cout << "  TOTAL          Rs." << total << "\n";

    cout << "\nPay by: 1.UPI  2.Card  3.Cash > ";
    int payChoice = readIntChoice();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Payment *payment = nullptr;
    if (payChoice == 1) {
        cout << "Enter UPI ID: ";
        string upiId; getline(cin, upiId);
        payment = new UpiPayment(upiId);
    } else if (payChoice == 2) {
        cout << "Enter 16-digit card number: ";
        string cardNo; getline(cin, cardNo);
        payment = new CardPayment(cardNo);
    } else if (payChoice == 3) {
        payment = new CashPayment();
    } else {
        cout << "  ERROR: invalid payment method.\n";
        return;
    }

    cout << "Customer name: ";
    string custName; getline(cin, custName);
    Customer customer(custName, "");

    service.bookSeats(show, &customer, seatNumbers, payment);
}

void handleCancel(BookingService &service) {
    cout << "Enter booking ID to cancel: ";
    string id; getline(cin, id);
    service.cancelBooking(id);
}

void handleMyTickets(BookingService &service) {
    if (service.getBookings().empty()) {
        cout << "  No bookings yet.\n";
        return;
    }
    for (Booking *b : service.getBookings()) {
        TicketPrinter::printTicket(*b);
    }
}

int main() {
    Cinema cinema("PVR Dehradun");
    setupCinema(cinema);
    BookingService service(&cinema);

    while (true) {
        cout << "\n===== MOVIE TICKET BOOKING =====\n";
        cout << "1. Movies  2. Book  3. Cancel  4. My tickets   0. Exit\n";
        cout << "Choose: ";
        int choice = readIntChoice();

        if (choice == 1) {
            cinema.listMovies();
        } else if (choice == 2) {
            handleBrowseAndBook(cinema, service);
        } else if (choice == 3) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            handleCancel(service);
        } else if (choice == 4) {
            handleMyTickets(service);
        } else if (choice == 0) {
            cout << "  Thank you for visiting " << cinema.getName() << "!\n";
            break;
        } else {
            cout << "  ERROR: invalid menu choice. Try again.\n";
        }
    }
    return 0;
}