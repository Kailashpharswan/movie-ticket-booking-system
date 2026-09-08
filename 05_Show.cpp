// Show: one screening = a Movie on a Screen at a time; owns its ShowSeats
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Show {
private:
    int showId;
    Movie *movie;                 // Aggregation — borrows a Movie, doesn't own it
    Screen *screen;                // Aggregation — borrows a Screen, doesn't own it
    string startTime;
    vector<ShowSeat> showSeats;    // Composition — ShowSeats die with the Show

public:
    Show(int showId, Movie *movie, Screen *screen, string startTime) {
        this->showId = showId;
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;

        // Build one ShowSeat per physical seat on the screen — all AVAILABLE
        for (Seat &s : screen->getSeats()) {
            showSeats.push_back(ShowSeat(&s));
        }
    }

    int getShowId() {
        return showId;
    }

    Movie* getMovie() {
        return movie;
    }

    Screen* getScreen() {
        return screen;
    }

    string getStartTime() {
        return startTime;
    }

    vector<ShowSeat>& getShowSeats() {
        return showSeats;
    }

    // F3: display the seat layout with AVAILABLE / BOOKED status
    void printSeatLayout() {
        cout << "\n  SCREEN-" << screen->getScreenNumber() << "  " << startTime
             << "  |  " << movie->getTitle() << "\n";
        printRow(SeatType::SILVER, "SILVER  ");
        printRow(SeatType::GOLD, "GOLD    ");
        printRow(SeatType::PLATINUM, "PLATINUM");
        cout << "  ( [ ] = available   [X] = booked )\n";
    }

    // Returns nullptr instead of crashing if the seat number doesn't exist
    ShowSeat* getShowSeat(string seatNumber) {
        for (ShowSeat &ss : showSeats) {
            if (ss.getSeatNumber() == seatNumber) return &ss;
        }
        return nullptr;
    }

private:
    void printRow(SeatType type, string label) {
        cout << "  " << label << " ";
        for (ShowSeat &ss : showSeats) {
            if (ss.getSeatType() == type) {
                cout << ss.getSeatNumber() << (ss.isAvailable() ? "[ ] " : "[X] ");
            }
        }
        cout << "\n";
    }
};