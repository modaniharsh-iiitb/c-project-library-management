#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"

#define MAX_ATTEMPTS 5  // maximum number of attempts to enter old password

// Made by Divyam Sareen
member *__memberLogin(member members[], int noOfMembers) {
    /* A function to log in as a member. This method takes in a password
        and user ID and verifies it against the member table. If the ID exists 
        and the password matches, the user is logged in as the member with the
        given member ID. */

    while (1) {
	    int t;
	    char passwd[30];
	    printf("Enter your ID, enter -1 to exit: ");
	    scanf("%d", &t);
	    printf("Enter your password: ");
	    scanf("%s", passwd);
	    if (t == -1) {
		    member *voidMember = (member *) malloc(sizeof(member));
            voidMember->id = -1;
            return voidMember;
        }
	    for (int i = 0; i < noOfMembers; i++) {
		    if (t == members[i].id && !strcmp(passwd, members[i].password)) {
                printf("Logged in successfully.\n\n");
			    return &(members[i]);
            }
	    }
	    printf("You have entered the incorrect ID or password.\n\n");
    } 
}

// Made by Aryan Mishra
void changePassword(member *m) {
    /* A funciton to change the member's password. This method takes in the old
        password and verifies it against the current one. If they match, the librarian
        can set a new password by typing it.*/
    
    char old_password[30], new_password[30];
    int attempts_left = MAX_ATTEMPTS;

    printf("Enter old password: ");
    scanf("\n%[^\n]%*c", old_password);

    while (strcmp(old_password, m->password)) {
        attempts_left--;
        printf("Incorrect password (%d attempts left).\n\n", attempts_left);

        if (attempts_left == 0) {
            printf("Maximum attempts reached. Password change aborted.\n");
            return;
        }

        printf("Enter old password: ");
        scanf("\n%[^\n]%*c", old_password);
    }

    printf("Enter new password: ");
    scanf("\n%[^\n]%*c", new_password);
    strcpy(m->password, new_password);
    printf("Password changed successfully.\n\n");
}

// Made by Nikita Kiran
void issueBook(member *member1, book books[], int noOfBooks, char date[]) {
    /*A function to issue a book to a member, provided it has available copies.*/

    if (member1->noOfCopiesIssued == 5)
    {
        printf("You have already reached the maximum limit of issued books.\n");
        return;
    }
    int bookid;
    printf("Enter the ID of the book you want to issue (enter -1 to cancel): ");
    scanf("%d", &bookid);
    if (bookid == -1)
        return;
    book *book1 = getBookByID(books, noOfBooks, bookid);
    if (book1->id == -1) {
        printf("Invalid book ID.\n");
        return;
    }
    if (copiesAvailable(*book1) == 0) {
        printf("No copies of the book are currently available.\n");
        return;
    }
    for (int i = 0; i < book1->noOfCopies; i++) {
        if (!book1->copies[i].isIssued) {
            book1->copies[i].isIssued = 1;
            strcpy(book1->copies[i].dateIssued, date);
            strcpy(book1->copies[i].dueDate, getDueDate(date));
            book1->copies[i].memberIDIssued = member1->id;
            member1->copiesIssued[member1->noOfCopiesIssued] = &(book1->copies[i]);
            member1->noOfCopiesIssued++;
            printf("Book issued successfully.\n\n");
            return;
        }
    }
}

// Made by Nikita Kiran
void returnBook(member *member1, book books[], int noOfBooks, char currDate[]) {
    /*A function to return a book, provided the given member has issued it.*/

    int num = member1->noOfCopiesIssued;
    if (!num) {
        printf("You have no issued books.\n\n");
        return;
    }
    int bookid;
    printf("Enter the ID of the book you want to return: ");
    scanf("%d", &bookid);
    for (int i = 0; i < num; i++) {
        if (member1->copiesIssued[i]->bookID == bookid) {
            if (compareDates(member1->copiesIssued[i]->dueDate, currDate) == 2) {
                int diff = diffBtwDates(member1->copiesIssued[i]->dueDate, currDate);
                printf("This book is overdue by %d day(s). You need to pay a fine of Rs. %d.\nPay fine? (y/n): ",diff,5*diff);
                char choice;
                scanf("\n%c", &choice);
                if (choice != 'y') {
                    printf("Book not returned.\n\n");
                    return;
                }
                printf("Fine paid successfully.\n");
            }
            member1->copiesIssued[i]->isIssued = 0;
            strcpy(member1->copiesIssued[i]->dateIssued, "00/00/0000");
            strcpy(member1->copiesIssued[i]->dueDate, "00/00/0000");
            member1->copiesIssued[i]->memberIDIssued = -1;
            member1->noOfCopiesIssued--;
            for (int j = i; j < member1->noOfCopiesIssued; j++)
                member1->copiesIssued[i] = member1->copiesIssued[i+1];
            printf("Book returned successfully.\n\n");
            return;
        }
    }
    return;
}

// Made by Nikita Kiran
void displayIssuedBooks(member *member1, book books[], int noOfBooks, char currentDate[], int isLibrarianCalling) {
    /*A function to display the books issued by the current member.*/

    if (member1->noOfCopiesIssued == 0) {
        if (isLibrarianCalling) {
            printf("Member \"%s\" has no issued books.\n\n", member1->name);
            return;
        }
        printf("You have no issued books.\n\n");
        return;
    }
    int totalfine = 0;
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
            totalfine += fine;
        }
        printf("| %3d | %-50s | %-30s | %-20s %9s | Rs. %12d |\n", member1->copiesIssued[i]->bookID, getBookByID(books, noOfBooks, member1->copiesIssued[i]->bookID)->name, member1->copiesIssued[i]->dateIssued, member1->copiesIssued[i]->dueDate, overdueText, fine);
    }
    printf("+-----+----------------------------------------------------+--------------------------------+--------------------------------+------------------+\n\n");
    printf("Total fine = Rs. %d\n\n", totalfine);
}

// Made by Harsh Modani
void searchBook(book books[], int noOfBooks) {
    /*A function that allows the member to search for a member by name.
        It is reused in the librarian loops.*/

    book searchResults[100];
    int noOfResults = 0;
    char searchString[50];
    printf("Enter search keyword (title, author, genre): ");
    scanf("\n%[^\n]%*c", searchString);
    for (int i = 0; i < noOfBooks; i++) {
        if (strstr(books[i].name, searchString) || strstr(books[i].author,searchString) || strstr(books[i].genre,searchString))
            searchResults[noOfResults++]=books[i];
    }
    if (noOfResults == 0){
        printf("No such book found.\n\n");
        return;
    }
    printBookList(searchResults, noOfResults);
}

// Made by Daksh Rajesh
int __memberLoop(book books[], int noOfBooks, member *member1) {
    /*The loop that runs indefinitely when the user logs in as a member.
        It returns -1 on breaking.*/

    // The member is required to input the date at the start of the loop.
	char date[11];
    printf("Enter the date in DD/MM/YYYY format: ");
    scanf("%s", date);
    while (!isValidDate(date)) {
        printf("Invalid date.\n\n");
        printf("Enter the date in DD/MM/YYYY format: ");
        scanf("%s", date);
    }
    printf("\n");

    int option;
	while(1) {
        printf("Enter the corresponding number to do the following:\n");
        printf("1. View the list of available books\n");
        printf("2. View the list of books issued by you\n");
        printf("3. Search for a book by title, genre or author\n");
        printf("4. Issue a book\n");
        printf("5. Return a book\n");
        printf("6. Change your password\n");
        printf("0. Exit\n> ");

		scanf("%d", &option);

	    if (option == 1) // views list of available books
            printBookList(books, noOfBooks);

		else if (option == 2) // allows members to view list of copies issued, due dates and fine if any
            displayIssuedBooks(member1, books, noOfBooks, date, 0);

        else if (option == 3) // search for a book by name, author or genre
            searchBook(books, noOfBooks);

        else if (option == 4)  // allows members to issue books            
            issueBook(member1, books, noOfBooks, date);

        else if (option == 5)  // allows members to return books
            returnBook(member1, books, noOfBooks, date);

		else if (option == 6) // allows members to change password
            changePassword(member1);

        else if (option == 0) // exit
            return -1;

		else // option is any other number
			printf("No such option\n\n");
	}

}