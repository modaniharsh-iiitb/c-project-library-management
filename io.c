#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

// function to be called to read the files "_books" and "_copies"
void readBookList(struct book books[], int *noOfBooks) {
    FILE *file1 = fopen("_books", "r");
    int n = 0;
    char buffer[300];
    while (fgets(buffer, 250, file1)) {
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
        book1.noOfCopies = 0;
        
        addBook(books, n, book1);
        n++;
    }
    fclose(file1);
    *noOfBooks = n;
    printf("Read book file\n");

    file1 = fopen("_copies", "r");
    while (fgets(buffer, 200, file1)) {
        struct copy copy1;
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
        
        struct book *b = getBookByID(books, *noOfBooks, copy1.bookID);
        b->copies[b->noOfCopies] = copy1;
        b->noOfCopies++;
    }
    printf("Read copy file\n");
    fclose(file1);
}

// function to be called to read the file "_members"
void readMemberList(struct member members[], int *noOfMembers, struct book books[], int noOfBooks) {
    FILE *file1 = fopen("_members", "r");
    int n = 0;
    char buffer[300];
    while (fgets(buffer, 200, file1)) {
        printf("Reading a line from member file\n");
        struct member member1;
        char *token = strtok(buffer, ",");

        if (token)
            member1.id = atoi(token);
        token = strtok(NULL, ",");
        if (token)
            strcpy(member1.name, token);
        token = strtok(NULL, ",");
        if (token)
            strcpy(member1.password, token);
        token = strtok(NULL, ",");
        if (token)
            member1.noOfCopiesIssued = atoi(token);
        

        for (int i = 0; i < member1.noOfCopiesIssued; i++) {
            char *token1 = strtok(token, ":");
            int bookid, copyid;
            if (token1)
                bookid = atoi(token1);
            token1 = strtok(NULL, ",");
            if (token1)
                copyid = atoi(token1);
            printf("Getting book\n");
            struct book *book1 = getBookByID(books, noOfBooks, bookid);
            for (int j = 0; j < book1->noOfCopies; j++) {
                printf("Looking at copy %d\n", j+1);
                if (book1->copies[j].copyID == copyid && book1->copies[j].isIssued)
                    member1.copiesIssued[i] = &(book1->copies[j]);
            }
        }

        addMember(members, n, member1);
        n++;
    }
    printf("Read member file\n");
    *noOfMembers = n;
}

// function to be called to write into the file "_books" and "_copies"
void writeBookList(struct book books[], int noOfBooks) {
    FILE *file1 = fopen("_books", "w");
    for (int i = 0; i < noOfBooks; i++) {
        fprintf(file1, "%d,%s,%s,%s,\n", books[i].id, books[i].name, books[i].author, books[i].genre);
    }
    fclose(file1);

    FILE *file2 = fopen("_copies", "w");
    for (int i = 0; i < noOfBooks; i++) {
        for (int j = 0; j < books[i].noOfCopies; j++) {
            fprintf(file2, "%d,%d,%d,%s,%s,\n",
                books[i].copies[j].bookID,
                books[i].copies[j].copyID,
                books[i].copies[j].isIssued,
                books[i].copies[j].dateIssued,
                books[i].copies[j].dueDate);
        }
    }
    fclose(file2);
}

// function to be called to write into the file "_members"
void writeMemberList(struct member members[], int noOfMembers) {
    FILE *file1 = fopen("_members", "w");
    for (int i = 0; i < noOfMembers; i++) {
        fprintf(file1, "%d,%s,%s,", members[i].id, members[i].name, members[i].password);
        for (int j = 0; j < members[i].noOfCopiesIssued; j++) {
            fprintf(file1, "%d:%d,",
                members[i].copiesIssued[j]->bookID,
                members[i].copiesIssued[j]->copyID);
        }
        fprintf(file1, "\n");
    }
    fclose(file1);
}

void printBookList(struct book books[], int noOfBooks) {
    printf("+-----+----------------------------------------------------+------------------------------------------+----------------------+------------------+\n");
    printf("| ID  | Name                                               | Author                                   | Genre                | Copies Available |\n");
    printf("+-----+----------------------------------------------------+------------------------------------------+----------------------+------------------+\n");
    for (int i = 0; i < noOfBooks; i++) {
        printf("| %-3d | %-50s | %-40s | %-20s | %-16d |\n", books[i].id, books[i].name, books[i].author, books[i].genre, copiesAvailable(books[i]));
    }
    printf("+-----+----------------------------------------------------+------------------------------------------+----------------------+------------------+\n");
}

void printMemberList(struct member members[], int noOfMembers) {
    printf("+-----+----------------------------------------------------+---------------+\n");
    printf("| ID  | Name                                               | Copies Issued |\n");
    printf("+-----+----------------------------------------------------+---------------+\n");
    for (int i = 0; i < noOfMembers; i++) {
        printf("| %3d | %50s | %13d |\n", members[i].id, members[i].name, members[i].noOfCopiesIssued);
    }
    printf("+-----+----------------------------------------------------+---------------+\n");
}