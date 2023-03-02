#include <stdlib.h>
#include <string.h>

#include "utils.h"

int issueBook(struct member *member1, int bookID, struct book books[], int noOfBooks, char date[]) {
    // returns 0 if successfully issued, -1 otherwise
    if (member1->noOfCopiesIssued == 5)
    {
        printf("You have already reached the maximum limit of issued books!\n");
        return -1;
    }
    struct book *book1 = getBookByID(books, noOfBooks, bookID);
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

int returnBook(struct member *member1, int bookID, struct book books[], int noOfBooks, char currDate[]) {
    // returns 0 if successfully returned, -1 otherwise
    int num = member1->noOfCopiesIssued;
    for (int i = 0; i < num; i++) {
        if (member1->copiesIssued[i].bookID == bookID) {
            if (compareDates(member1->copiesIssued[i].dueDate, currDate) != 2) {
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
            if (choice=='y') {
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

void displayIssuedBooks(struct member *member1, struct book books[], int noOfBooks, char currentDate[]) {
    int totalfine= 0;
    printf("+-----+----------------------------------------------------+--------------------------------+--------------------------------+------------------+\n");
    printf("| ID  | Name                                               | Date of Issue                  | Due Date                       | Fine Due         |\n");
    printf("+-----+----------------------------------------------------+--------------------------------+--------------------------------+------------------+\n");
    for (int i = 0; i < member1->noOfCopiesIssued; i++) {
        char *overdueText = "";
        int fine = 0;
        if (compareDates(member1->copiesIssued[i].dueDate, currentDate) == 2) {
            strcpy(overdueText, "Overdue");
            fine = 5 * diffBtwDates(member1->copiesIssued[i].dueDate, currentDate);
            totalfine+=fine;
        }
        printf("| %3d | %50s | %30s | %20s %9s | Rs. %12d |\n", member1->copiesIssued[i].bookID, getBookByID(books, noOfBooks, member1->copiesIssued[i].bookID)->name, member1->copiesIssued[i].dateIssued, member1->copiesIssued[i].dueDate, overdueText, fine);
    }
    printf("+-----+----------------------------------------------------+--------------------------------+--------------------------------+------------------+\n");
    printf("Total fine= Rs.%d\n",totalfine);
}