#ifndef VALIDATION_H_INCLUDED
#define VALIDATION_H_INCLUDED

#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int date_validate (date x);
int email_validate (char e[]);
int national_id_validate (char n[]);
int number_validate (char n[]);
int name_validate(char n[]);

/*---------------------------------------------------------------------------------------------------------------------*/

int date_validate(date x)
{
    time_t currentTime = time(NULL);
    if (currentTime == (time_t)-1) {
        printf(RED "System date and time ERROR (reading error). Try again later\n");
        return 0;  // time() sometimes return -1 if a problem occurred
    }

    struct tm *formattedTime = localtime(&currentTime);
    if (formattedTime == NULL) {  // NULL check, if localtime() failed to work correctly
        printf(RED "System date and time ERROR (format error). Try again later\n");
        return 0;
    }

    // Check the year first
    if(x.years < (formattedTime->tm_year + 1900)) {
        puts(RED "Invalid year - past date");
        return 0;
    }

    // Check month (1-12) and is not past actual date
    if(x.months < 1 || x.months > 12){
        puts(RED "Invalid month");
        return 0;
    }

    // Check days based on month and is not past actual date
    switch(x.months) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if(x.days < 1 || x.days > 31)
                {puts(RED "Invalid day"); return 0;}
        case 4: case 6: case 9: case 11:
            if(x.days < 1 && x.days > 30)
                {puts(RED "Invalid day"); return 0;}
        case 2:
            if(x.days < 1 && x.days > 29)
                {puts(RED "Invalid day"); return 0;}
    }

    if(x.years == (formattedTime->tm_year + 1900)){ // if same year restrict month
        if(x.months < formattedTime->tm_mon + 1)  // +1 to tm_mon because it reads months from 0 to 11!
            {puts(RED "Invalid month - past date"); return 0;}
        if(x.months == formattedTime->tm_mon + 1){
            if(x.days < formattedTime->tm_mday)
                {puts(RED "Invalid day - past date"); return 0;}
        }
    }

    return 1;
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

int email_validate (char e[]) // email[50]
{
    if(strlen(e) > 49){
            puts(RED "E-mail exceeded limit!");
            return 0;
    }// validate limit exceed even if input is correct so user is not fooled that the whole thing is going to be saved

    int i=0; // i is the index
    if(!( isalnum(e[i]) || isdigit(e[i]) )){
        printf(RED "Invalid: only " BOLD "alphanumeric" RESET RED " and " BOLD "digits" RESET RED " are allowed for " BOLD "first and last" RESET RED " characters\n");
        return 0;
    }
    // if first char is not alpha-numeric or a digit return 0

    int flag_at = 0, flag_dot = 0; // flags to make sure . and @ are present at least once, and no more than one @, and no consecutive . (ex: ...);

    for(i=1 ; e[i] != '\0' && i<50 ; i++){
        if(!( isalnum(e[i]) || isdigit(e[i]) || e[i]=='_' || e[i]=='-' ||  e[i] == '.' || e[i] == '@')){
           printf(RED "%c is an invalid character!\n", e[i]);
           return 0;
        }
        if(e[i] == '@'){
            if(flag_at){
                puts(RED "Invalid: you can't have " BOLD "more than one " BOLD "@!" RESET);
                return 0;
            }
            if(e[i+1] == '.'){
                puts(RED "Invalid: you can't have "BOLD "dots (.) directly after @ (write domain)" RESET);
                return 0;
            }
            flag_at=1;
        }
        else if(e[i] == '.'){
            if(e[i-1] == '.'){
                puts(RED "Invalid: you can't have " BOLD "consecutive " BOLD "dots (.)" RESET);
                return 0;
            }
        flag_dot = 1;
        }
    }
    if( e[i-1] == '_' || e[i-1] == '-' || e[i-1] == '.' || e[i-1] == '@'){
        printf(RED "Invalid: only " BOLD "alphanumeric" RESET RED " and " BOLD "digits" RESET RED " are allowed for " BOLD "first and last" RESET RED " characters\n");
        return 0;
    }
    if(!flag_at || !flag_dot){
        puts(RED "Invalid: you need at least one " BOLD "." RESET RED " before .com and at least one " BOLD "@" RESET);
        return 0;
    }

    return 1;
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

int national_id_validate (char n[]) // n[15]
{
    if(strlen(n) < 14){
            puts(RED "Invalid (too short): National ID is only " BOLD "14 digits!" RESET);
            return 0;
    }
    if(strlen(n) > 14){
            puts(RED "Invalid (too long): National ID is only " BOLD "14 digits!" RESET);
            return 0;
    } // validate limits exceed

    for(int i=0; i<14; i++){ //14 not 15 to not include \0
        if(!isdigit(n[i])){
            puts(RED "Invalid national id; only " BOLD "digits" RESET RED " are valid");
            return 0;
        }
    }
    return 1;
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

int number_validate (char n[]) //n[12]
{
    if(strlen(n) != 11){
            puts(RED "Phone number is only " BOLD "11 digits!" RESET);
            return 0;
    } // validate limit exceed

    if(n[0] != '0'){
        puts(RED "Invalid: only " BOLD "0" RESET RED " is accepted for the " BOLD "first digit" RESET);
        return 0;
    }
    if(n[1] != '1'){
        puts(RED "Invalid: only " BOLD "1" RESET RED " is accepted for the " BOLD "second digit" RESET);
        return 0;
    }
    for(int i=2 ; i<11 ; i++){ //11 not 12 to avoid \0
        if(!isdigit(n[i])){
            puts(RED "Invalid: only " BOLD "digits" RESET RED " are accepted");
            return 0;
        }
    }
    return 1;
}

/*$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$*/

int name_validate(char n[]) //n[100]
{
    if(strlen(n)<=2){
        puts(RED "Name too short!");
        return 0;
    }
    if(strlen(n) > 99){
        puts(RED "Name exceeded limit!");
        return 0;
    } // validate limit exceed

    int i=0;
    for(i=0 ; i<(int)strlen(n) && n[i]!='\0' ; i++){
        if(!isalpha(n[i]) && n[i]!=' '){
            puts(RED "Invalid: only include " BOLD "alphabetical characters" RESET RED " and " BOLD "spaces" RESET);
            return 0;
        }
    }
    return 1;
}


#endif // VALIDATION_H_INCLUDED
