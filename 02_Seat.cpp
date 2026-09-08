// Seat: one physical seat — its number and type (SILVER/GOLD/PLATINUM)
#include <string>
using namespace std;

enum class SeatType { SILVER, GOLD, PLATINUM };
string seatTypeToString(SeatType type) {
    switch (type) {
        case SeatType::SILVER:   return "SILVER";
        case SeatType::GOLD:     return "GOLD";
        case SeatType::PLATINUM: return "PLATINUM";
    }
    return "UNKNOWN";
}

// Constants instead of magic numbers
const double SILVER_PRICE   = 150.0;
const double GOLD_PRICE     = 250.0;
const double PLATINUM_PRICE = 400.0;

class Seat {
private:
    string seatNumber;   // e.g. "A1"
    SeatType type;

public:
    Seat(string seatNumber, SeatType type) {
        this->seatNumber = seatNumber;
        this->type = type;
    }

    string getSeatNumber() {
        return seatNumber;
    }

    SeatType getType() {
        return type;
    }

    double getPrice() {
        switch (type) {
            case SeatType::SILVER:   return SILVER_PRICE;
            case SeatType::GOLD:     return GOLD_PRICE;
            case SeatType::PLATINUM: return PLATINUM_PRICE;
        }
        return 0.0;
    }
};