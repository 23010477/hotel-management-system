#include <stdio.h>
/* there is 2 headers used inside other headers
structs.h and basicio.c + basicio.h */
#include "reservation.h"
#include "checkio.h"
#include "view.h"

int LogIn();

int main()
{
    char choice = 'n';
    while (1)
    {
        puts(BLUE "Login ... enter 1\n"
                "exit program ... enter 0" RESET);
        scanf(" %c", &choice);
        while (getchar() != '\n')
            ; // remove any extra buffer input of chars
        if (choice == '0')
        {
            return 0;
        }
        if (choice != '1')
        {
            puts(RED "Enter 1 or 0 only");
            puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            continue;
        }
        choice = LogIn();
        if (choice)
        {
            break;
        }
    }

    puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
    while (1)
    {
        printf(GREEN "Enter\t" BLUE "Function\n\n" GREEN "  1  \t" BLUE "New Reservation\n" GREEN "  2  \t" BLUE "Check-in\n" GREEN "  3  \t" BLUE "Cancel a Reservation\n" GREEN "  4  \t" BLUE "Check-out\n" GREEN "  5  \t" BLUE "Check Available Rooms\n" GREEN "  6  \t" BLUE "View Customer Details\n" GREEN "  7  \t" BLUE "Edit a Reservation\n" GREEN "  8  \t" BLUE "Query (search)\n" GREEN "  9  \t" BLUE "Reservation Report\n" GREEN "  s  \t" BLUE "view reservation (sorted)\n" YELLOW "  0  \texit program\n" RESET);

        char choice = 'n';
        scanf(" %c", &choice);
        getchar();
        switch (choice)
        {
        case '1':
            reserve();
            break;
        case '2':
            check_in();
            break;
        case '3':
            cancel_reservation();
            break;
        case '4':
            check_out();
            break;
        case '5':
            rooms_availability();
            break;
        case '6':
            view_customer_details();
            break;
        case '7':
            edit_reservation();
            break;
        case '8':
            Query();
            break;
        case '9':
            reservation_report();
            break;
        case 's':
            print_sorted();
            break;
        case '0':
            exit(0);
            break;
        default:
            puts(RED "Invalid choice, " UNDERLINE "choose from 0 to 10" RESET);
            puts(GREEN "# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
            break;
        }
    }

    return 0;
}

int LogIn()
{
    user x;
    int i, t1, t2;
    int lines = 1;

    FILE *f1;
    f1 = fopen("users.txt", "r");
    if (f1 == NULL)
    { // to test the file opened or not.
        printf(RED "Error opening file users.txt");
        return 0;
    }

    char name[50], pass[50];

    printf(BLUE "Enter user name: " RESET);
    fgets(name, 60, stdin); // extra allowance of chars to check number of chars
    // if I restricted fgets to correct value: will not detect error
    name[strcspn(name, "\n")] = '\0'; // replace \n with \0 only if found (strcspn returns index of the first encounter of \n or \0 in this case)
    if (strlen(name) >= 50)
    {
        puts(RED "username is too long");
        puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
        fclose(f1);
        return 0;
    }

    printf(BLUE "\nEnter user password: " RESET);
    fgets(pass, 60, stdin); // extra allowance of chars to check number of chars
    // if I restricted fgets to correct value: will not detect error
    pass[strcspn(pass, "\n")] = '\0';
    if (strlen(pass) >= 50)
    {
        puts(RED "password is too long");
        puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
        fclose(f1);
        return 0;
    }

    char s;
    while ((s = fgetc(f1)) != EOF)
    { // calculate the number of lines.
        if (s == '\n')
            lines++;
    }

    rewind(f1); // resets position for start of file.
    for (i = 0; i < lines; i++)
    {
        fscanf(f1, "%s", x.username);
        fscanf(f1, "%s", x.password);
        t1 = strcmp(name, x.username);
        t2 = strcmp(pass, x.password);
        if (t1 == 0 && t2 == 0)
        {
            fclose(f1);
            printf(GREEN "accessed successfully\n");
            return 1;
        }
    }
    puts(RED "Incorrect username or password!" RESET);
    puts(GREEN "\n# -$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$- #\n");
    fclose(f1);
    return 0;
}