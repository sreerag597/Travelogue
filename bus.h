#ifndef BUS_H
#define BUS_H

#define MAX 20
#define SEATS 40

typedef struct
{
    int busno;
    char source[30];
    char destination[30];
    float fare;
    int seat_map[SEATS];
}Bus;

extern Bus buses[MAX];
extern int buscount;

int findbus(int busno);
void addbus();
void viewbuses();
void viewseats(int bus_index);

#endif