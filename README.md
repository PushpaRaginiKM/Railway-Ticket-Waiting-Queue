# RailQueue – Railway Reservation System

## Project overview
RailQueue is a beginner-friendly C project that demonstrates the **linear queue** data structure through a railway reservation example.

The waiting list follows **FIFO (First In, First Out)**: the passenger who joins first is considered first when a confirmed ticket is cancelled.

## Module concepts used
- Queue representation using an array
- `front` and `rear` pointers
- Enqueue: insert a passenger at the rear
- Dequeue: promote the passenger at the front
- Empty queue: `front = -1`
- First insertion: `front = rear = 0`

## Objectives
- Implement Linear Queue operations (`enqueue` and `dequeue`) in C.
- Automate ticket confirmation, waiting list placement, and cancellation upgrades.
- Maintain First-In, First-Out (FIFO) fairness for waiting passengers.

## Features
1. Display trains, routes and illustrative fares
2. Book a ticket
3. Cancel a ticket
4. Check booking status using PNR
5. Display a train's waiting queue
6. View booking history

## Data Structure
- Linear Queue (2D Array)
- Structure Array
- Seat Matrix


## Sample demonstration
```text
===== RAILQUEUE RESERVATION =====
1. Show trains and fares
2. Book ticket
3. Cancel ticket
4. Check PNR
5. View waiting queue
6. Booking history
0. Exit
Enter choice: 2
Enter train number (101-103): 102
Enter passenger name: Anu
Enter age: 19
Ticket confirmed. PNR: 1001 | Seat: 1 | Fare: Rs.250
```
## Conclusion
* Demonstrates practical implementation of Linear Queues (`enqueue` and `dequeue`) in C[cite: 2].
* Guarantees fair, First-In First-Out (FIFO) ticket upgrades during cancellations[cite: 2].
* Bridges theoretical data structures with real-world reservation logic[cite: 2].

## Team Members
Name:  PUSHPA RAGINI KM   | Register No.: 20251ECE0198
Name:  ARUNA JYOTHI       | Register No.: 20251ECE0229
Name:  THEJAHWINI         | Register No.: 20251ECE0230
Name:  LEISHA             | Register No.: 20251ECE0191
Name:  SANJANA G          | Register No.: 20251ECE0210
