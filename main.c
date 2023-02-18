#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "member.h"

// function to be called to read the file "_books"
int readBookList(struct book books[]) {
    FILE *file1 = fopen("_books", "r");
    int n = 0;
    char buffer[300];
    while (fgets(buffer, 200, file1)) {
        struct book book1;
        char *token = strtok(buffer, ",");

        if (token)
            book1.id = atoi(token);
        token = strtok(NULL, ",");
        if (token)
            strcpy(book1.name, token);
        token = strtok(NULL, ",");
        if (token)
            strcpy(book1.author, token);
        token = strtok(NULL, ",");
        if (token)
            strcpy(book1.genre, token);
        token = strtok(NULL, ",");
        if (token)
            book1.noOfCopies = atoi(token);

        for (int i = 0; i < book1.noOfCopies; i++) {
            char *token1 = strtok(token, ":");
            if (token1)
                book1.copies[i].bookID = atoi(token1);
            token1 = strtok(NULL, ":");
            if (token1)
                book1.copies[i].copyID = atoi(token1);
            token1 = strtok(NULL, ":");
            if (token1)
                book1.copies[i].copyID = atoi(token1);
            token1 = strtok(NULL, ":");
            if (token1)
                strcpy(book1.copies[i].dateIssued, token1);
        }
        
        addBook(books, n, book1);
        n++;
    }
    return n;
}

// function to be called to read the file "_members"
int readMemberList(struct member members[]) {
    FILE *file1 = fopen("_members", "r");
    int n = 0;
    char buffer[300];
    while (fgets(buffer, 200, file1)) {
        struct member member1;
        char *token = strtok(buffer, ",");

        if (token)
            member1.id = atoi(token);
        token = strtok(NULL, ",");
        if (token)
            strcpy(member1.name, token);
        token = strtok(NULL, ",");
        if (token)
            member1.noOfCopiesIssued = atoi(token);
        

        for (int i = 0; i < member1.noOfCopiesIssued; i++) {
            char *token1 = strtok(token, ":");
            if (token1)
                member1.copiesIssued[i].bookID = atoi(token1);
            token1 = strtok(NULL, ":");
            if (token1)
                member1.copiesIssued[i].copyID = atoi(token1);
            member1.copiesIssued[i].isIssued = 1;
            token1 = strtok(NULL, ":");
            if (token1)
                strcpy(member1.copiesIssued[i].dateIssued, token1);
        }

        addMember(members, n, member1);
        n++;
    }
    return n;
}

// function to be called to write into the file "_books"
void writeBookList(struct book books[], int noOfBooks) {
    FILE *file1 = fopen("_books", "w");
        for (int i = 0; i < noOfBooks; i++) {
            fprintf(file1, "%d,%s,%s,%s,", books[i].id, books[i].name, books[i].author, books[i].genre);
            for (int j = 0; j < books[i].noOfCopies; j++) {
                fprintf(file1, "%d:%d:%d:%s",
                    books[i].copies[j].bookID,
                    books[i].copies[j].copyID,
                    books[i].copies[j].isIssued,
                    books[i].copies[j].dateIssued);
                if (j != books[i].noOfCopies-1)
                    fprintf(file1, ",");
            }
            fprintf(file1, "\n");
        }
    fclose(file1);
}

// function to be called to write into the file "_members"
void writeMemberList(struct member members[], int noOfMembers) {
    FILE *file1 = fopen("_members", "w");
        for (int i = 0; i < noOfMembers; i++) {
            fprintf(file1, "%d,%s,", members[i].id, members[i].name);
            for (int j = 0; j < members[i].noOfCopiesIssued; j++) {
                fprintf(file1, "%d:%d:%d:%s",
                    members[i].copiesIssued[j].bookID,
                    members[i].copiesIssued[j].copyID,
                    members[i].copiesIssued[j].isIssued,
                    members[i].copiesIssued[j].dateIssued);
                if (j != members[i].noOfCopiesIssued-1)
                    fprintf(file1, ",");
            }
            fprintf(file1, "\n");
        }
    fclose(file1);
}

// function to be called on initiation of the program
void __onInit(int *noOfBooks, int *noOfMembers, struct book books[], struct member members[]) {
    *noOfBooks = readBookList(books);
    *noOfMembers = readMemberList(members);
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

int main() {
    // declarations
    struct book books[100]; // assumed here that the number of books never exceeds 100 initially; the condition is later checked with addBook()
    struct member members[100]; // assumed here that the number of members never exceeds 100 initially; the condition is later checked with addMember()
    int noOfBooks, noOfMembers;

    // starting running block
    __onInit(&noOfBooks, &noOfMembers, books, members);

    // ending running block
    __onClose(0, books, members, noOfBooks, noOfMembers);
}