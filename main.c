#include<stdio.h>
#include<stdlib.h>
#include "bus.h"
#include "booking.h"
#include "file_io.h"

int main()
{
    loadbusesfromfile();
    loadbookingsfromfile();
    int choice;

    while(1)
    {
        printf("\n==== TRAVELOGUE ====\n");
        printf("\n1. Add Bus\n2. View Buses\n3. View Seat Map\n");
        printf("4. Book Ticket\n5. Cancel Booking\n6. View Bookings\n7. Exit\n");
        printf("Enter choice: "); 
        scanf("%d",&choice); 
        switch(choice)
        {
            case 1: 
                addbus();
                break;

            case 2:
                viewbuses();
                break;

            case 3:
                {
                int bus_no; 
                printf("Enter Bus Number: "); 
                scanf("%d",&bus_no);
                int idx=findbus(bus_no);
                if(idx!=-1) 
                {
                    viewseats(idx); 
                }
                else 
                {
                    printf("Bus not found!\n");
                }
                break;
            }

            case 4:
                bookticket();
                break;

            case 5:
                cancelbooking();
                break;

            case 6:
                viewbooking();
                break;

            case 7:
                printf("Exiting...");
                exit(0);

            default :
                printf("Invalid choice!\n");
        }  
    }
    return 0;

}