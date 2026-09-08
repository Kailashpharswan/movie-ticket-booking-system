# Step A - Requirement Analysis

## Functional Requirements

FR1 - Movie listing: on request, the system displays every movie currently playing (title, language, duration). If no movie exists, an empty list is shown and the program does not crash.

FR2 - Shows: given a chosen movie, the system lists all its shows as screen number and start time. If the movie has no shows, a message is shown and control returns to the menu without crashing.

FR3 - Seat layout: given a chosen show, the system displays every seat on that show's screen, grouped by type (SILVER/GOLD/PLATINUM), each marked [ ] AVAILABLE or [X] BOOKED. The layout reflects only that show's own seat statuses, never another show on the same screen.

FR4 - Booking: a customer selects one or more seat numbers for a show. If any selected seat is already BOOKED, the whole booking is rejected and no seat changes state. Booking is confirmed only after payment succeeds.

FR5 - Pricing: the total for a booking equals the sum of each selected seat's type price (SILVER Rs.150, GOLD Rs.250, PLATINUM Rs.400). Changing a price must require editing only the price table (Seat class), no other class.

FR6 - Payment: exactly one method (UPI / Card / Cash) per booking. If payment fails, seats are released and booking status becomes FAILED.

FR7 - Ticket: immediately after a successful payment, the system prints a ticket containing booking id, movie title, screen number, show start time, the booked seat numbers, and the total amount. No ticket is printed for a rejected or failed booking.

FR8 - Cancellation: given a valid, CONFIRMED booking id, the system sets that booking's status to CANCELLED and releases every one of its seats back to AVAILABLE. An invalid booking id, or one that is not CONFIRMED, shows an error and changes nothing.

## Non-Functional Requirements

NFR1 - Modularity: each class lives in exactly one file (13 class files + main). A change to one class's internals never requires editing another class's file.

NFR2 - Extensibility: adding a new payment method (e.g. NetBanking) must be possible by adding one new class that extends Payment, with zero edits to BookingService, Booking, or any existing Payment subclass.

NFR3 - Input validation: every menu choice, seat number, and numeric input is validated. Invalid input produces a clear message and returns to the menu instead of crashing or corrupting state.

NFR4 - Usability: seat layouts and tickets are printed in a fixed, readable text format so a non-technical console user can follow the flow without external documentation.