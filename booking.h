#ifndef BOOKING_H
#define BOOKING_H
#include "bus.h"

typedef struct
{
    int id;
    char passenger[30];
    int busno;
    int seat_no[SEATS];
    int seat_booked;
    float fare;
}Booking;

extern Booking bookings[MAX];
extern int booking_count;


void bookticket();
void cancelbooking();
void viewbooking();
void printticket(Booking b);

#endif