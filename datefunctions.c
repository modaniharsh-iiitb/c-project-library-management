#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"

// Made by Divyam Sareen
int isLeapYear(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        return 1;
    return 0;
}

// Made by Divyam Sareen
void dateConverter(char *date, int *day, int *month, int *year) {
    /*A function that inflates the values of three integers - day, month and year -
        given a string date input*/

    *day = (date[0]-'0') * 10 + (date[1]-'0');
    *month = (date[3]-'0') * 10 + (date[4]-'0');
    *year = (date[6]-'0') * 1000 + (date[7]-'0') * 100 + (date[8]-'0') * 10 + (date[9]-'0');
}

// Made by Divyam Sareen
int between0and9(char a) {
    /*A function that checks if a given character is a numberical 
        value between '0' and '9'.*/

    return (a >= '0' && a <= '9');
}

// Made by Divyam Sareen
int isValidDate(char date[]) {
    /* A function that checks if a given date is valid. */

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5)
            continue;
        if (!between0and9(date[i]))
            return 0;
    }
    
    int day, month, year;
    dateConverter(date, &day, &month, &year);
    if (month > 12)
        return 0;
    int maxDays=31;
    switch (month) {
        case 2:
            maxDays = 28;
            if (isLeapYear(year))
                maxDays++;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            maxDays = 30;
    }
    if (day > maxDays) {
        return 0;
    }
    return 1;
}

// Made by Nikita Kiran
char *getDueDate(char dateIssued[]) {
    /* A function that calculates the due date of a book given the issue date.
        The due date is 7 days from the date of issue.*/

    return getNextDate(dateIssued, 7);
}

// Made by Nikita Kiran
char *getNextDate(char date[], int n) {
    /* A function that calculates the date n days after the given date.*/

    int day, month, year;
    dateConverter(date, &day, &month, &year);

    day = day + n;
    int numOfDays = 31;
    switch (month) {
        case 2:
            numOfDays = 28;
            if (isLeapYear(year))
                numOfDays++;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            numOfDays = 30;
    }
    if (day > numOfDays) {
        day = day - numOfDays;
        month++;
    }
    if (month > 12) {
        month = month - 12;
        year++;
    }
    char *nextDate = malloc(11 * sizeof(char));
    sprintf(nextDate, "%02d/%02d/%04d", day, month, year);

    return nextDate;
}

// Made by Nikita Kiran
int compareDates(char date1[], char date2[]) {
    /* A function that compares the two given dates. It returns 0 if both are equal,
       1 if date1 is greater and 2 if date2 is greater.*/ 

    int day1, day2, month1, month2, year1, year2;
    dateConverter(date1, &day1, &month1, &year1);
    dateConverter(date2, &day2, &month2, &year2);

    if (year1 > year2)
        return 1;
    else if (year2 > year1)
        return 2;
    else {
        if (month1 > month2)
            return 1;
        else if (month2 > month1)
            return 2;
        else {
            if (day1 > day2)
                return 1;
            else if (day2 > day1)
                return 2;
            else
                return 0;
        }
    }
}

// Made by Nikita Kiran
int diffBtwDates(char date1[], char date2[]) {
    /* A function that calculates the number of days between two given dates.
        It assumes that date1 is less than or equal to date2, and the arguments
        in the rest of the code are passed accordingly.*/

    int i = 0;
    char currDate[11];
    strcpy(currDate, date1);
    while (1) {
        if (!compareDates(currDate, date2))
            return i;
        strcpy(currDate, getNextDate(currDate, 1));
        i++;
    }
}
