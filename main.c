#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"
#include "copy.h"

int readBookList(struct book books[]) {
    int id; char name[50], author[40], genre[20];
    int noOfCopies = 1; struct copy copies[10];
    struct book book1;

    FILE *file1 = fopen("books", "r");
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
        copies[0] = (struct copy) {.bookID = id, .copyID = 1, .isIssued = 0, .dateIssued = ""};
        book1 = (struct book) {.id = id, .name = name, .author = author, .genre = genre, .noOfCopies = 1, .copies = copies};
        books[n] = book1;
        n++;
    }
    return n;
}

int main() {

}