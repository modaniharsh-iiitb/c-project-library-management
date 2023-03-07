#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"

// Made by Dhruv Kothari
book *getBookByID(book books[], int n, int id) {
    /*A function that returns a pointer to the book that has its ID equal to the input
        ID. It returns a pointer to a new book with ID -1 if no such book is found.*/

    for (int i = 0; i < n; i++) {
        if (books[i].id == id)
            return &(books[i]);
    }
    book *voidBook = malloc(sizeof(book));
    voidBook->id = -1;
    voidBook->noOfCopies = 0;
    return voidBook;
}

// Made by Dhruv Kothari
int addBook(book books[], int *noOfBooks, book book1) {
    /*A function that adds a new book to the list of books. It returns 0 if a book
        is added successfully and -1 if it is not.*/

    if (*noOfBooks >= 100) {
        printf("Too many books added already.\n");
        return -1;
    }
    books[(*noOfBooks)++] = book1;
    return 0;
}

// Made by Dhruv Kothari
int addCopy(book *book1, int copyID) {
    /*A function that adds a new copy of a book. It returns 0 if a copy
        is added successfully and -1 if it is not.*/

    if (book1->noOfCopies == 5) {
        printf("Too many copies added already.\n");
        return -1;
    }
    book1->copies[book1->noOfCopies++] = (copy){.bookID = book1->id, .copyID = copyID, .isIssued = 0, .dateIssued = "00/00/0000", .dueDate = "00/00/0000", .memberIDIssued = -1};
    return 0;
}

// Made by Nikita Kiran
int removeCopy(book books[], int *noOfBooks, book *book1, member members[], int noOfMembers, int copyID) {
    /*A function that removes a copy of a book. It returns 0 if the copy
        is removed successfully and -1 if it is not.*/

    int index;
    int isFound = 0;
    for (index = 0; index < book1->noOfCopies; index++) {
        if (book1->copies[index].copyID == copyID) {
            isFound = 1;
            break;
        }
    }
    if (!isFound) {
        printf("Copy with ID %d does not exist.\n", copyID);
        return -1;
    }
    if (book1->copies[index].isIssued) {
        printf("Cannot remove this copy as it is currently issued.\n");
        return -1;
    }
    book1->noOfCopies--;

    for (int i = index; i < book1->noOfCopies; i++) {
        book1->copies[i] = book1->copies[i + 1];
        if (book1->copies[i].memberIDIssued != -1) {
            member *m = getMemberByID(members, noOfMembers, book1->copies[i].memberIDIssued);
            for (int j = 0; j < m->noOfCopiesIssued; j++) {
                if (m->copiesIssued[j] == &(book1->copies[i]) + 1)
                    m->copiesIssued[j]--;
            }
        }
    }
    if (!(book1->noOfCopies)) {
        printf("That was the last copy of this book. Removing the book as well.\n");
        return removeBook(books, noOfBooks, book1->id);
    }
    return 0;
}

// Made by Harsh Modani
int removeBook(book books[], int *noOfBooks, int bookID) {
    /*A function that removes a book to the list of books. It returns 0 if a book
        is removed successfully and -1 if it is not.*/

    if (!(*noOfBooks)) {
        printf("No books present; books cannot be removed.\n");
        return -1;
    }
    int index = 0;
    int isFound = 0;
    for (index = 0; index < *noOfBooks; index++) {
        if (books[index].id == bookID) {
            isFound = 1;
            break;
        }
    }
    if (!isFound) {
        printf("Book with ID %d not found.\n", bookID);
        return -1;
    }
    for (int i = 0; i < books[index].noOfCopies; i++) {
        if (books[index].copies[i].isIssued) {
            printf("Cannot remove this book as there is a copy issued of it already.\n");
            return -1;
        }
    }
    (*noOfBooks)--;
    for (int i = index; i < *noOfBooks; i++)
        books[i] = books[i + 1];
    return 0;
}

// Made by Dhruv Kothari
int copiesAvailable(book book1) {
    /*A function that calculates the number of copies not issued (and thus available
        for issue) of a given book.*/

    int count = 0;
    for (int i = 0; i < book1.noOfCopies; i++) {
        if (!book1.copies[i].isIssued)
            count++;
    }
    return count;
}
