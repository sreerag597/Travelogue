#include <stdio.h>
#include <string.h>
#include "booking.h"
#include "bus.h"
#include "file_io.h"

Booking bookings[MAX];
int booking_count=0;

void printticket(Booking b)
{
    printf("\n================== BUS TICKET ==================\n");
    printf("Booking ID   : %d\n",b.id);
    printf("Passenger    : %s\n",b.passenger);
    printf("Bus Number   : %d\n",b.busno);
    printf("Seats Booked : ");
    for(int i=0;i<b.seat_booked;i++)
    {
         printf("%d ",b.seat_no[i]);
    }
    printf("\nTotal Fare   : ₹%.2f\n",b.fare);
    printf("================================================\n");
}

void bookticket()
{
    if(buscount==0)
    { 
        printf("\nNo buses available!\n");
         return; 
    }

    char src[30], dest[30];
    printf("Enter Source: "); 
    scanf("%s", src);
    printf("Enter Destination: "); 
    scanf("%s", dest);

    int found=0;
    printf("\nAvailable Buses for %s -> %s\n\n", src, dest);
    printf("\n%-10s %-10s %-20s\n", "Bus No", "Fare", "Available Seats");
    printf("------------------------------------------\n");

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

            printf("%-10d %-10.2f %-20d\n", buses[i].busno, buses[i].fare, avail);
            found = 1;
        }
    }

    if(!found)
    { 
        printf("⚠️ No buses found!\n"); 
        return; 
    }

    int bus_no; 
    printf("Enter Bus Number to book: "); 
    scanf("%d", &bus_no);
    int idx=findbus(bus_no); 
    if(idx==-1)
    { 
        printf("Bus not found!\n"); 
        return; 
    }

    viewseats(idx);

    Booking b; 
    b.id=booking_count+1; 
    b.busno=bus_no;
    printf("Enter Passenger Name: "); 
    scanf("%s", b.passenger);
    printf("How many seats to book: "); 
    scanf("%d",&b.seat_booked);

    int available=0; 
    for(int i=0;i<SEATS;i++)
    {
        if(buses[idx].seat_map[i]==0)
        { 
            available++;
        }
    }
    if(b.seat_booked>available)
    { 
        printf("Not enough seats!\n"); 
        return; 
    }

    printf("Enter seat numbers to book: ");
    for(int i=0;i<b.seat_booked;i++)
    {
        scanf("%d",&b.seat_no[i]);
        if(buses[idx].seat_map[b.seat_no[i]-1]==1)
        {
            printf("Seat %d booked! Try again.\n",b.seat_no[i]);
            i--; 
            continue;
        }
        buses[idx].seat_map[b.seat_no[i]-1]=1;
    }

    b.fare = b.seat_booked * buses[idx].fare;
    bookings[booking_count++]=b;
    savebookingstofile();
    savebusestofile();
    printticket(b);
}

void cancelbooking()
{
    int id; 
    printf("Enter Booking ID to cancel: "); 
    scanf("%d",&id);
    for(int i=0;i<booking_count;i++)
    {
        if(bookings[i].id==id)
        {
            int idx=findbus(bookings[i].busno);
            for(int j=0;j<bookings[i].seat_booked;j++)
            {
                buses[idx].seat_map[bookings[i].seat_no[j]-1]=0;
            }
            for(int k=i;k<booking_count-1;k++)
            {
                 bookings[k]=bookings[k+1];
            }
            booking_count--;
            savebookingstofile();
            savebusestofile();
            printf("Booking cancelled!\n");
            return;
        }
    }
    printf("Booking ID not found!\n");
}

void viewbooking()
{
    if(booking_count==0)
    { 
        printf("No bookings!\n"); 
        return; 
    }
    printf("\n%-5s %-15s %-8s %-10s %-10s\n", "ID", "Passenger", "Bus No", "Seats", "Fare");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < booking_count; i++)
    {
        printf("%-5d %-15s %-8d %-10d %-10.2f\n",
           bookings[i].id,
           bookings[i].passenger,
           bookings[i].busno,
           bookings[i].seat_booked,
           bookings[i].fare);
    }

}
