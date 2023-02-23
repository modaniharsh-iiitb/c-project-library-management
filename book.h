#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "copy.h"

// structure describing a book
struct book {
    int id;
    char name[50];
    char author[40];
    char genre[20];
    int noOfCopies;
    struct copy *copies;
};

struct book *getBookByID(struct book books[], int n, int id);

int addCopy(struct book books[], int n, int id);

int removeCopy(struct book books[], int n, int id);

int addBook(struct book books[], int n, struct book book1);

int removeBook(struct book books[], int n, int index);

int copiesAvailable(struct book book1);