#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define MAX_ATTEMPTS 5

// Made by Divyam Sareen
int __librarianLogin(char passwd[]) {
    /* A function to log in as the librarian. This method takes in a password
        and verifies it against the current one. If they match, the user is
        logged in as the librarian. */

    while (1) {
        char s[30];
        printf("Enter the password, enter -1 to exit: ");
        scanf("%s", s);

        if (!strcmp(s, "-1"))
            return -1;
        
        if (!strcmp(s, passwd)) {
            printf("Logged in successfully.\n\n");
            return 0;
        }
        printf("You have entered the incorrect password.\n\n");
    }
}

// Made by Aryan Mishra
void changeLibrarianPassword(char passwd[]) {
    /* A function to change the librarian's password. This method takes in the old
        password and verifies it against the current one. If they match, the librarian
        can set a new password by typing it. */
    
    char old_password[30], new_password[30];
    int attempts_left = MAX_ATTEMPTS;

    printf("Enter old password: ");
    scanf("\n%[^\n]%*c", old_password);

    while (strcmp(old_password, passwd)) {
        printf("Incorrect password (%d attempts left).\n\n", attempts_left--);

        if (!attempts_left) {
            printf("Maximum attempts reached. Password change aborted.\n\n");
            return;
        }

        printf("Enter old password: ");
        scanf("\n%[^\n]%*c", old_password);
    }

    printf("Enter new password: ");
    scanf("\n%[^\n]%*c", new_password);
    strcpy(passwd, new_password);
    printf("Password changed successfully.\n\n");
}

// Made by Nikita Kiran
void callAddBook(book books[], int *noOfBooks) {
    /*A function that allows the librarian to either add a new book altogether,
        or add a copy of a new book.*/
    
    int choice;
    printf("Enter the corresponding number to do the following:\n");
    printf("1. Add a new book\n");
    printf("2. Add copies to an existing book\n> ");
    scanf("\n%d", &choice);
    if (choice == 1) {
        // new book to be added to the collection
        book newBook;          
        printf("Enter the book ID: ");
        scanf("\n%d", &(newBook.id));
        while (newBook.id <= 0) {
            printf("Invalid book ID; book ID must be positive.\n");
            printf("Enter the book ID: ");
            scanf("\n%d", &(newBook.id));
        }
        if (getBookByID(books, *noOfBooks, newBook.id)->id != -1) {
            printf("Book with id %d already exists.\n\n", newBook.id);
            return;
        }
        printf("Enter the title of the book: ");
        scanf("\n%[^\n]%*c", newBook.name);
        printf("Enter the author of the book: ");
        scanf("\n%[^\n]%*c", newBook.author);
        printf("Enter the genre of the book: ");
        scanf("\n%[^\n]%*c", newBook.genre);

        // no more than 5 copies of a book can exist in the library
        printf("Enter the number of copies of the book: ");
        scanf("\n%d", &(newBook.noOfCopies));
        if (newBook.noOfCopies > 5) {
            printf("Too many copies. Adding only 5 copies instead.\n");
            newBook.noOfCopies = 5;
        }

        for (int i = 0; i < newBook.noOfCopies; i++)
            newBook.copies[i] = (copy) {.bookID = newBook.id, .copyID = (i+1), .isIssued = 0, .dateIssued = "00/00/0000", .dueDate = "00/00/0000", .memberIDIssued = -1};

        int a = addBook(books, noOfBooks, newBook);
        if (!a)
            printf("Successfully added %d copies of the book \"%s\" to the collection.\n\n", newBook.noOfCopies, newBook.name);
        else
            printf("Unsuccessful\n\n");
    } else if (choice == 2) {
        int id;
        printBookList(books, *noOfBooks);
        printf("Enter the ID of the book: ");
        scanf("%d", &id);
        book *b = getBookByID(books, *noOfBooks, id);

        if(b->id == -1) {
            printf("Book with ID %d does not exist.\n\n", b->id);
            return;
        }

        int newCopyID;
        printf("Enter the new copy ID that is to be added: ");
        scanf("%d", &newCopyID);
        for(int i = 0; i < b->noOfCopies; i++){
            if (b->copies[i].copyID == newCopyID){
                printf("Copy of book with id %d already exists.\n\n", newCopyID);
                return;
            }
        }
        int a = addCopy(b, newCopyID);
        if (!a)
            printf("Successfully added a copy of the book \"%s\".\n\n", b->name);
        else
            printf("Unsuccessful\n\n");
    } else
        printf("Invalid option.\n\n");
}

// Made by Harsh Modani
void callRemoveBook(book books[], int *n, member members[], int noOfMembers) {
    /*A function that allows the librarian to either remove a book altogether,
        or remove a single copy of a new book.*/
    
    int choice;
    printf("Enter the corresponding number to do the following:\n");
    printf("1. Remove a book\n");
    printf("2. Remove a copy of a book\n> ");
    scanf("\n%d", &choice);
    if (choice == 1) {
        int id;
        
        // book to be removed from the collection
        printf("Enter the ID of the book to be removed: ");
        scanf("\n%d", &id);
        book *book1 = getBookByID(books, *n, id);
        if (!removeBook(books, n, id))
            printf("Successfully removed book \"%s\".\n\n", book1->name);
        else
            printf("Unsuccessful\n\n");
    } else if (choice == 2) {
        int id;

        // finding the book of which a copy is to be added
        printf("Enter the ID of the book: ");
        scanf("%d", &id);
        book *b;
        b = getBookByID(books, *n, id);
        if(b->id == -1) {
            printf("Book with ID %d does not exist.\n\n", id);
            return;
        }

        // new copy ID for the copy to be added
        int copyID;
        printf("Enter the ID of the copy that is to be removed: ");
        scanf("%d", &copyID);
        if (!removeCopy(books, n, b, members, noOfMembers, copyID))
            printf("Successfully removed the copy.\n\n");
        else
            printf("Unsuccessful\n\n");
    } else 
        printf("Invalid option.\n\n");
    
}

// Made by Harsh Modani
void addMember(member members[], int *noOfMembers) {
    /*A function that allows the librarian to add a new member.*/

    if (*noOfMembers >= 100) {
        printf("Too many members added already.\n\n");
        return;
    }
    member newMember;
    printf("Enter member ID: ");
    scanf("%d", &(newMember.id));
    while (newMember.id <= 0) {
            printf("Invalid book ID; book ID must be positive.\n");
            printf("Enter the book ID: ");
            scanf("\n%d", &(newMember.id));
    }
    if (getMemberByID(members, *noOfMembers, newMember.id)->id != -1) {
        printf("Member with id %d already exists.\n\n", newMember.id);
        return;
    }
    printf("Enter member name: ");
    scanf("\n%[^\n]%*c", newMember.name);
    printf("Enter member password: ");
    scanf("%s", newMember.password);
    newMember.noOfCopiesIssued = 0;
    members[(*noOfMembers)++] = newMember;
    printf("Successfully added member \"%s\".\n\n", newMember.name);
}

// Made by Nikita Kiran
void removeMember(member members[], int *noOfMembers) {
    /*A function that allows the librarian to remove a member,
        provided they do not have a copy issued.*/

    if (!(*noOfMembers)) {
        printf("No members present; members cannot be removed.\n\n");
        return;
    }
    int memberID;
    printf("Enter member ID: ");
    scanf("%d", &memberID);
    int index = 0;
    int isFound = 0;
    for (index = 0; index < *noOfMembers; index++) {
        if (members[index].id == memberID ) {
            isFound = 1;
            break;
        }
    }
    if (!isFound) {
        printf("Member with ID %d not found.\n\n", memberID);
        return;
    }
    if (getMemberByID(members, *noOfMembers, memberID)->noOfCopiesIssued) {
        printf("Cannot deregister member \"%s\" as they have book(s) issued under their name.\n\n", getMemberByID(members, *noOfMembers, memberID)->name);
        return;
    }
    (*noOfMembers)--;
    for (int i = index; i < *noOfMembers; i++)
        members[i] = members[i+1];
    printf("Successfully removed member.\n\n");
    return;
}

// Made by Nikita Kiran
void searchMember(member members[], int noOfMembers) {
    /*A function that allows the librarian to search for a member by name.*/

    member searchResults[100];
    int noOfResults = 0;
    char searchString[50];
    printf("Enter member name: ");
    scanf("\n%[^\n]%*c", searchString);
    for (int i = 0; i < noOfMembers; i++) {
        if (strstr(members[i].name, searchString))
            searchResults[noOfResults++]=members[i];
    }
    if (noOfResults == 0){
        printf("No such member found.\n\n");
        return;
    }
    printMemberList(searchResults, noOfResults);
}

// Made by Daksh Rajesh
int __librarianLoop(book books[], int *noOfBooks, member members[], int *noOfMembers, char passwd[]) {
    /*The loop that runs indefinitely when the user logs in as a librarian.
        It returns -1 on breaking.*/

    int option;
	while (1) {
        printf("Enter the corresponding number to do the following:\n");
        printf("1. View the list of books\n");
        printf("2. View the list of members\n");
        printf("3. Search for a book by title, author or genre\n");
        printf("4. Search for a member by name\n");
        printf("5. Add a book or a copy of a book\n");
        printf("6. Remove a book or a copy of a book\n");
        printf("7. Register a new member\n");
        printf("8. Remove a member\n");
        printf("9. Change your password\n");
        printf("10. View books issued by a member\n");
        printf("0. Exit\n> ");

		scanf("%d",&option);

	    if (option == 1) // views list of books
			printBookList(books, *noOfBooks);
        
		else if (option == 2) // views list of members
		    printMemberList(members, *noOfMembers);

        else if (option == 3) // search for a book
            searchBook(books, *noOfBooks);

        else if (option == 4) // search for a member
            searchMember(members, *noOfMembers);

		else if (option == 5) // allows librarian to add copies
            callAddBook(books, noOfBooks);

        else if (option == 6) // allows librarian to remove copies
            callRemoveBook(books, noOfBooks, members, *noOfMembers);

        else if (option == 7) // allows librarian to register members
            addMember(members, noOfMembers);

        else if (option == 8) // allows librarian to deregister members
            removeMember(members, noOfMembers);

		else if (option == 9) // allows librarian to change password
            changeLibrarianPassword(passwd);
        
        else if (option == 10) { // allows librarian to see books issued by a specific member
            int memberID;
            printf("Enter member ID: ");
            scanf("%d", &memberID);
            member *m = getMemberByID(members, *noOfMembers, memberID);
            if (m->id == -1){
                printf("Invalid member ID.\n\n");
                continue;
            }
            char date[11];
            printf("Enter the date in DD/MM/YYYY format: ");
            scanf("%s", date);
            while (!isValidDate(date)) {
                printf("Invalid date.\n\n");
                printf("Enter the date in DD/MM/YYYY format: ");
                scanf("%s", date);
            }
            displayIssuedBooks(m, books, *noOfBooks, date, 1);
        }
		else if (option == 0) // exit
			return -1;

        else // option is any other number
            printf("No such option\n\n");
	}
		
}