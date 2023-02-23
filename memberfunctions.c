#include <stdlib.h>
#include <string.h>

#include "member.h"
#include "book.h"

int isLeapYear(int year)
{
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        return 1;
    return 0;
}

char *getDueDate(char dateIssued[])
{
    int day = (dateIssued[0] - '0') * 10 + dateIssued[1] - '0';
    int month = (dateIssued[3] - '0') * 10 + dateIssued[4] - '0';
    int year = (dateIssued[6] - '0') * 1000 + (dateIssued[7] - '0') * 100 + (dateIssued[8] - '0') * 10 + (dateIssued[9] - '0');
    day = day + 7;
    int numOfDays = 31;
    switch (month)
    {
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
    if (day > numOfDays)
    {
        day = day - numOfDays;
        month++;
    }
    if (month > 12)
    {
        month = month - 12;
        year++;
    }
    char *dueDate = malloc(11 * sizeof(char));
    dueDate[2] = '/';
    dueDate[5] = '/';
    dueDate[0] = day / 10 + '0';
    dueDate[1] = day % 10 + '0';
    dueDate[3] = month / 10 + '0';
    dueDate[4] = month % 10 + '0';
    dueDate[6] = year / 1000 + '0';
    year = year % 1000;
    dueDate[7] = year / 100 + '0';
    year = year % 100;
    dueDate[8] = year / 10 + '0';
    dueDate[9] = year % 10 + '0';
    dueDate[10] = '\0';
    return dueDate;
}

int compareDates(char date1[], char date2[])
{
    int day1 = (date1[0] - '0') * 10 + date1[1] - '0';
    int month1 = (date1[3] - '0') * 10 + date1[4] - '0';
    int year1 = (date1[6] - '0') * 1000 + (date1[7] - '0') * 100 + (date1[8] - '0') * 10 + (date1[9] - '0');
    int day2 = (date2[0] - '0') * 10 + date2[1] - '0';
    int month2 = (date2[3] - '0') * 10 + date2[4] - '0';
    int year2 = (date2[6] - '0') * 1000 + (date2[7] - '0') * 100 + (date2[8] - '0') * 10 + (date2[9] - '0');
    if (year1 > year2)
        return 1;
    else if (year2 > year1)
        return 2;
    else
    {
        if (month1 > month2)
            return 1;
        else if (month2 > month1)
            return 2;
        else
        {
            if (day1 > day2)
                return 1;
            else if (day2 > day1)
                return 2;
            else
                return 0;
        }
    }
}

int issueBook(struct member *member1, int bookid, struct book books[], int noOfBooks, char date[])
{
    // returns 0 if successfully issued, -1 otherwise
    if (member1->noOfCopiesIssued == 5)
    {
        printf("You have already reached the maximum limit of issued books!\n");
        return -1;
    }
    struct book *book1 = getBookByID(books, noOfBooks, bookid);
    if (copiesAvailable(*book1) == 0)
    {
        printf("No copies of the book are currently available!\n");
        return -1;
    }
    for (int i = 0; i < book1->noOfCopies; i++)
    {
        if (!book1->copies[i].isIssued)
        {
            book1->copies[i].isIssued = 1;
            strcpy(book1->copies[i].dateIssued, date);
            strcpy(book1->copies[i].dueDate,getDueDate(date));
            member1->copiesIssued[member1->noOfCopiesIssued] = book1->copies[i];
            member1->noOfCopiesIssued++;
            return 0;
        }
    }
}