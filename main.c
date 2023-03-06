#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

// function to be called on initiation of the program
void __onInit(int *noOfBooks, int *noOfMembers, book books[], member members[], char password[]) {
    readMemberList(members, noOfMembers, books, *noOfBooks);
    readBookList(books, noOfBooks, members, *noOfMembers);
    FILE *file1 = fopen("_password", "r");
    fscanf(file1, "%s", password);
}

// function to be called on exit of the program
void __onClose(book books[], member members[], int noOfBooks, int noOfMembers, char passwd[]) {

    writeBookList(books, noOfBooks);
    writeMemberList(members, noOfMembers);
    writePassword(passwd);
}

void __choose(char passwd[], member members[], int *noOfMembers, book books[], int *noOfBooks) {
    char choice;
    while (1) {
        printf("Enter 1 if you are a librarian and 2 if you are a member. Enter 0 to exit.\n> ");
        scanf("\n%c", &choice);
        if (choice == '1') {
            int m = __librarianLogin(passwd);
            if (m == -1)
                continue;
            while (!m)
                m = __librarianLoop(books, noOfBooks, members, noOfMembers, passwd);
        } else if (choice == '2') {
            member *m = __memberLogin(members, *noOfMembers);
            if (m->id == -1)
                continue;
            int n = 0;
            while (!n)
                n = __memberLoop(books, *noOfBooks, m);
        } else if (choice == '0')
            return;
        else
            printf("Invalid input.\n\n"); 
    }
}

int main() {
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
