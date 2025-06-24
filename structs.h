#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

// ANSI escape sequences (\033 --> escape char in C)
#define RESET "\033[0m"
#define RED "\033[0;91m"
#define GREEN "\033[0;92m"
#define YELLOW "\033[0;93m"
#define BLUE "\033[0;94m"
#define CLEAR "\033[2J \033[1;1H" // (clear terminal and move cursor to top left)
#define BOLD "\033[1m" // Never forget to reset after use!
#define UNDERLINE "\033[4m" // Never forget to reset after use!


typedef struct
{
    int days;
    int months;
    int years;
}date;

typedef struct
{
    char username[50] ;
    char password[50] ;

}user;

typedef struct
{
    int reservation_id;
    char room_number[5]; //4  values + NULL (ex. 1001,1002,.. / 2001,2003,.. / 3001 ...)
    char status[12]; // largest word "unconfirmed" is 11 + NULL
    char name[100];
    char national_id[15]; // 14 digits only + NULL
    int no_nights;
    date check_in_date;
    char email[50];
    char number[12]; // 11 digits + NULL

}reservation;

typedef struct
{
    char room_number[5]; //4  values + NULL (ex. 1001,1002,.. / 2001,2003,.. / 3001 ...)
    char room_status[10]; // largest word "available" is 9 + NULL
    char room_view[11]; // largest word "GardenView" is 10 + NULL
    int price_per_night;

}room;


#endif // STRUCTS_H_INCLUDED
