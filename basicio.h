#ifndef BASICIO_H_INCLUDED
#define BASICIO_H_INCLUDED

#include"structs.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int to_main(int c);
int input_reservation(reservation line[]); // input data in reservation.txt into array entered in argumnet
void put_customer(reservation x); // print name + national ID + email + phone number
int add_to_reservation(reservation x); //append reservation with one struct
void write_reservation(reservation line[], int n); // write reservation.txt
void write_room(room line[], int n); // write room.txt
int input_room(room r[]); // input data in room.txt into array entered in argumnet
void end_of_fn(); // ask for any char to end function and return to menu

/*---------------------------------------------------------------------------------------------------------------------*/


int to_main(int c)
{
    tolower(c);
    if(c == 'm')
        return 1;
    if(c == 'e')
        return 2;
    return 0;
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

int input_reservation(reservation line[]) // input data in reservation.txt into array entered in argument and return number of structs
{
    FILE *fptr = fopen("reservation.txt", "r");
    if (fptr == NULL) {
        printf(RED "Error: Could not open the reservation.txt\n" RESET);
        return -1;
    }

    int i;
    char buffer[250];
    for(i = 0; fgets(buffer, sizeof(buffer), fptr) && i < 100; i++) {
        if (sscanf(buffer, "%d,%4[^,],%11[^,],%99[^,],%14[^,],%d,%2d-%2d-%4d,%49[^,],%11[^\n]",
            &line[i].reservation_id,
            line[i].room_number,
            line[i].status,
            line[i].name,
            line[i].national_id,
            &line[i].no_nights,
            &line[i].check_in_date.days,
            &line[i].check_in_date.months,
            &line[i].check_in_date.years,
            line[i].email,
            line[i].number) != 11) {
            printf(RED "Warning: Invalid format in line %d\n" RESET, i + 1);
            continue;
        }
    }

    fclose(fptr);
    return i;
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

void put_customer(reservation x) // print name + national ID + email + phone number
{
    printf(BLUE "Name: " GREEN "%s\n", x.name);
    printf(BLUE "National ID:" GREEN "%s\n", x.national_id);
    printf(BLUE "E-mail:" GREEN "%s\n", x.email);
    printf(BLUE "Phone Number:" GREEN "%s\n", x.number);
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

int add_to_reservation(reservation x) //append reservation with one struct
{
    FILE *fptr = fopen("reservation.txt", "a+");

    if (fptr == NULL) {
        printf("Error: Could not open the file.\n");
        return 0;
    }

    int num_written = fprintf(fptr, "%d,%s,%s,%s,%s,%d,%02d-%02d-%4d,%s,%11s\n",
                              x.reservation_id,
                              x.room_number,
                              x.status,
                              x.name,
                              x.national_id,
                              x.no_nights,
                              x.check_in_date.days,
                              x.check_in_date.months,
                              x.check_in_date.years,
                              x.email,
                              x.number);

    // in case error with fprintf
    if (num_written < 0) {
        printf("Error writing to file.\n");
        fclose(fptr);
        return 0;
    }

    fclose(fptr);
    return 1;
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

void write_reservation(reservation line[], int n)//n is number of elements
{
        FILE *fptr = fopen("reservation.txt", "w"); // Open the file in write mode
    if (fptr == NULL){  // Check if the file was opened successfully
        printf(RED "Error: Could not open the reservation.txt\n");
        return;
    }

    for (int i = 0; i < n; i++)
        {
            fprintf(fptr, "%d,%s,%s,%s,%s,%d,%d-%d-%4d,%s,%11s\n",
                              line[i].reservation_id,
                              line[i].room_number,
                              line[i].status,
                              line[i].name,
                              line[i].national_id,
                              line[i].no_nights,
                              line[i].check_in_date.days,
                              line[i].check_in_date.months,
                              line[i].check_in_date.years,
                              line[i].email,
                              line[i].number);
        }

    fclose(fptr);
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

void write_room(room line[], int n)//n is number of elements
{
    FILE *fptr = fopen("room.txt", "w"); // Open the file in rwrite mode
    if (fptr == NULL){  // Check if the file was opened successfully
        printf(RED "Error: Could not open the room.txt\n" UNDERLINE "any output of room number or id is invalid\n"RESET);
        return;
    }

    for (int i = 0; i < n; i++)
        {
            fprintf(fptr, "%s %s %s %d\n",
                    line[i].room_number,
                    line[i].room_status,
                    line[i].room_view,
                    line[i].price_per_night);
        }

    fclose(fptr);
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

int input_room(room r[])
{
    FILE *froom = fopen("room.txt", "r");
    if (froom == NULL) {
        printf(RED "Error: Cannot open Room.txt!\n" RESET);
        return 0;
    }

    int i;
    char buffer[50];
    for(i = 0; fgets(buffer, sizeof(buffer), froom) && i < 100; i++) {
        if (sscanf(buffer, "%4s %9s %10s %d",
            r[i].room_number,
            r[i].room_status,
            r[i].room_view,
            &r[i].price_per_night) != 4) {
            printf(RED "Warning: Invalid format in line %d\n" RESET, i + 1);
            continue;
        }
    }

    fclose(froom);
    return i;
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

void end_of_fn() // function it will be in will not return except when this function returns
{
    printf(YELLOW "Enter any character (or press enter) to go back to main menu (Enter e to exit): " RESET);
    char m;
    //while(getchar() != '\n'); // clear input buffer from any chars before input
    scanf(" %c", &m);
    if(m=='e' || m=='E')
        exit(0);
    printf(CLEAR);
}


#endif // BASICIO_H_INCLUDED
