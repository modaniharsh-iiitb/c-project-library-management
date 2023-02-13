#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"

int readBookList(struct book books[]) {
    FILE *file1 = fopen("_books", "r");
    int n = 0;
    char buffer[200];
    while (fgets(buffer, 200, file1)) {
        struct book book1;
        char *token = strtok(buffer, ",");
        if (token) {
            book1.id = atoi(token);
        }
        token = strtok(NULL, ",");
        if (token) {
            strcpy(book1.name, token);
        }
        token = strtok(NULL, ",");
        if (token) {
            strcpy(book1.author, token);
        }
        token = strtok(NULL, ",");
        if (token) {
            strcpy(book1.genre, token);
        }
        token = strtok(NULL, ",");
        if (token) {
            book1.noOfCopies = atoi(token);
        }
        for (int i = 0; i < (10 < book1.noOfCopies ? 10 : book1.noOfCopies); i++) {
            book1.copies[i] = (struct copy) {.bookID = book1.id, .copyID = i+1, .isIssued = 0, .dateIssued = ""};
        }
        addBook(books, n, book1);
        n++;
    }
    return n;
}

void __onInit(int *noOfBooks, int *noOfMembers, struct book books[]) {
    *noOfBooks = readBookList(books);
}

void __onClose(int code, struct book books[], int noOfBooks) {
    if (code == 0) {
        FILE *file1 = fopen("_books", "w");
        for (int i = 0; i < noOfBooks; i++) {
            fprintf(file1, "%d,%s,%s,%s,%d\n", books[i].id, books[i].name, books[i].author, books[i].genre, books[i].noOfCopies);
        }
    } else {
        exit(0);
    }
}

int main() {
    // declarations
    struct book books[100]; // assumed here that the number of books never exceeds 100 initially; the condition is later checked with addBook()
    int noOfBooks, noOfMembers;

    // starting running block
    __onInit(&noOfBooks, &noOfMembers, books);

    // ending running block
    __onClose(0, books, noOfBooks);
}