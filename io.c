#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

// Made by Harsh Modani
void readMemberList(member members[], int *noOfMembers) {
    /* A function to be called to read the file "_members".*/

    FILE *file1 = fopen("_members", "r");
    char buffer[300];
    while (fgets(buffer, 200, file1)) {
        member member1;
        char *token = strtok(buffer, ",");

        if (token)
            member1.id = atoi(token);
        token = strtok(NULL, ",");
        if (token)
            strcpy(member1.name, token);
        token = strtok(NULL, ",");
        if (token)
            strcpy(member1.password, token);

        members[(*noOfMembers)++] = member1;
    }
}

// Made by Harsh Modani
void readBookList(book books[], int *noOfBooks, member members[], int noOfMembers) {
    /* A function to be called to read the files "_books" and "_copies".*/

    FILE *file1 = fopen("_books", "r");
    char buffer[300];
    while (fgets(buffer, 250, file1)) {
        book book1;
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
        book1.noOfCopies = 0;
        
        books[(*noOfBooks)++] = book1;
    }
    fclose(file1);

    file1 = fopen("_copies", "r");
    while (fgets(buffer, 200, file1)) {
        copy copy1;
        char *token = strtok(buffer, ",");

        if (token)
            copy1.bookID = atoi(token);
        token = strtok(NULL, ",");
        if (token)
            copy1.copyID = atoi(token);
        token = strtok(NULL, ",");
        if (token)
            copy1.isIssued = atoi(token);
        token = strtok(NULL, ",");
        if (token)
            strcpy(copy1.dateIssued, token);
        token = strtok(NULL, ",");
        if (token)
            strcpy(copy1.dueDate, token);
        token = strtok(NULL, ",");
        if (token)
            copy1.memberIDIssued = atoi(token);
        
        book *b = getBookByID(books, *noOfBooks, copy1.bookID);
        b->copies[b->noOfCopies++] = copy1;
        member *member1 = getMemberByID(members, noOfMembers, copy1.memberIDIssued);
        member1->copiesIssued[member1->noOfCopiesIssued++] = &(b->copies[b->noOfCopies-1]);
    }
    fclose(file1);
}

// Made by Harsh Modani
void writeBookList(book books[], int noOfBooks) {
    /* A function to be called to write into the files "_books" and "_copies".*/

    FILE *file1 = fopen("_books", "w");
    for (int i = 0; i < noOfBooks; i++)
        fprintf(file1, "%d,%s,%s,%s,\n", books[i].id, books[i].name, books[i].author, books[i].genre);  
    fclose(file1);

    file1 = fopen("_copies", "w");
    for (int i = 0; i < noOfBooks; i++) {
        for (int j = 0; j < books[i].noOfCopies; j++)
                fprintf(file1, "%d,%d,%d,%s,%s,%d,\n",
                books[i].copies[j].bookID,
                books[i].copies[j].copyID,
                books[i].copies[j].isIssued,
                books[i].copies[j].dateIssued,
                books[i].copies[j].dueDate,
                books[i].copies[j].memberIDIssued);
    }
    fclose(file1);
}

// Made by Harsh Modani
void writeMemberList(member members[], int noOfMembers) {
    /* A function to be called to write into the file "_members".*/

    FILE *file1 = fopen("_members", "w");
    for (int i = 0; i < noOfMembers; i++)
        fprintf(file1, "%d,%s,%s,\n", members[i].id, members[i].name, members[i].password);
    fclose(file1);
}

// Made by Daksh Rajesh
void writePassword(char passwd[]) {
    /* A function to be called to write into the file "_password".*/

    FILE *file1 = fopen("_password", "w");
    fprintf(file1, "%s", passwd);
    fclose(file1);
}

// Made by Daksh Rajesh
void printBookList(book books[], int noOfBooks) {
    /* A function to be called to print the given list of books.*/

    printf("+-----+----------------------------------------------------+------------------------------------------+----------------------+--------------+------------------+\n");
    printf("| ID  | Name                                               | Author                                   | Genre                | Total Copies | Copies Available |\n");
    printf("+-----+----------------------------------------------------+------------------------------------------+----------------------+--------------+------------------+\n");
    for (int i = 0; i < noOfBooks; i++) {
        printf("| %3d | %-50s | %-40s | %-20s | %12d | %16d |\n", books[i].id, books[i].name, books[i].author, books[i].genre, books[i].noOfCopies, copiesAvailable(books[i]));
    }
    printf("+-----+----------------------------------------------------+------------------------------------------+----------------------+--------------+------------------+\n\n");
}

// Made by Daksh Rajesh
void printMemberList(member members[], int noOfMembers) {
    /* A function to be called to print the given list of members.*/

    printf("+-----+----------------------------------------------------+---------------+\n");
    printf("| ID  | Name                                               | Copies Issued |\n");
    printf("+-----+----------------------------------------------------+---------------+\n");
    for (int i = 0; i < noOfMembers; i++) {
        printf("| %3d | %-50s | %13d |\n", members[i].id, members[i].name, members[i].noOfCopiesIssued);
    }
    printf("+-----+----------------------------------------------------+---------------+\n\n");
}