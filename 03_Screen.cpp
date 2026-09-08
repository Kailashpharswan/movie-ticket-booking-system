// Screen: one auditorium — a screen number that OWNS its seats
#include <string>
#include <vector>
using namespace std;

class Screen {
private:
    int screenNumber;
    vector<Seat> seats;   // Composition — seats live and die with the screen

public:
    Screen(int screenNumber) {
        this->screenNumber = screenNumber;

        // Build a fixed layout: 4 SILVER, 3 GOLD, 2 PLATINUM
        seats.push_back(Seat("A1", SeatType::SILVER));
        seats.push_back(Seat("A2", SeatType::SILVER));
        seats.push_back(Seat("A3", SeatType::SILVER));
        seats.push_back(Seat("A4", SeatType::SILVER));
        seats.push_back(Seat("B1", SeatType::GOLD));
        seats.push_back(Seat("B2", SeatType::GOLD));
        seats.push_back(Seat("B3", SeatType::GOLD));
        seats.push_back(Seat("C1", SeatType::PLATINUM));
        seats.push_back(Seat("C2", SeatType::PLATINUM));
    }

    int getScreenNumber() {
        return screenNumber;
    }

    vector<Seat>& getSeats() {
        return seats;
    }
};