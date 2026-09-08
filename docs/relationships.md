# Step C - Relationships

For every pair, the lifetime test decides the relationship: if the whole is destroyed, does the part die too?

| Pair | Choice | Justification (lifetime test) |
|---|---|---|
| Cinema - Screen | Composition | A screen belongs to exactly one cinema in this design. Screens live inside Cinema's own vector and are destroyed with it - there is no scenario where a screen outlives its cinema. |
| Screen - Seat | Composition | A physical seat only exists as part of a specific screen. If the screen is torn down, seat A1 of that screen does not move elsewhere - it ceases to exist too. |
| Show - Movie | Aggregation | (Given as the worked example.) A Show borrows a Movie. Cancelling the 6 PM show does not delete "3 Idiots" - it still exists and still plays at 9 PM. |
| Show - Screen | Aggregation | A Show borrows a Screen for its duration. Ending that show does not delete Screen-1 - the same screen goes on hosting other shows. |
| Show - ShowSeat | Composition | A ShowSeat (this seat's status for this show) has no meaning once the show is gone. When the Show is destroyed, every one of its ShowSeats is destroyed with it. |
| Booking - Customer | Association | A Customer can exist without ever making a booking, and a Booking references a customer without owning them. Deleting a booking must never delete the customer record. |
| Booking - ShowSeat | Aggregation | A Booking references specific ShowSeats, but cancelling or deleting the booking does not delete the seat - it is released back to AVAILABLE and can be booked by someone else. |
| Booking - Payment | Composition | Each Payment object is created for, and belongs to, exactly one Booking; it is never reused by another booking and is destroyed with it (see Booking's destructor). |
| Payment - UpiPayment | Inheritance | UpiPayment IS-A Payment: it inherits the pay() contract and supplies its own implementation. The same applies to CardPayment and CashPayment. |
| BookingService - Booking | Composition (in this implementation) | BookingService creates every Booking, and in the code, its destructor deletes all of them - so by the lifetime test this pair is composition here. In a larger, persistent system, bookings would likely be stored in a database and would outlive any one in-memory service, making it association instead - a fair alternative answer. |

Note: every row above is backed by an explicit lifetime-test justification, not just "it feels like has-a."