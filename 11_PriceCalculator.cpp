// PriceCalculator: turn a list of seats into a total amount
#include <vector>
using namespace std;

class PriceCalculator {
public:
    static double calculateTotal(vector<ShowSeat*> seats) {
        double total = 0.0;
        for (ShowSeat *s : seats) total += s->getPrice();
        return total;
    }
};