#ifndef CHECKIO_H_INCLUDED
#define CHECKIO_H_INCLUDED

#include"structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basicio.h"
#include <time.h>
#include <ctype.h>
#include "validation.h"

void check_out();
void check_in();

/*---------------------------------------------------------------------------------------------------------------------*/

void check_in ()
{

    reservation reservations[100];
    char line1[100];
    int i = 0, found = 0;
    FILE *f = fopen("reservation.txt", "r+");

    if (f == NULL)
    {
        printf(RED "Error opening file.\n" RESET);
        end_of_fn();
        return;
    }
    //
    int input_search;
    printf(BLUE "Enter reservation id:\n");
    printf(YELLOW "{ Enter 'm' to return to the main menu or 'e' to exit }\n" RESET);
    scanf("%d", &input_search);

    if (input_search == 'm')
    {
        end_of_fn();
        return;
    }
    else if (input_search == 'e')
    {
        end_of_fn();
        exit(0);
    }
// ************************************ copieng the file to array of structs ******************************
    while (fgets(line1, sizeof(line1), f) != NULL && i < 100)
    {
        sscanf(line1, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%[^\n]",
               &reservations[i].reservation_id,
               reservations[i].room_number,
               reservations[i].status,
               reservations[i].name,
               reservations[i].national_id,
               &reservations[i].no_nights,
               &reservations[i].check_in_date.days,
               &reservations[i].check_in_date.months,
               &reservations[i].check_in_date.years,
               reservations[i].email,
               reservations[i].number);

        if(date_validate(reservations[i].check_in_date)){
            puts(RED "Date is still in future");
            fclose(f);
            end_of_fn();
            return;
        }


        if (reservations[i].reservation_id > 0)
        {
            if (input_search == reservations[i].reservation_id)
            {
                if (strcmp(reservations[i].status, "unconfirmed") == 0)
                {
                    strcpy(reservations[i].status, "confirmed");
                    printf(GREEN "Reservation ID %d is now confirmed.\n" RESET, reservations[i].reservation_id);
                    found = 1;
                }
                else if (strcmp(reservations[i].status, "confirmed") == 0)
                {
                    printf(BLUE "The reservation is already checked in.\n" RESET);
                    found = 1;
                }
            }
            i++;
        }
    }

    if (!found)
    {
        printf(RED "Reservation ID not found.\n" RESET);
        fclose(f);
        end_of_fn();
        return;
    }
// ********************************* writing the array back to the file *****************************
    rewind(f);
    for (int j = 0; j < i; j++)
    {
        fprintf(f, "%d,%s,%s,%s,%s,%d,%d-%d-%d,%s,%s\n",
                reservations[j].reservation_id,
                reservations[j].room_number,
                reservations[j].status,
                reservations[j].name,
                reservations[j].national_id,
                reservations[j].no_nights,
                reservations[j].check_in_date.days,
                reservations[j].check_in_date.months,
                reservations[j].check_in_date.years,
                reservations[j].email,
                reservations[j].number);
    }

    fclose(f);
    end_of_fn();
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

void check_out()
{
    int i = 0;
    int found = 0;// Flag to indicate whether the search is successful
    int choice;
    char room_number[5];
    int check;

    // input reservation.txt
    reservation rev[100];
    int n_rev = input_reservation(rev);

    n_rev = input_reservation(rev);
    if (n_rev == 0) {
        printf(RED "Error: No reservations found!\n" RESET);
        end_of_fn();
        return;
    }

    // get check-out method choice
    while(1) {
        printf(BLUE "To cancel by reservation ID: " GREEN "Enter 0\n"
               BLUE "To cancel by room number: " GREEN "Enter 1\n" RESET);
        scanf(" %c", &choice);
        while(getchar() != '\n'); // clear input buffer from all chars
        if(choice == 'm' || choice == 'M'){
            end_of_fn();
            return;
        }
        if(choice == 'e' || choice == 'E'){
            exit(0);
        }
        if(choice != '0' && choice != '1'){
            puts(RED "Invalid input; enter 0 or 1");
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }
        break;
    }

    // Search for reservation
    if (choice == '0') {
        int id;
        char temps[11];
        while(1) {
            printf(BLUE "Enter reservation ID: " RESET);
            int temp = scanf("%s", temps);
            while(getchar() != '\n');
            if (strlen(temps) && (check = to_main(temps[0])))
            {
                if (check == 1)
                {
                    end_of_fn();
                    return;
                }
                if (check == 2)
                    exit(0);
            }
            id  = atoi(temps);
            if (temp != 1 || id < 0) {
                printf(RED "Error: Invalid reservation ID!\n" RESET);
                puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
                continue;
            }
            break;
        }

        for(i = 0; i < n_rev; i++) {
            if(rev[i].reservation_id == id) {
                strcpy(room_number, rev[i].room_number); // save room number to change room.txt
                found = 1;
                break;
            }// i will be equal to index at which room should change to available
        } // also i is the index of the reservation checking out
    }
/*-----------------------------------------------------------------------*/
                            //choice 0 ended
    else {
        while(1){
            printf(BLUE "Enter the room number: " RESET);
            fgets(room_number, 6, stdin);
            room_number[strcspn(room_number, "\n")] = '\0';
            if (strlen(room_number) == 1 && (check = to_main(room_number[0])))
            {
                if (check == 1)
                {
                    end_of_fn();
                    return;
                }
                if (check == 2)
                    exit(0);
            }
            if(strlen(room_number) > 4){
                printf(RED "Error: Invalid room number!\n" RESET);
                puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
                continue;
            }
            break;
        }
        for(i = 0; i < n_rev; i++) {
            if(!strcmp(rev[i].room_number, room_number)) {
                found = 1;
                break;
            } // i will be equal to index at which room changes to available
        }
    }
/*------------------------------------------------------------------------------*/
                                //choice one ended
    if (!found) {
        printf(RED "Reservation not found!\n" RESET);
        end_of_fn();
        return;
    }

    // check reservation --> that it is confirmed
    if(!strcmp(rev[i].status, "unconfirmed")) {
        printf(RED "check-out cannot be done (check-in is unconfirmed)\n" RESET);
        end_of_fn();
        return;
    }
/*------------------------------------------------------------------------------*/
                    //finished checking for any condition that will prevent checkout

    // save??
    while(1) {
        printf(BLUE "Are you sure you want to cancel reservation (save?)\n"
               GREEN "Enter 'y' for yes or 'n' for no: " RESET);
        char answer;
        scanf(" %c", &answer);
        if(answer == 'n' || answer == 'N') {
            printf(YELLOW "cancellation cancelled.\n" RESET);
            end_of_fn();
            return;
        }
        if(answer == 'y' || answer == 'Y')
            break;
        if(answer == 'm' || answer == 'M'){
            end_of_fn();
            return;
        }
        if(answer == 'e' || answer == 'E'){
            exit(0);
        }
        printf(RED "Invalid input. Please enter 'y' or 'n'\n" RESET);
        puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
        continue;
    }

/*------------------------------------------------------------------------------*/

// action:

    room r[100];
    int n_r = input_room(r);
    if (n_r == 0) {
        printf(RED "Error: Could not read room data\n" RESET);
        end_of_fn();
        return;
    }

    int room_found = 0;
    int j;
    for(j = 0; j < n_r; j++) {
        if(!strcmp(r[j].room_number, room_number)) {
            strcpy(r[j].room_status, "Available");
            room_found = 1;
            break;
        } // j is index of room!!
    }

    if (!room_found) {
        printf(RED "Error: Room not found in room database\n" RESET);
        end_of_fn();
        return;
    }

// time work:

    time_t currentTime = time(NULL);
    if (currentTime == (time_t)-1) {
        printf(RED "System date and time ERROR (reading error). Try again later\n");
        end_of_fn();
        return;  // time() sometimes return -1 if a problem occurred
    }

    struct tm *formattedTime = localtime(&currentTime);
    if (formattedTime == NULL) {  // NULL check, if localtime() failed to work correctly
        printf(RED "System date and time ERROR (format error). Try again later\n");
        end_of_fn();
        return;
    }

    int true_nights = formattedTime->tm_mday - rev[i].check_in_date.days;
    int temp=0;
    if( temp = (formattedTime->tm_mon + 1) - rev[i].check_in_date.months ){ // if not zero if will be entered
        true_nights += 30 * temp; // added number of months increase (approximated number of nights --> if 31 or 29 is ignored)
    }
    if( temp = (formattedTime->tm_year + 1900) - rev[i].check_in_date.years ){
        true_nights += 365 * temp; // added number of years increase (approximated number of nights --> leap year is excluded)
    }

    int reserved_nights = rev[i].no_nights;

    int cost=0;  // variable to store cost
    if(true_nights <= reserved_nights){
        cost = r[j].price_per_night * reserved_nights;
        printf(BLUE "cost of stay is: %d\n", cost);
        printf(BLUE "cost per night is %d and charge is for number of nights reserved %d\n", r[j].price_per_night, reserved_nights);
    }
    else{
        cost = r[j].price_per_night * reserved_nights + (r[j].price_per_night + 100) * (true_nights - reserved_nights);
        printf(BLUE "cost of stay is: %d\n", cost);
        printf(BLUE "cost per night is %d and charge is for number of rooms reserved %d "
               "+ penalty of $100 per extra night (number of extra nights = %d)",
               r[j].price_per_night, reserved_nights, true_nights - reserved_nights);
    }

//delete reservation:

    for(int k = i; k < n_rev - 1; k++) { // i is equal to index at which room changed to available
        rev[k] = rev[k + 1];
    }
    n_rev--; // new number of structs is less by one

    // write changes back to files
    write_room(r, n_r);
    write_reservation(rev, n_rev);

    printf(GREEN "Check-out Successful!\n" RESET);
    end_of_fn();

}


#endif // CHECKIO_H_INCLUDED
