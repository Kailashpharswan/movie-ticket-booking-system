\# Movie Ticket Booking System — TCS-504 Assignment 1



A menu-driven C++ console program for booking movie tickets at a single

cinema — built for the System Design (TCS-504) course, B.Tech CSE Sem 5.



\## Build \& run



Only compile `main.cpp` — it `#include`s every other class file directly

(no header files are used, per the assignment's rules), so all 13 class

files are compiled exactly once, as part of this one command:





On Windows (PowerShell), the run command is:.\\ticket\_booking.exe





\*\*Do not\*\* run `g++ \*.cpp` — that would compile each class file twice

(once directly, once via the `#include` in main.cpp) and cause

"multiple definition" linker errors.



\## File list



| File | Class |

|---|---|

| `01\_Movie.cpp` | Movie |

| `02\_Seat.cpp` | Seat, SeatType |

| `03\_Screen.cpp` | Screen |

| `04\_Cinema.cpp` | Cinema |

| `05\_Show.cpp` | Show |

| `06\_ShowSeat.cpp` | ShowSeat, SeatStatus |

| `07\_Customer.cpp` | Customer |

| `08\_Booking.cpp` | Booking, BookingStatus |

| `09\_Payment.cpp` | Payment (abstract) |

| `10\_PaymentTypes.cpp` | UpiPayment, CardPayment, CashPayment |

| `11\_PriceCalculator.cpp` | PriceCalculator |

| `12\_TicketPrinter.cpp` | TicketPrinter |

| `13\_BookingService.cpp` | BookingService |

| `main.cpp` | console menu, cinema setup |



File numbers follow the assignment's suggested naming, but `main.cpp`

`#include`s them in \*\*compile-dependency order\*\*, not numeric order —

e.g. `ShowSeat` before `Show`, and `Show` before `Cinema`, since a class

stored \*by value\* inside another must be fully defined first. This is

explained in a comment at the top of `main.cpp`.



\## Features implemented (F1–F8)



\- F1 — list all movies currently playing

\- F2 — for a chosen movie, list its shows (screen + start time)

\- F3 — seat layout with AVAILABLE / BOOKED status

\- F4 — book one or more seats (reject an already-booked seat)

\- F5 — price by seat type (SILVER ₹150, GOLD ₹250, PLATINUM ₹400)

\- F6 — pay by UPI / Card / Cash — a failed payment does not confirm the booking

\- F7 — print a ticket (booking id, movie, screen, time, seats, amount)

\- F8 — cancel a booking — seats become AVAILABLE again



\## Edge cases demonstrated



1\. Booking an already-BOOKED seat → rejected, nothing changes

2\. A failed payment (e.g. invalid card number) → booking NOT confirmed, seats released

3\. Cancelling a booking → its seats show AVAILABLE again

4\. An invalid seat number or menu choice → clear message, no crash



\## OOP concepts and where they live



| Concept | Where |

|---|---|

| Encapsulation | `ShowSeat.status`, `Booking.status` are private; changed only via `book()`/`release()`/`confirm()`/`cancel()` |

| Abstraction | `Payment` — callers only ever see `pay(amount)`, never the concrete class |

| Inheritance | `UpiPayment`, `CardPayment`, `CashPayment` extend `Payment` |

| Runtime polymorphism | `BookingService::bookSeats()` calls `payment->pay(total)` through a `Payment\*` |

| Static members | `Booking::nextBookingId` generates unique booking IDs |

| `this` keyword | used in every constructor |

| Composition | `Cinema \*-- Screen`, `Screen \*-- Seat`, `Show \*-- ShowSeat` |

| Aggregation | `Show o-- Movie`, `Show o-- Screen`, `ShowSeat o-- Seat` |

| Association | `Booking -- Customer`, `BookingService -- Booking` |



\## Documentation



See `docs/` for the requirement analysis, noun-verb table, relationship

table, class diagram, and sequence diagram (Steps A–E, G of the assignment).

