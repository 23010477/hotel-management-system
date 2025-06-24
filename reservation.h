#ifndef RESERVATION_H_INCLUDED
#define RESERVATION_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<ctype.h>

#include "structs.h"
#include"validation.h"
#include"basicio.h"

void reserve();
void edit_reservation();
void cancel_reservation();

/*---------------------------------------------------------------------------------------------------------------------*/

void reserve()
{
/* ---------------------------------------------------------------------------------- */
                            //receiving customer data
    reservation x;
    puts(YELLOW "Enter m to go back to menu or enter e to exit program " UNDERLINE "at any time" RESET);
    int check; // check to go to main

    while(1){
        printf(BLUE "Enter name: "RESET);
        fgets(x.name,120,stdin); // extra allowance of chars to check number of chars by validation test
        // if I restricted fgets to correct value: validation will not detect error and extra chars will be saved by the next fgets! (opening a chance for an error undetected)
        x.name[strcspn(x.name, "\n")]='\0'; //replace \n with \0 only if found (strcspn returns index of the first encounter of \n or \0 in this case)
        if(strlen(x.name)==1 && (check = to_main(x.name[0]))){
            if(check == 1) {end_of_fn(); return;}; if(check == 2) exit(0);
        } // if input was to go back to main menue
        if(!name_validate(x.name)){
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }

        printf(BLUE"\nCustomer details: ");
        printf(GREEN "\n\tEnter National ID: " RESET);
        fgets(x.national_id,20,stdin);
        x.national_id[strcspn(x.national_id, "\n")]='\0'; //replace \n with \0 only if found (this function is crucial for validation to work if correct number of chars is entered)
        if(strlen(x.national_id)==1 && (check = to_main(x.national_id[0]))){
            if(check == 1) {end_of_fn(); return;}; if(check == 2) exit(0);
        } // if input was to go back to main menue
        if(!national_id_validate(x.national_id)){
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }

        printf(GREEN"\n\tEnter e-mail: "RESET);
        fgets(x.email,70,stdin);
        x.email[strcspn(x.email, "\n")]='\0';
        if(strlen(x.email)==1 && (check = to_main(x.email[0]))){
            if(check == 1) {end_of_fn(); return;}; if(check == 2) exit(0);
        } // if input was to go back to main menue
        if(!email_validate(x.email)){
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }

        printf(GREEN "\n\tEnetr mobile number: "RESET);
        fgets(x.number,15,stdin);
        x.number[strcspn(x.number, "\n")]='\0'; //replace \n with \0 only if found
        if(strlen(x.number)==1 && (check = to_main(x.number[0]))){
            if(check == 1) {end_of_fn(); return;}; if(check == 2) exit(0);
        } // if input was to go back to main menue
        if(!number_validate(x.number)){
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }

        printf(BLUE "\nEnter date in the format: dd-mm-yyyy\n" RESET);
        int no_input = scanf("%2d-%2d-%4d", &x.check_in_date.days, &x.check_in_date.months, &x.check_in_date.years); //check reads number of inputs read by scanf
        if(no_input == 1){
            puts(YELLOW "if you want to retry date input enter any char; enter m or e to go to main menu or exit");
            char tempc;
            scanf(" %c", &tempc);
            if(check = to_main(tempc)){
                if(check == 1) {end_of_fn(); return;}; if(check == 2) exit(0);
            }
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        } // if input was m
        if(no_input != 3){
            puts(RED "Invalid date format. Please enter in " BOLD "dd-mm-yyyy format.\n" RESET);
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }
        if(!date_validate(x.check_in_date)){
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }

        printf(BLUE "Number of Nights: " RESET);
        scanf("%d", &x.no_nights);
        while(getchar() != '\n'); // clear input buffer from any chars
        if(check = to_main(x.no_nights)){
            if(check == 1) {end_of_fn(); return;}; if(check == 2) exit(0);
        } // if input was to go back to main menue
        if(x.no_nights < 1){
            puts(RED "number of nights must be greater than or equal 1");
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }
        //Optionally, fflush(stdin) can be used to clear any remaining characters in the input buffer before prompting the user again.
        break;
    }

    char y[11]; // to save room_status
    while(1){
        printf(BLUE "\nChoose room category\n"
               GREEN "\t-for SeaView enter 1\n"
               "\t-for LakeView enter 2\n"
               "\t-for GardenView enter 3\n"RESET);
               int choice;
               scanf("%d", &choice);
               while(getchar() != '\n'); // clear input buffer from any chars
        switch(choice)
        {
            case 1: strcpy(y, "SeaView"); break;
            case 2: strcpy(y, "LakeView"); break;
            case 3: strcpy(y, "GardenView"); break;
            case 'm': case 'M': end_of_fn(); return;
            case 'e': case 'E': exit(0);
            default: puts(RED "Invlaid input, please enter 1 or 2 or 3");
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }
        break;
    }
    strcpy(x.status, "unconfirmed"); // to be changed to confirmed with check-in
/* ---------------------------------------------------------------------------------- */
                            // generating random ID + check uniqueness:

    srand(time(NULL));// Seed the random number generator with current time
    //ensures that the seed value changes each time the program runs, resulting in a different sequence of random numbers
    //if we did not seed, every time we run the program the same sequence will appear

    x.reservation_id = rand(); // rand will never exceed the max value for int

    // input reservation.txt into an array
    reservation line[100]; // Array to store lines from the file in structs
    int n = input_reservation(line); // line array is filled with reservation.txt data and n is number of elements (not last index number)

    for(int i=0; i<n; i++){
        if(line[i].reservation_id == x.reservation_id){
            x.reservation_id = rand();
            i = 0; // to check the whole array again after changing id
        }
    }
/* ---------------------------------------------------------------------------------- */
                            // Find a suitable room

    FILE *fptr = fopen("room.txt", "r");
    room r[100]; // array to store lines from the file in structs
    int n_r; //number of read structs
    char buffer[250]; //enough size to contain a whole line
    for(n_r=0 ; fgets(buffer, sizeof(buffer), fptr) && n_r<100 ; n_r++){
        sscanf(buffer,"%4[^' '] %9[^' '] %10[^' '] %d\n",
        r[n_r].room_number,
        r[n_r].room_status,
        r[n_r].room_view,
        &r[n_r].price_per_night);
    }
    fclose(fptr);

    int n_i = -1;  // n_i is the index that will point to the room that will be used
    for(int i=0; i<n_r; i++){ //n_r is number of elements and not last index
        if(!strcmp( r[i].room_view ,y) && !strcmp( r[i].room_status ,"Available")){ //I cannot compare r.room_status with available using == bec. in this way the pointers will be compared
            strcpy(r[i].room_status,"Reserved");
            strcpy(x.room_number,r[i].room_number);
            n_i = i; // n_i is now the index that points to the room that will be used
            break;
        }
    }

    if(n_i == -1){
        puts(RED "No available room with this specifications");
        end_of_fn();
        return;
    }

/* ---------------------------------------------------------------------------------- */
                            // Save Reservation??
    printf(BLUE "the price per night for your room will be: %d\n", r[n_i].price_per_night);

    while(1){
        printf(BLUE"Do you want to proceed and save the reservation?\n"
               GREEN "\tif yes enter y\tif no enter n\n"RESET);
        char a;//answer
        getchar(); //takes \n from printf
        scanf(" %c", &a);
        if(check = to_main(a)){
            if(check == 1) return; if(check == 2) exit(0);
        }
        if(a=='n' || a=='N'){
            puts(YELLOW "Reservation is canceled");
            end_of_fn();
            return;
        }
        if(a=='y' || a=='Y'){
            if(!add_to_reservation(x)){
                puts(BLUE "if you want to try again enter y; else enter n");
                continue;
            }
            break;
        }
        puts(RED "invalid input; please enter either n or y");
    }

/* ---------------------------------------------------------------------------------- */
                        // Write room.txt again

    write_room(r, n_r); // r is array of lines of room.tx + n_r is number of elements
    puts(BLUE "Reservation saved successfully! (if no error in opening room.txt)");
    printf(GREEN "\tCustomer's ID is: " RESET "%d\n"
           GREEN "\tCustomer's room number is: " RESET "%s\n", x.reservation_id, x.room_number);

    end_of_fn();
    return;

printf(CLEAR);
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

void edit_reservation()
{
    int reservation_id = 0;
    char temp;
    reservation new;
    room room1;

    reservation line[100];
    int count = input_reservation(line); // copy reservation.txt into array


    printf(GREEN "*******************************************************************************************************\n" RESET);
    while(1){
        printf(BLUE "To edit your reservation data, choose to enter the room number or reservation id:\n");
        printf(GREEN "\tenter 1 to enter reservation id , or 0 to enter the room number :\n");
        printf(YELLOW "                                                            { to back to main enter m and to exit enter e }\n" RESET);
        scanf(" %c", &temp);
        while(getchar() != '\n'); // clear input buffer from any chars
        if (temp == 'm')
        {
            end_of_fn();
            return;
        }
        else if (temp == 'e')
        {
            exit(0);
        }
        if (temp == '0')
        {
            printf(BLUE "To edit your reservation data, enter your room rumber:\n" RESET);
            printf(YELLOW "                                                            { to back to main enter m and to exit enter e }\n" RESET);
            scanf("%s", room1.room_number);
            if (strcmp(room1.room_number, "m") == 0)
            {
                end_of_fn();
                return;
            }
            else if (strcmp(room1.room_number, "e") == 0)
            {
                exit(0);
            }
            break;
        }
        else if (temp == '1')
        {
            printf(BLUE "To edit your reservation data, enter your reservation ID:\n" RESET);
            printf(YELLOW "                                                            { to back to main enter m and to exit enter e }\n" RESET);
            scanf("%d", &reservation_id);
            if (reservation_id == 'm')
            {
                end_of_fn();
                return;
            }
            else if (reservation_id == 'e')
            {
                exit(0);
            }
            break;
        }
        else{
            puts(RED "Invalid input!");
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }
    }
    // ************************************ Search for the reservation ID in the array ***********************************************
    int found = 0, index = 0;
    for (int i = 0; i < count; i++)
    {
        if (line[i].reservation_id == reservation_id || (strcmp(line[i].room_number, room1.room_number)) == 0) // when we find the true id or true room number we will edit the reservation
        {
            strcpy(new.room_number,room1.room_number); //to have everything synchronised
            found = 1;
            index = i; //index of the line being changed
            new = line[i]; // default is no change
            break;
        }
    }
    if (!found)
    {
        printf(RED "Reservation ID not found.\n" RESET);
        end_of_fn();
        return;
    }

    printf(BLUE "Your previous data:\n");
    put_customer(line[index]);

    room r[100];      // array to store lines from the file in structs
    int count_r = input_room(r);
    int index_r;
    for (int i = 0; i < count_r; i++)
    {
        if ((strcmp(r[i].room_number, room1.room_number)) == 0) // when we find the true id or true room number we will edit the reservation
        {
            index_r = i; //index of the line being changed
            room1 = r[i]; // default is no change
            break;
        }
    }
    // *********************************** taking the new inputs from user ****************************************

    printf(GREEN "--------------------------------------------------\n" RESET);
    printf(BLUE BOLD "Now enter the new value for every field: if you do not want to change a field enter f\n");
    printf(GREEN "--------------------------------------------------\n" RESET);
    printf(GREEN "\tEnter the name:\n" RESET);
    printf(YELLOW "                                                            { to back to main enter m and to exit enter e }\n" RESET);

    while(1){
        scanf("%s", new.name);
        if (strcmp(new.name, "m") == 0 || strcmp(new.name, "M") == 0)
        {
            end_of_fn();
            return;
        }
        else if (strcmp(new.name, "e") == 0 || strcmp(new.name, "E") == 0)
        {
            exit(0);
        }
        else if (strcmp(new.name, "f") == 0 || strcmp(new.name, "F") == 0)
        {
            break;
        }
        if(name_validate(new.name))
            break;

        puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
        continue;
    }
    while (1)
    {
        printf(GREEN "\tEnter the mobile number:\n" RESET);
        printf(YELLOW "                                                            { to back to main enter m and to exit enter e }\n" RESET);
        scanf("%s", new.number);
        if (strcmp(new.number, "m") == 0 || strcmp(new.number, "M") == 0)
        {
            end_of_fn();
            return;
        }
        else if (strcmp(new.number, "e") == 0 || strcmp(new.number, "E") == 0)
        {
            exit(0);
        }
        else if (strcmp(new.number, "f") == 0 || strcmp(new.number, "F") == 0)
        {
            break;
        }
        if (number_validate(new.number))
            break;

        puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
        continue;
    }

    while (1)
    {
        printf(GREEN "\tEnter the email:\n" RESET);
        printf(YELLOW "                                                            { to back to main enter m and to exit enter e }\n" RESET);
        scanf("%s", new.email);
        if (strcmp(new.email, "m") == 0 || strcmp(new.email, "M") == 0)
        {
            end_of_fn();
            return;
        }
        else if (strcmp(new.email, "e") == 0 || strcmp(new.email, "E") == 0)
        {
            exit(0);
        }
        else if (strcmp(new.email, "f") == 0 || strcmp(new.email, "F") == 0)
        {
            break;
        }
        if (email_validate(new.email))
            break;

        puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
        continue;
    }

    // *************************************** date and check it  ************************************************************

    while (1)
    {
        printf(BLUE "Enter the check-in date (dd-mm-year): \n" RESET);
        printf(YELLOW "                                                            { to back to main enter m and to exit enter e }\n" RESET);
        int no_input = scanf("%2d-%2d-%4d", &new.check_in_date.days, &new.check_in_date.months, &new.check_in_date.years);
        if (no_input != 3)
        {
            puts(YELLOW "if you want to retry date input enter any char; enter m or e or f to go to main menu or exit or do not modify");
            char tempc;
            scanf(" %c", &tempc);
            tolower(tempc);
            if (tempc == 'm')
            {
                end_of_fn();
                return;
            }
            else if (tempc == 'e')
            {
                exit(0);
            }
            else if (tempc == 'f')
            {
                break;
            }
            puts(RED "Invalid date format. Please enter in " BOLD "dd-mm-yyyy format.\n" RESET);
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;

        }
        if (date_validate(new.check_in_date))
            break;

        puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
        continue;
    }

    while(1){
        printf(BLUE "Enter the number of nights:\n" RESET);
        printf(YELLOW "                                                            { to back to main enter m and to exit enter e }\n" RESET);
        char tempc;
        scanf(" %c", &tempc);
        while(getchar() != '\n'); // clear input buffer from any chars
        tolower(tempc);
        if (tempc == 'm')
        {
            end_of_fn();
            return;
        }
        else if (tempc == 'e')
        {
            exit(0);
        }
        else if (tempc == 'f')
        {
            break;
        }
        new.no_nights = tempc - '0';
        if(new.no_nights < 1){
            puts(RED "number of nights must be greater than or equal one");
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }
        break;
    }

    // ******************************* changing the room view means reserving a new room with that view ***********************************

    char y[11]; // to save room_status
    strcpy(new.status, "unconfirmed"); // to be changed to confirmed with check-in

    while (1)
    {
        printf(BLUE "\nChoose room category\n" GREEN "\t-for SeaView enter 1\n"
                    "\t-for LakeView enter 2\n"
                    "\t-for GardenView enter 3\n" RESET);
      printf(YELLOW "                                                            { to back to main enter m and to exit enter e }\n" RESET);
        char choice;
        scanf(" %c", &choice);
        while(getchar() != '\n'); // clear input buffer from any chars
        switch (choice)
        {
        case '1':
            strcpy(y, "SeaView");
            break;
        case '2':
            strcpy(y, "LakeView");
            break;
        case '3':
            strcpy(y, "GardenView");
            break;
        case 'm':
        case 'M':
            end_of_fn();
            return;
        case 'e':
        case 'E':
            exit(0);
        case 'f':
        case 'F':
            break;
        default:
            puts(RED "Invalid input, please enter 1 or 2 or 3");
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }

        int n_i = -1;  // n_i is the index that will point to the room that will be used
        for(int i=0; i<count_r; i++){ //n_r is number of elements and not last index
            if(!strcmp( r[i].room_view ,y) && !strcmp( r[i].room_status ,"Available")){ //I cannot compare r.room_status with available using == bec. in this way the pointers will be compared
                strcpy(r[i].room_status,"Reserved");
                strcpy(r[i].room_number,r[i].room_number);
                n_i = i; // n_i is now the index that points to the room that will be used
                break;
            }
        }

        if(n_i == -1){
            puts(RED "No available room with this specifications");
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }

        strcpy(new.room_number,r[n_i].room_number);//change room numbers
        room1 = r[n_i];
        strcpy(r[index_r].room_status, "Available"); // change previous room to being available

        break;
    }

    // ***************************************** ask the user to save or not ********************************************************

    while (1)
    {
        printf(BLUE "Do you want to proceed and save the reservation?\n" GREEN "\tif yes enter y\tif no enter n\n" RESET);
        char a; // answer
        scanf(" %c", &a);
        while(getchar() != '\n'); // clear input buffer from any chars
        if (a == 'n' || a == 'N')
        {
            puts(YELLOW "all changes are discarded! ");
            end_of_fn();
            return;
        }
        if (a == 'y' || a == 'Y')
        {
            // Update the reservation data
            line[index] = new;
            //changes on room are done on array directly

        }
        puts(RED "invalid input; please enter either n or y");
        puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
    }

    // ************************************* write the updated data back to the file *********************************************

    write_reservation(line,count);
    write_room(r,count_r);

    end_of_fn();
    return;
}


/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

void cancel_reservation()
{
    int check;
    char choice = 'x';
    room r[100];
    reservation rev[100];
    char room_number[5] = {0}; // Initialize to zeros
    int i = 0, found = 0;
    int n_rev, n_r;

    printf(YELLOW "Enter m to return to main or enter e to exit at anytime\n" RESET);

    // read all reservations first
    n_rev = input_reservation(rev);
    if (n_rev == 0) {
        printf(RED "Error: No reservations found!\n" RESET);
        end_of_fn();
        return;
    }

    // get cancellation method choice
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
            }
        }
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

    // check reservation --> that it is unconfirmed
    if(!strcmp(rev[i].status, "confirmed")) {
        printf(RED "Cancellation cannot be done (check-in is confirmed)\n" RESET);
        end_of_fn();
        return;
    }

    // save??
    while(1) {
        printf(BLUE "Are you sure you want to cancel reservation (save?)\n"
               GREEN "Enter 'y' for yes or 'n' for no: " RESET);
        char answer;
        scanf(" %c", &answer);
        while (getchar() != '\n');
        if(answer == 'n' || answer == 'N') {
            printf(YELLOW "cancellation cancelled.\n" RESET);
            end_of_fn();
            return;
        }
        if(answer == 'y' || answer == 'Y')
            break;
        if(to_main(answer) == 1){
            end_of_fn();
            return;
        }
        if(to_main(answer) == 2)
            exit(0);

        printf(RED "Invalid input. Please enter 'y' or 'n'\n" RESET);
    }

    // update room status in room.txt
    n_r = input_room(r);
    if (n_r == 0) {
        printf(RED "Error: Could not read room data\n" RESET);
        end_of_fn();
        return;
    }

    int room_found = 0;
    for(int j = 0; j < n_r; j++) {
        if(!strcmp(r[j].room_number, room_number)) {
            strcpy(r[j].room_status, "Available");
            room_found = 1;
            break;
        }
    }

    if (!room_found) {
        printf(RED "Error: Room not found in room database\n" RESET);
        end_of_fn();
        return;
    }

    // remove the cancelled reservation from array
    for(int j = i; j < n_rev - 1; j++) { // i is equal to index at which room changed to available
        rev[j] = rev[j + 1];
    }
    n_rev--; // new number of structs is less by one

    // write changes back to files
    write_room(r, n_r);
    write_reservation(rev, n_rev);

    printf(GREEN "Reservation cancelled successfully!\n" RESET);
    end_of_fn();
}


#endif // RESERVATION_H_INCLUDED
