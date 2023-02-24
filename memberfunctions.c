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

char *getNextDate(char date[])
{
    int day = (date[0] - '0') * 10 + date[1] - '0';
    int month = (date[3] - '0') * 10 + date[4] - '0';
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');
    day = day + 1;
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
    char *nextDate = malloc(11 * sizeof(char));
    nextDate[2] = '/';
    nextDate[5] = '/';
    nextDate[0] = day / 10 + '0';
    nextDate[1] = day % 10 + '0';
    nextDate[3] = month / 10 + '0';
    nextDate[4] = month % 10 + '0';
    nextDate[6] = year / 1000 + '0';
    year = year % 1000;
    nextDate[7] = year / 100 + '0';
    year = year % 100;
    nextDate[8] = year / 10 + '0';
    nextDate[9] = year % 10 + '0';
    nextDate[10] = '\0';
    return nextDate;
}

int compareDates(char date1[], char date2[])
// returns 0 if both are equal; 1 if first date is greater; 2 if second date is greater
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

int diffBtwDates(char date1[], char date2[])
// assumes date1 is less than or equal to date2
{
    int i = 0;
    char currDate[11];
    strcpy(currDate, date1);
    while (1)
    {
        if (!compareDates(currDate, date2))
            return i;
        strcpy(currDate, getNextDate(currDate));
        i++;
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
            strcpy(book1->copies[i].dueDate, getDueDate(date));
            member1->copiesIssued[member1->noOfCopiesIssued] = book1->copies[i];
            member1->noOfCopiesIssued++;
            return 0;
        }
    }
}

int returnBook(struct member *member1, int bookid, struct book books[], int noOfBooks, char currDate[])
{
    // returns 0 if successfully returned, -1 otherwise
    int num = member1->noOfCopiesIssued;
    for (int i = 0; i < num; i++)
    {
        if (member1->copiesIssued[i].bookID == bookid)
        {
            if (compareDates(member1->copiesIssued[i].dueDate, currDate) != 2)
            {
                member1->copiesIssued[i].isIssued = 0;
                strcpy(member1->copiesIssued[i].dateIssued, "");
                strcpy(member1->copiesIssued[i].dueDate, "");
                member1->noOfCopiesIssued--;
                return 0;
            }
            int diff=diffBtwDates(member1->copiesIssued[i].dueDate, currDate);
            printf("This book is overdue by %d days. You need to pay a fine of Rs.%d.\nPay fine(y/n) :",diff,5*diff);
            char choice;
            scanf("%c",&choice);
            if (choice=='y')
            {
                printf("Fine paid successfully!\n");
                member1->copiesIssued[i].isIssued = 0;
                strcpy(member1->copiesIssued[i].dateIssued, "");
                strcpy(member1->copiesIssued[i].dueDate, "");
                member1->noOfCopiesIssued--;
                return 0;
            }
        }
    }
    return -1;
}

void displayIssuedBooks(struct member *member1, struct book books[], int noOfBooks, char currentDate[])
{
    int totalfine= 0;
    printf("+-----+----------------------------------------------------+--------------------------------+--------------------------------+------------------+\n");
    printf("| ID  | Name                                               | Date of Issue                  | Due Date                       | Fine Due         |\n");
    printf("+-----+----------------------------------------------------+--------------------------------+--------------------------------+------------------+\n");
    for (int i = 0; i < member1->noOfCopiesIssued; i++)
    {
        char *overdueText = "";
        int fine = 0;
        if (compareDates(member1->copiesIssued[i].dueDate, currentDate) == 2)
        {
            strcpy(overdueText, "Overdue");
            fine = 5 * diffBtwDates(member1->copiesIssued[i].dueDate, currentDate);
            totalfine+=fine;
        }
        printf("| %3d | %50s | %30s | %20s %9s | Rs. %12d |\n", member1->copiesIssued[i].bookID, getBookByID(books, noOfBooks, member1->copiesIssued[i].bookID)->name, member1->copiesIssued[i].dateIssued, member1->copiesIssued[i].dueDate, overdueText, fine);
    }
    printf("+-----+----------------------------------------------------+--------------------------------+--------------------------------+------------------+\n");
    printf("Total fine= Rs.%d\n",totalfine);
}