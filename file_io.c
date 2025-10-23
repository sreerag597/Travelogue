#include<stdio.h>
#include "file_io.h"
#include "bus.h"
#include "booking.h"

extern Bus buses[];
extern int buscount;
extern Booking bookings[];
extern int bookingcount;

void savebusestofile()
{
    FILE *fp = fopen("buses.txt", "w");
    if (!fp) 
    {
        printf("Error saving buses file!\n");
        return;
    }

    // Save each bus cleanly
    for (int i = 0; i < buscount; i++) 
    {
        fprintf(fp, "%d %s %s %.2f\n", 
                buses[i].busno, 
                buses[i].source, 
                buses[i].destination, 
                buses[i].fare);

        // Save seat map (0 or 1 per seat)
        for (int j = 0; j < SEATS; j++) 
        {
            fprintf(fp, "%d ", buses[i].seat_map[j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void loadbusesfromfile()
{
    FILE *fp = fopen("buses.txt", "r");
    if (!fp) return;

    buscount = 0;
    while (fscanf(fp, "%d %s %s %f", 
                  &buses[buscount].busno, 
                  buses[buscount].source, 
                  buses[buscount].destination, 
                  &buses[buscount].fare) == 4)
    {
        for (int i = 0; i < SEATS; i++) {
            fscanf(fp, "%d", &buses[buscount].seat_map[i]);
        }
        buscount++;
    }

    fclose(fp);
}

void savebookingstofile()
{
    FILE *fp = fopen("bookings.txt", "w");
    if (!fp) {
        printf("❌ Error saving bookings file!\n");
        return;
    }

    for (int i = 0; i < booking_count; i++) {
        fprintf(fp, "%d %s %d %d %.2f\n",
                bookings[i].id,
                bookings[i].passenger,
                bookings[i].busno,
                bookings[i].seat_booked,
                bookings[i].fare);

        for (int j = 0; j < bookings[i].seat_booked; j++) {
            fprintf(fp, "%d ", bookings[i].seat_no[j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

void loadbookingsfromfile()
{
    FILE *fp = fopen("bookings.txt", "r");
    if (!fp) return;

    booking_count = 0;
    while (fscanf(fp, "%d %s %d %d %f",
                  &bookings[booking_count].id,
                  bookings[booking_count].passenger,
                  &bookings[booking_count].busno,
                  &bookings[booking_count].seat_booked,
                  &bookings[booking_count].fare) == 5)
    {
        for (int j = 0; j < bookings[booking_count].seat_booked; j++) {
            fscanf(fp, "%d", &bookings[booking_count].seat_no[j]);
        }

        // mark those seats as booked in the corresponding bus
        for (int i = 0; i < buscount; i++) {
            if (buses[i].busno == bookings[booking_count].busno) {
                for (int j = 0; j < bookings[booking_count].seat_booked; j++) {
                    buses[i].seat_map[bookings[booking_count].seat_no[j] - 1] = 1;
                }
                break;
            }
        }

        booking_count++;
    }

    fclose(fp);
}