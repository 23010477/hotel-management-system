#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include"structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "basicio.h"
#include"validation.h"

void rooms_availability();
void view_customer_details();
void Query();
void reservation_report();
void print_sorted();

/*------------------------------------------------------------------------*/

void rooms_availability()
{
    FILE *fptr = fopen("room.txt", "r"); // Open the file in read mode
    if (fptr == NULL) // Check if the file was opened successfully
    {
        printf(RED"Error: Could not open the file.\n");
        return;
    }

    char line[100][100]; // Array to store lines from the file
    int i = 0;
    printf(GREEN"{  this is our rooms  }\n"); // designed title in the output
    while (fgets(line[i], 100, fptr) != NULL && i < 100) // Read lines from the file
    {
        printf(BLUE"%s"RESET, line[i]); // Print each line
        i++;
    }
    printf("\n");

    fclose(fptr); // Close the file
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

void view_customer_details()
{
    reservation reservations[100];
    int id, i = 0;
    char room_number[5];
    char choice;
    printf(YELLOW "Enter 'm' to return to the main menu or 'e' to exit at anytime\n" RESET);

    while(1){
        printf(GREEN "Enter 1: " BLUE "to view by Reservation id\n"
               GREEN "Enter 2: " BLUE "to view by Room Number\n" RESET);
        scanf(" %c", &choice);
        while (getchar() != '\n');
        if (to_main(choice) == 1) // Return to menu
        {
            end_of_fn();
            return;
        }
        else if (to_main(choice) == 2) // Exit
            exit(0);

        if (choice != '1' && choice != '2')
        {
            printf(RED "Invalid choice. Please enter a valid option (1 or 2).\n" RESET);
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }
        break;
    }

    if (choice == '1')
    {
        int id;
        char temps[11];
        int check;
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
    }
    else if (choice == '2')
    {
        while(1){
            printf(BLUE " enter your room rumber:\n" RESET);
            printf(YELLOW "{ to back to main enter 0}\n" RESET);
            scanf("%s", room_number);
            if (strlen(room_number) == 1 && (to_main(room_number[0]) == 1)){
                end_of_fn();
                return;
            }
            if (strlen(room_number) == 1 && (to_main(room_number[0]) == 2)){
                exit(0);
            }
            if(strlen(room_number) >= 5){
                puts(RED "Invalid room number: too long");
                puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
                continue;
            }
            break;
        }
    }

    int n_rev = input_reservation(reservations);

    int found = 0;
    for (int i = 0; i < n_rev; i++)
    {
        if (id == reservations[i].reservation_id || strcmp(room_number, reservations[i].room_number) == 0) // if the input id ==reserved id
        {
            printf(GREEN "your reservation id: %d\n Name: %s\n National id: %s\n Email: %s\n Number: %s\n",
                   reservations[i].reservation_id,
                   reservations[i].name,
                   reservations[i].national_id,
                   reservations[i].email,
                   reservations[i].number);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf(RED "invalid reservation id"); // if the input id != reserved id
        end_of_fn();
        return;
    }
    end_of_fn();
    return;
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

void Query()
{
    printf(YELLOW "Enter m to return to the main menu or e to exit at anytime\n" RESET);
    reservation reservations[100];
    room rooms[100];

    // Open files and check for errors
    input_reservation(reservations);
    input_room(rooms);

    // Ask for search option
    char choice;
    while(1){
        puts(BLUE "to search by name (for reservation details and the customer info)");
        puts(GREEN "\t Enter 1");
        puts(BLUE "to search by room number (for room info)");
        puts(GREEN "\t Enter 2");
        puts(BLUE "to search by room status (to view all available and occupied rooms)");
        puts(GREEN "\t Enter 3");
        scanf(" %c", &choice);
        while (getchar() != '\n');// clear input buffer after scanf

        // Handle 'm' or 'e' input

        if ( to_main(choice) == 1) // Return to menu
        {
            end_of_fn();
            return;
        }
        else if (to_main(choice) == 2) // Exit
            exit(0);

        if (choice < '1' || choice > '3')
        {
            printf(RED "Invalid choice. Please enter a valid option (1-3).\n" RESET);
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }
        break;
    }

    // Get search term
    char search_term[100];
    printf(BLUE "Enter your search term: " RESET);
    fgets(search_term, sizeof(search_term), stdin);
    search_term[strcspn(search_term, "\n")] = '\0'; // remove extra newline

    // handle 'm' or 'e' input for search term
    if (strlen(search_term)==1 && to_main(search_term[0])== 1)
    {
        end_of_fn();
        return;
    }
    else if (strlen(search_term)==1 && to_main(search_term[0]) == 2)
        exit(0);


    int found = 0;

    // Search by name
    if (choice=='1')
    {
        for (int i = 0; i < 100; i++)
        {
            if (strcmp(search_term, reservations[i].name) == 0)
            {
                printf(BLUE "Customer Information:\n");
                printf(GREEN "\tName: %s\n\tNational ID: %s\n\tEmail: %s\n\tPhone Number: %s\n",
                       reservations[i].name,
                       reservations[i].national_id,
                       reservations[i].email,
                       reservations[i].number);
                printf(BLUE"Reservation Details:\n");
                printf(GREEN"\tReservation ID: %d\n\tRoom Number: %s\n\tRoom Status: %s\n\tNumber of Nights: %d\n\tCheck-in Date: %d-%d-%d\n",
                       reservations[i].reservation_id,
                       reservations[i].room_number,
                       reservations[i].status,
                       reservations[i].no_nights,
                       reservations[i].check_in_date.days,
                       reservations[i].check_in_date.months,
                       reservations[i].check_in_date.years);
                found = 1;
                break;
            }
        }
    }
    // Search by room number
    else if (choice=='2')
    {
        for (int i = 0; i < 100; i++)
        {
            if (strcmp(search_term, rooms[i].room_number) == 0)
            {
                printf(BLUE "Room Information:\n");
                printf(GREEN"\tRoom Status: %s\n\tRoom View: %s\n\tPrice per Night: %d\n",
                       rooms[i].room_status,
                       rooms[i].room_view,
                       rooms[i].price_per_night);
                // Check if the room is reserved
                for (int j = 0; j < 100; j++)
                {
                    if (strcmp(rooms[i].room_number, reservations[j].room_number) == 0)
                    {
                        printf(GREEN"\tReserved By: %s\n", reservations[j].name);
                        printf(GREEN"\tNational ID: %s\n\tEmail: %s\n\tPhone: %s\n",
                               reservations[j].national_id,
                               reservations[j].email,
                               reservations[j].number);
                        break;
                    }
                }
                found = 1;
                break;
            }
        }
    }
    // Search by room status
    else if (choice=='3')
    {
        for (int i = 0; i < 100; i++)
        {
            if (strcmp(search_term, rooms[i].room_status) == 0)
            {
                printf(BLUE "Room Information:\n");
                printf(GREEN"\tRoom Number: %s\n\tRoom View: %s\n\tPrice per Night: %d\n",
                       rooms[i].room_number,
                       rooms[i].room_view,
                       rooms[i].price_per_night);
                found = 1;
            }
        }
    }

    if (!found)
    {
        printf(RED "No matches found.\n" RESET);
    }
    end_of_fn();
    return;
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

void reservation_report()
{
    date d;
    int check;
    while(1){
        printf(BLUE "\nEnter date in the format: dd-mm-yyyy\n" RESET);
        int no_input = scanf("%d-%d-%4d", &d.days, &d.months, &d.years); //check reads number of inputs read by scanf
        if(no_input == 1){
            puts(YELLOW "if you want to retry date input enter any char; enter m or e to go to main menu or exit");
            char tempc;
            scanf(" %c", &tempc);
            if(check = to_main(tempc)){
                if(check == 1) end_of_fn(); return; if(check == 2) exit(0);
            }
        }
        if(no_input != 3){
            puts(RED "Invalid date format. Please enter in " BOLD "dd-mm-yyyy format.\n" RESET);
            continue;
        }
        if(!date_validate(d)){
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }
        break;
    }


    reservation line[100];
    int n = input_reservation(line);

    int c=0;
    puts(BLUE UNDERLINE "Customers going to check in on that day:\n"RESET);
    for(int i=0; i<n; i++){
        if(line[i].check_in_date.years == d.years){
            if(line[i].check_in_date.months == d.months){
                if(line[i].check_in_date.days == d.days){
                    c++;
                    printf(BLUE UNDERLINE "\tCustomer number %d:\n"RESET, c);
                    put_customer(line[i]); // if same date print customer details
                }
            }
        }
    }
    if(!c){ // in case no customers check in on that day
        puts("None");
    }

    end_of_fn();
    return;
}

 /*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

void print_sorted()
{
    reservation reservations[100];

    int n = input_reservation(reservations);

     for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            date d1 = reservations[j].check_in_date;
            date d2 = reservations[j + 1].check_in_date;

            if (d1.years > d2.years ||
                (d1.years == d2.years && d1.months > d2.months) ||
                (d1.years == d2.years && d1.months == d2.months && d1.days > d2.days))
            {
                // Swap reservations
                reservation temp = reservations[j];
                reservations[j] = reservations[j + 1];
                reservations[j + 1] = temp;
            }
        }
    }

    write_reservation(reservations, n);

    for(int i=0; i<n; i++){
        printf(BLUE UNDERLINE "Customer %d\n\n" RESET, i+1);
        put_customer(reservations[i]);
    }

    end_of_fn();
    return;
}


#endif // VIEW_H_INCLUDE
