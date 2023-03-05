#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"

#define MAX_ATTEMPTS 5  // maximum number of attempts to enter old password

struct member __memberLogin(struct member members[], int noOfMembers) {
    // returns -1 if the member wants to exit without logging in, 0 if they log in successfully
    while (1) {
	    int t;
	    char passwd[30];
	    printf("Enter your ID, enter -1 to exit: ");
	    scanf("%d", &t);
	    printf("Enter your password: ");
	    scanf("%s", passwd);
	    if (t == -1) {
		    struct member voidMember;
            voidMember.id = -1;
            return voidMember;
        }
	    for (int i = 0; i < noOfMembers; i++) {
		    if (t == members[i].id && !strcmp(passwd, members[i].password))
			    return members[i];
	    }
	    printf("You have entered the incorrect ID or password.\n\n");
    } 
}

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
            member1->copiesIssued[member1->noOfCopiesIssued] = &(book1->copies[i]);
            member1->noOfCopiesIssued++;
            return 0;
        }
    }
}

int returnBook(struct member *member1, int bookID, struct book books[], int noOfBooks, char currDate[]) {
    // returns 0 if successfully returned, -1 otherwise
    int num = member1->noOfCopiesIssued;
    for (int i = 0; i < num; i++) {
        if (member1->copiesIssued[i]->bookID == bookID) {
            if (compareDates(member1->copiesIssued[i]->dueDate, currDate) != 2) {
                member1->copiesIssued[i]->isIssued = 0;
                strcpy(member1->copiesIssued[i]->dateIssued, "");
                strcpy(member1->copiesIssued[i]->dueDate, "");
                member1->noOfCopiesIssued--;
                return 0;
            }
            int diff=diffBtwDates(member1->copiesIssued[i]->dueDate, currDate);
            printf("This book is overdue by %d days. You need to pay a fine of Rs.%d.\nPay fine(y/n) :",diff,5*diff);
            char choice;
            scanf("%c",&choice);
            if (choice=='y') {
                printf("Fine paid successfully!\n");
                member1->copiesIssued[i]->isIssued = 0;
                strcpy(member1->copiesIssued[i]->dateIssued, "");
                strcpy(member1->copiesIssued[i]->dueDate, "");
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
        char *overdueText = (char *) malloc(9*sizeof(char));
        strcpy(overdueText, "");
        int fine = 0;
        if (compareDates(member1->copiesIssued[i]->dueDate, currentDate) == 2) {
            strcpy(overdueText, "Overdue");
            fine = 5 * diffBtwDates(member1->copiesIssued[i]->dueDate, currentDate);
            totalfine+=fine;
        }
        printf("| %3d | %50s | %-30s | %-20s %9s | Rs. %12d |\n", member1->copiesIssued[i]->bookID, getBookByID(books, noOfBooks, member1->copiesIssued[i]->bookID)->name, member1->copiesIssued[i]->dateIssued, member1->copiesIssued[i]->dueDate, overdueText, fine);
    }
    printf("+-----+----------------------------------------------------+--------------------------------+--------------------------------+------------------+\n");
    printf("Total fine= Rs.%d\n",totalfine);
}

void changePassword(struct member *m) {
    // to change password
    
    char old_password[30], new_password[30];
    int attempts_left = MAX_ATTEMPTS;  // initialize attempts left to max

    // prompt user to enter old password
    printf("Enter old password: ");
    fgets(old_password, sizeof(old_password), stdin);

    // remove trailing newline character from password
    old_password[strcspn(old_password, "\n")] = '\0';

    // loop until correct old password is entered or maximum attempts reached
    while (strcmp(old_password, m->password) != 0) {
        attempts_left--;  // decrement attempts left
        printf("Incorrect password (%d attempts left).\n\n", attempts_left);

        // check if maximum attempts reached
        if (attempts_left == 0) {
            printf("Maximum attempts reached. Password change aborted.\n");
            return;  // exit function without changing password
        }

        // prompt user to enter old password again
        printf("Enter old password: ");
        fgets(old_password, sizeof(old_password), stdin);

        // remove trailing newline character from password
        old_password[strcspn(old_password, "\n")] = '\0';
    }

    // if correct old password entered, prompt user to enter new password
    printf("Enter new password: ");
    fgets(new_password, sizeof(new_password), stdin);
    // remove trailing newline character from password
    new_password[strcspn(new_password, "\n")] = '\0';
    // update password in member struct with new password
    strcpy(m->password, new_password);
    printf("Password changed successfully.\n");
}

void search(struct book books[], int noOfBooks){
    struct book searchResults[100];
    int noOfResults=0;
    char searchString[50];
    printf("Enter search keyword (title, author, genre): ");
    scanf("%s",searchString);
    for (int i=0;i<noOfBooks;i++){
        if(strstr(books[i].name,searchString)!=NULL || strstr(books[i].author,searchString)!=NULL || strstr(books[i].genre,searchString)!=NULL)
            searchResults[noOfResults++]=books[i];
    }
    printBookList(searchResults,noOfResults);
}

int __memberLoop(struct book books[], int noOfBooks, struct member member1) {
    // returns -1 to break
		
    int option;
	while(1) {
        printf("Enter the corresponding number to do the following:\n");
        printf("1. Print the list of available books\n");
        printf("2. View the list of books issued by you\n");
        printf("3. Issue a book\n");
        printf("4. Return a book\n");
        printf("5. Search for a book by title, genre or author\n");
        printf("6. Change your password\n");
        printf("7. Exit\n> ");

		scanf("%d", &option);
	    if (option == 1) // views list of available books
            printBookList(books, noOfBooks);
		else if (option == 2) { // allows members to view list of copies issued, due dates and fine if any
            char date[11];
            int day, month, year;
            printf("Enter the date in DD/MM/YYYY format: ");
            scanf("%d/%d/%d", &day, &month, &year);
            sprintf(date, "%02d/%02d/%4d", day, month, year);
            displayIssuedBooks(&member1, books, noOfBooks, date);
        } else if (option == 3) { // allows members to issue books
            int bookid;
            printf("Enter the ID of the book you want to issue: ");
            scanf("%d", &bookid);
            char date[11];
            int day, month, year;
            printf("Enter the date in DD/MM/YYYY format: ");
            scanf("%d/%d/%d", &day, &month, &year);
            sprintf(date, "%02d/%02d/%4d", day, month, year);
            issueBook(&member1, bookid, books, noOfBooks, date);
		} else if (option == 4) { // allows members to return books
            int bookid;
            printf("Enter the ID of the book you want to return: ");
            scanf("%d", &bookid);
            char date[11];
            int day, month, year;
            printf("Enter the date in DD/MM/YYYY format: ");
            scanf("%d/%d/%d", &day, &month, &year);
            sprintf(date, "%02d/%02d/%4d", day, month, year);
            returnBook(&member1, bookid, books, noOfBooks, date);
		}
		else if (option == 6) // allows members to change password
            changePassword(&member1);
        else if (option == 7) // exit
            return -1;
        else if (option == 5) { // search for a book by name, author or genre
            search(books,noOfBooks);
        }
		else // option is any other number
			printf("No such option\n");
	}

}