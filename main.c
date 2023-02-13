#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"
#include "copy.h"

int readBookList(struct book books[]) {
    int id; char name[50], author[40], genre[20];
    int noOfCopies = 1; struct copy copies[10];
    struct book book1;

    FILE *file1 = fopen("_books", "r");
    int n = 0;
    char buffer[200];
    while (fgets(buffer, 200, file1)) {
        char *token = strtok(buffer, " ");
        if (token) {
            id = atoi(token);
        }
        token = strtok(NULL, " ");
        if (token) {
            strcpy(name, token);
        }
        token = strtok(NULL, " ");
        if (token) {
            strcpy(author, token);
        }
        token = strtok(NULL, " ");
        if (token) {
            strcpy(genre, token);
        }
        token = strtok(NULL, " ");
        if (token) {
            noOfCopies = atoi(token);
        }
        for (int i = 0; i < (10 < noOfCopies ? 10 : noOfCopies); i++) {
            copies[i] = (struct copy) {.bookID = id, .copyID = i+1, .isIssued = 0, .dateIssued = ""};
        }
        book1 = (struct book) {.id = id, .name = name, .author = author, .genre = genre, .noOfCopies = 1, .copies = copies};
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
            fprintf(file1, "%d %s %s %s %d\n", books[i].id, books[i].name, books[i].author, books[i].genre, books[i].noOfCopies);
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