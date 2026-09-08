# Step B - Noun-Verb Analysis

## Nouns from the problem statement

| Noun found | Keep as a class? | Reason |
|---|---|---|
| Movie | Yes | has its own data and identity |
| Seat | Yes | has number, type, price |
| "seat layout" | No | it is a view of a Show's seats, not a thing - becomes a print method |
| Screen | Yes | has its own identity (screen number) and owns a fixed set of seats |
| Cinema | Yes | the theatre; owns screens, lists movies and shows |
| Show | Yes | one specific screening - combines a Movie + Screen + start time |
| seat status (available/booked) | No, but becomes ShowSeat | status is not a property of Seat itself - the same physical seat A1 is booked for the 6 PM show yet free for the 9 PM show - so it becomes its own class, ShowSeat, plus a SeatStatus enum |
| Customer | Yes | has name and phone; an identity independent of any one booking |
| Booking | Yes | groups a show, seats, amount and status under one identity (a booking id) |
| Ticket | No | not a persistent object - it is a formatted printout of a Booking - becomes a print method on TicketPrinter |
| Payment / UPI / Card / Cash | Yes (abstract + 3 subclasses) | three ways of doing the same thing (pay()) - a case for an abstract base class |
| price / amount | No | a derived number, not a thing with identity - becomes a calculation method (PriceCalculator) |
| booking id | No | an attribute of Booking, not a separate object |

## Verbs and the methods they became

| Verb / action in the brief | Becomes |
|---|---|
| list movies | listMovies() on Cinema |
| list shows | (loop over Cinema's shows, filtered by movie, in main.cpp) |
| display seat layout | printSeatLayout() on Show |
| book seats | bookSeats() on BookingService |
| pay | pay(amount) on Payment |
| print a ticket | printTicket() on TicketPrinter |
| cancel a booking | cancelBooking() on BookingService, cancel() on Booking |

## Classes and their key methods

| Class | Its ONE responsibility | Key methods |
|---|---|---|
| Movie | title, language, duration - nothing else | getTitle(), getLanguage(), getDurationMinutes() |
| Seat | one physical seat: number and type | getSeatNumber(), getType(), getPrice() |
| Screen | one auditorium; owns its seats | getScreenNumber(), getSeats() |
| Cinema | the theatre; owns its screens | addScreen(), addMovie(), addShow(), listMovies() |
| Show | a Movie on a Screen at a time; owns its ShowSeats | printSeatLayout(), getShowSeat(seatNo) |
| ShowSeat | status of ONE seat FOR ONE show | isAvailable(), book(), release() |
| Customer | name and phone | getName(), getPhone() |
| Booking | booking id, show, seats, amount, status | confirm(), cancel(), getStatus() |
| Payment (abstract) | the payment contract | pay(amount) - pure virtual |
| UpiPayment / CardPayment / CashPayment | how each method actually pays | pay(amount) |
| PriceCalculator | turn a list of seats into a total amount | calculateTotal(seats) - static |
| TicketPrinter | format and print a ticket - printing only | printTicket(booking) - static |
| BookingService | the orchestrator; runs the booking flow end to end | bookSeats(...), cancelBooking(id) |