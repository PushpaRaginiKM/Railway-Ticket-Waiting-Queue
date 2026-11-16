/* RailQueue - Railway Reservation using a Linear Queue
   Based on Module 2: Queue (FIFO), Enqueue and Dequeue.
   Compile: gcc railqueue.c -o railqueue
*/
#include <stdio.h>
#include <string.h>

#define TRAINS 3
#define CAPACITY 3
#define MAX_PASSENGERS 100

struct Passenger {
    int pnr, train, age, status, seat;
    char name[50];
};

int main(void) {
    struct Passenger p[MAX_PASSENGERS];
    int waiting[TRAINS][MAX_PASSENGERS];
    int front[TRAINS] = {-1, -1, -1};
    int rear[TRAINS] = {-1, -1, -1};
    int seatUsed[TRAINS][CAPACITY] = {{0}};
    int total = 0, nextPNR = 1001;
    int choice, train, age, i, j, id, pnr, found, seat;
    char name[50];
    const char *trainName[TRAINS] = {
        "Karnataka Express", "Mysuru Intercity", "Coastal Express"
    };
    const char *route[TRAINS] = {
        "Bengaluru-Delhi", "Bengaluru-Mysuru", "Bengaluru-Mangaluru"
    };
    const int fare[TRAINS] = {1200, 250, 450};

    for (i = 0; i < MAX_PASSENGERS; i++) {
        p[i].status = 0; /* 0 = cancelled, 1 = confirmed, 2 = waiting */
        p[i].seat = 0;
    }

    do {
        printf("\n===== RAILQUEUE RESERVATION =====\n");
        printf("1. Show trains and fares\n");
        printf("2. Book ticket\n");
        printf("3. Cancel ticket\n");
        printf("4. Check PNR\n");
        printf("5. View waiting queue\n");
        printf("6. Booking history\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) return 0;

        switch (choice) {
        case 1:
            printf("\nTrain  Train Name              Route                    Fare\n");
            for (i = 0; i < TRAINS; i++)
                printf("%d     %-23s %-24s Rs.%d\n",
                       101 + i, trainName[i], route[i], fare[i]);
            break;

        case 2:
            if (total == MAX_PASSENGERS) {
                printf("Passenger list is full.\n");
                break;
            }
            printf("Enter train number (101-103): ");
            scanf("%d", &train);
            train -= 101;
            if (train < 0 || train >= TRAINS) {
                printf("Invalid train number.\n");
                break;
            }
            printf("Enter passenger name: ");
            scanf(" %49[^\n]", name);
            printf("Enter age: ");
            scanf("%d", &age);
            if (age < 1 || age > 120) {
                printf("Invalid age.\n");
                break;
            }

            id = total++;
            strcpy(p[id].name, name);
            p[id].pnr = nextPNR++;
            p[id].train = train;
            p[id].age = age;
            p[id].seat = 0;

            seat = -1;
            for (i = 0; i < CAPACITY; i++)
                if (seatUsed[train][i] == 0) {
                    seat = i;
                    break;
                }
            if (seat != -1) {
                seatUsed[train][seat] = 1;
                p[id].status = 1;
                p[id].seat = seat + 1;
                printf("Ticket confirmed. PNR: %d | Seat: %d | Fare: Rs.%d\n",
                       p[id].pnr, p[id].seat, fare[train]);
            } else if (rear[train] < MAX_PASSENGERS - 1) {
                if (front[train] == -1) front[train] = 0;
                rear[train]++;
                waiting[train][rear[train]] = id;
                p[id].status = 2;
                printf("Added to waiting list. PNR: %d | Fare: Rs.%d\n",
                       p[id].pnr, fare[train]);
            } else {
                p[id].status = 0;
                printf("Waiting queue is full. Booking not accepted.\n");
            }
            break;

        case 3:
            printf("Enter PNR to cancel: ");
            scanf("%d", &pnr);
            found = -1;
            for (i = 0; i < total; i++)
                if (p[i].pnr == pnr && p[i].status != 0) {
                    found = i;
                    break;
                }
            if (found == -1) {
                printf("Active PNR not found.\n");
                break;
            }

            train = p[found].train;
            if (p[found].status == 1) {
                p[found].status = 0;
                printf("Confirmed ticket cancelled.\n");

                /* Dequeue the first active passenger in FIFO order. */
                while (front[train] != -1 && front[train] <= rear[train]) {
                    id = waiting[train][front[train]];
                    front[train]++;
                    if (p[id].status == 2) {
                        for (j = 0; j < CAPACITY; j++)
                            if (seatUsed[train][j] == 0) break;
                        if (j == CAPACITY) break;
                        seatUsed[train][j] = 1;
                        p[id].status = 1;
                        p[id].seat = j + 1;
                        printf("Waiting PNR %d is now confirmed. Seat: %d\n",
                               p[id].pnr, p[id].seat);
                        break;
                    }
                }
                if (front[train] > rear[train])
                    front[train] = rear[train] = -1;
            } else {
                p[found].status = 0;
                printf("Waiting-list booking cancelled.\n");
            }
            break;

        case 4:
            printf("Enter PNR: ");
            scanf("%d", &pnr);
            found = -1;
            for (i = 0; i < total; i++)
                if (p[i].pnr == pnr) {
                    found = i;
                    break;
                }
            if (found == -1 || p[found].status == 0) {
                printf("PNR not found or cancelled.\n");
            } else {
                printf("\nPNR: %d\nName: %s\nTrain: %s\nAge: %d\n",
                       p[found].pnr, p[found].name,
                       trainName[p[found].train], p[found].age);
                printf("Status: %s\nSeat: ",
                       p[found].status == 1 ? "Confirmed" : "Waiting");
                if (p[found].seat)
                    printf("%d\n", p[found].seat);
                else
                    printf("Not assigned\n");
            }
            break;

        case 5:
            printf("Enter train number (101-103): ");
            scanf("%d", &train);
            train -= 101;
            if (train < 0 || train >= TRAINS) {
                printf("Invalid train number.\n");
                break;
            }
            printf("Waiting queue (front to rear): ");
            if (front[train] == -1)
                printf("Empty");
            else
                for (i = front[train]; i <= rear[train]; i++) {
                    id = waiting[train][i];
                    if (p[id].status == 2)
                        printf("%d ", p[id].pnr);
                }
            printf("\nFront = %d, Rear = %d\n",
                   front[train], rear[train]);
            break;

        case 6:
            printf("\nPNR     Name                     Train  Status\n");
            for (i = 0; i < total; i++) {
                if (p[i].status == 0) continue;
                printf("%-7d %-24s %-6d %s\n", p[i].pnr, p[i].name,
                       p[i].train + 101,
                       p[i].status == 1 ? "Confirmed" : "Waiting");
            }
            break;

        case 0:
            printf("Thank you for using RailQueue.\n");
            break;

        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
