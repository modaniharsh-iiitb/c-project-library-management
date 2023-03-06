#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

// Made by Aryan Mishra
void __onInit(int *noOfBooks, int *noOfMembers, book books[], member members[], char password[]) {
    /*A function to be called on initiation of the program. It reads the files and puts
        their values into variables that will be referred to throughout the program.*/

    readMemberList(members, noOfMembers);
    readBookList(books, noOfBooks, members, *noOfMembers);
    FILE *file1 = fopen("_password", "r");
    fscanf(file1, "%s", password);
}

// Made by Aryan Mishra
void __onClose(book books[], member members[], int noOfBooks, int noOfMembers, char passwd[]) {
    /*A function to be called on completion of the program run. It writes the variables
        stored in memory in the program, into the files.*/

    writeBookList(books, noOfBooks);
    writeMemberList(members, noOfMembers);
    writePassword(passwd);
}

// Made by Aryan Mishra
void __choose(char passwd[], member members[], int *noOfMembers, book books[], int *noOfBooks) {
    /*A function that lets the user choose between using the system as a librarian
        or a member.*/

    int option;
    while (1) {
        printf("Enter 1 if you are a librarian and 2 if you are a member. Enter 0 to exit.\n> ");
        scanf("\n%d", &option);
        if (option == 1) {
            int m = __librarianLogin(passwd);
            if (m == -1)
                continue;
            while (!m)
                m = __librarianLoop(books, noOfBooks, members, noOfMembers, passwd);
        } else if (option == 2) {
            member *m = __memberLogin(members, *noOfMembers);
            if (m->id == -1)
                continue;
            int n = 0;
            while (!n)
                n = __memberLoop(books, *noOfBooks, m);
        } else if (option == 0)
            return;
        else
            printf("Invalid input.\n\n"); 
    }
}

// Made by Aryan Mishra
void main() {
    // declarations
    book books[100]; // assumed here that the number of books never exceeds 100 initially; the condition is later checked with addBook()
    member members[100]; // assumed here that the number of members never exceeds 100 initially; the condition is later checked with addMember()
    int noOfBooks, noOfMembers;
    char passwd[30];

    // starting running block
    __onInit(&noOfBooks, &noOfMembers, books, members, passwd);

    // looping through control
    __choose(passwd, members, &noOfMembers, books, &noOfBooks);

    // ending running block
    __onClose(books, members, noOfBooks, noOfMembers, passwd);
}
