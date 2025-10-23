#include <stdio.h>
#include <string.h>
#include "bus.h"
#include "file_io.h"

Bus buses[MAX];
int buscount=0;

int findbus(int busno)
{
    for(int i=0;i<buscount;i++)
    {
        if(buses[i].busno==busno)
        { 
            return i;
        }
    }
    return -1;
}

void addbus()
{
    Bus b;
    printf("Enter Bus Number: "); 
    scanf("%d", &b.busno);

    
    for (int i = 0; i < buscount; i++) {
        if (buses[i].busno == b.busno) {
            printf("\n⚠️ Bus number %d already exists!\n", b.busno);
            return;
        }
    }

    printf("Enter Source: "); 
    scanf("%s", b.source);
    printf("Enter Destination: "); 
    scanf("%s", b.destination);
    printf("Enter Fare per Seat: "); 
    scanf("%f", &b.fare);

    
    for (int i = 0; i < SEATS; i++) {
        b.seat_map[i] = 0;
    }

    
    buses[buscount++] = b;
    savebusestofile();

    printf("\n✅ Bus added successfully!\n");
}


void viewbuses()
{
    if(buscount==0)
    { 
        printf("No buses!\n");
        return; 
    }
    char src[30], dest[30]; 
    printf("Enter Source: "); 
    scanf("%s",src);
    printf("Enter Destination: "); 
    scanf("%s",dest);
    int found=0;
    printf("\n%-10s %-10s %-15s\n", "Bus No", "Fare", "Available Seats");
    printf("-------------------------------------------\n");

    for (int i = 0; i < buscount; i++)
    {
        if (strcasecmp(buses[i].source, src) == 0 && strcasecmp(buses[i].destination, dest) == 0)
        {
            int avail = 0;
            for (int j = 0; j < SEATS; j++)
            {
                if (buses[i].seat_map[j] == 0)
                    avail++;
            }

            printf("%-10d %-10.2f %-15d\n", buses[i].busno, buses[i].fare, avail);
            found = 1;
        }
    }

    if(!found)
    { 
        printf("⚠️ No buses found for this route!\n");
    }
}

void viewseats(int bus_index)
{
    Bus *b = &buses[bus_index];
    printf("\nSeat Map for Bus %d (%s -> %s)\n\n", b->busno, b->source, b->destination);
    printf("[ ] = Available   \033[31m[XX]\033[0m = Booked\n\n");

    for(int i=0;i<SEATS;i++)
    {
        if(b->seat_map[i]==0) 
        {
            printf("[%-2d]", i+1);
        }
        else 
        {
            printf("\033[31m[XX]\033[0m");
        }
        if(i%4==1)
        {
            printf(" ");
        }
        
        if(i%4==3)
        {
             printf("\n"); // new row after 4 seats
        }
    }
    printf("\n");
}

