#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

// function to be called on initiation of the program
void __onInit(int *noOfBooks, int *noOfMembers, struct book books[], struct member members[], char password[]) {
    readBookList(books, noOfBooks);
    readMemberList(members, noOfMembers, books, *noOfBooks);
    FILE *file1 = fopen("_password", "r");
    fscanf(file1, "%s", password);

    // remove later
    printBookList(books, *noOfBooks);
    printMemberList(members, *noOfMembers);
}

// function to be called on exit of the program
void __onClose(int code, struct book books[], struct member members[], int noOfBooks, int noOfMembers) {
    // code = 0 is successful exit
    if (code == 0) {
        writeBookList(books, noOfBooks);
        writeMemberList(members, noOfMembers);
    } else {
        exit(0);
    }
}

int __choose(char passwd[], struct member members[], int *noOfMembers, struct book books[], int *noOfBooks) {
    char choice;
    while (1) {
        printf("Enter 1 if you are a librarian and 2 if you are a member. Enter 0 to exit.:\n> ");
        scanf("%c", &choice);
        if (choice == '1') {
            int m = __librarianLogin(passwd);
            if (m == -1)
                continue;
            while (!m)
                m = __librarianLoop(books, noOfBooks, members, noOfMembers, passwd);
        } else if (choice == '2') {
            struct member m = __memberLogin(members, *noOfMembers);
            if (m.id == -1)
                continue;
            int n = 0;
            while (!n)
                n = __memberLoop(books, *noOfBooks, m);
        } else if (choice == '0')
            return 0;
        else
            printf("Invalid input.\n\n"); 
    }
    return 0;
}

int main() {
    // declarations
    struct book books[100]; // assumed here that the number of books never exceeds 100 initially; the condition is later checked with addBook()
    struct member members[100]; // assumed here that the number of members never exceeds 100 initially; the condition is later checked with addMember()
    int noOfBooks, noOfMembers;
    char passwd[30];
    int code;

    // starting running block
    __onInit(&noOfBooks, &noOfMembers, books, members, passwd);

    // looping through control
    code = __choose(passwd, members, &noOfMembers, books, &noOfBooks);

    // ending running block
    __onClose(code, books, members, noOfBooks, noOfMembers);
}
