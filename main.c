#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "member.h"

int readBookList(struct book books[]) {
    FILE *file1 = fopen("_books", "r");
    int n = 0;
    char buffer[300];
    while (fgets(buffer, 200, file1)) {
        struct book book1;
        int noOfCopies = 0;
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

        while ((token = strtok(NULL, ","))) {
            char *token1 = strtok(token, ":");
            if (token1)
                book1.copies[noOfCopies].bookID = atoi(token1);
            token1 = strtok(NULL, ":");
            if (token1)
                book1.copies[noOfCopies].copyID = atoi(token1);
            book1.copies[noOfCopies].isIssued = 1;
            token1 = strtok(NULL, ":");
            if (token1)
                strcpy(book1.copies[noOfCopies].dateIssued, token1);
            noOfCopies++;
        }
        
        for (int i = 0; i < (10 < book1.noOfCopies ? 10 : book1.noOfCopies); i++)
            book1.copies[i] = (struct copy) {.bookID = book1.id, .copyID = i+1, .isIssued = 0, .dateIssued = ""};
        
        addBook(books, n, book1);
        n++;
    }
    return n;
}

int readMemberList(struct member members[]) {
    FILE *file1 = fopen("_members", "r");
    int n = 0;
    char buffer[300];
    while (fgets(buffer, 200, file1)) {
        struct member member1;
        int noOfCopiesIssued = 0;
        char *token = strtok(buffer, ",");

        if (token)
            member1.id = atoi(token);
        token = strtok(NULL, ",");
        if (token)
            strcpy(member1.name, token);

        while ((token = strtok(NULL, ","))) {
            char *token1 = strtok(token, ":");
            if (token1)
                member1.copiesIssued[noOfCopiesIssued].bookID = atoi(token1);
            token1 = strtok(NULL, ":");
            if (token1)
                member1.copiesIssued[noOfCopiesIssued].copyID = atoi(token1);
            member1.copiesIssued[noOfCopiesIssued].isIssued = 1;
            token1 = strtok(NULL, ":");
            if (token1)
                strcpy(member1.copiesIssued[noOfCopiesIssued].dateIssued, token1);
            noOfCopiesIssued++;
        }

        addMember(members, n, member1);
        n++;
    }
    return n;
}

void __onInit(int *noOfBooks, int *noOfMembers, struct book books[], struct member members[]) {
    *noOfBooks = readBookList(books);
    *noOfMembers = readMemberList(members);
}

void __onClose(int code, struct book books[], struct member members[], int noOfBooks, int noOfMembers) {
    if (code == 0) {
        FILE *file1 = fopen("_books", "w");
        for (int i = 0; i < noOfBooks; i++) {
            fprintf(file1, "%d,%s,%s,%s,", books[i].id, books[i].name, books[i].author, books[i].genre);
            for (int j = 0; j < books[i].noOfCopies; j++) {
                fprintf(file1, "%d:%d:%s",
                    books[i].copies[j].bookID,
                    books[i].copies[j].copyID,
                    books[i].copies[j].isIssued,
                    books[i].copies[j].dateIssued);
                if (j != members[i].noOfCopiesIssued-1)
                    fprintf(file1, ",");
            }
        }
        fclose(file1);
        file1 = fopen("_members", "w");
        for (int i = 0; i < noOfMembers; i++) {
            fprintf(file1, "%d,%s,", members[i].id, members[i].name);
            for (int j = 0; j < members[i].noOfCopiesIssued; j++) {
                fprintf(file1, "%d:%d:%s",
                    members[i].copiesIssued[j].bookID,
                    members[i].copiesIssued[j].copyID,
                    members[i].copiesIssued[j].isIssued,
                    members[i].copiesIssued[j].dateIssued);
                if (j != members[i].noOfCopiesIssued-1)
                    fprintf(file1, ",");
            }
            fprintf(file1, "\n");
        }
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