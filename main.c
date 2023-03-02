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
        token = strtok(NULL, ",");
        if (token)
            book1.noOfCopies = atoi(token);
        
        addBook(books, n, book1);
        n++;
    }
    fclose(file1);
    *noOfBooks = n;

    file1 = fopen("_copies", "r");
    while (fgets(buffer, 200, file1)) {
        struct copy copy1;
        int nc = 0;
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
        
        struct book *b = getBookByID(books, noOfBooks, copy1.bookID);
        b->copies[nc] = copy1;
        nc++;
    }
    fclose(file1);
}

// function to be called to read the file "_members"
void readMemberList(struct member members[], int *noOfMembers) {
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
            strcpy(member1.password, token);
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
    *noOfMembers = n;
}

// function to be called to write into the file "_books"
void writeBookList(struct book books[], int noOfBooks) {
    FILE *file1 = fopen("_books", "w");
    for (int i = 0; i < noOfBooks; i++) {
        fprintf(file1, "%d,%s,%s,%s,%d\n", books[i].id, books[i].name, books[i].author, books[i].genre, books[i].noOfCopies);
    }
    fclose(file1);

    file1 = fopen("_copies", "w");
    for (int i = 0; i < noOfBooks; i++) {
        for (int j = 0; j < books[i].noOfCopies; j++) {
            fprintf(file1, "%d,%d,%d,%s,%s",
                books[i].copies[j].bookID,
                books[i].copies[j].copyID,
                books[i].copies[j].isIssued,
                books[i].copies[j].dateIssued,
                books[i].copies[j].dueDate);
            if (j != books[i].noOfCopies-1)
                fprintf(file1, ",");
        }
    }
    fclose(file1);
}

// function to be called to write into the file "_members"
void writeMemberList(struct member members[], int noOfMembers) {
    FILE *file1 = fopen("_members", "w");
    for (int i = 0; i < noOfMembers; i++) {
        fprintf(file1, "%d,%s,%s,", members[i].id, members[i].name, members[i].password);
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

// function to be called on initiation of the program
void __onInit(int *noOfBooks, int *noOfMembers, struct book books[], struct member members[], char password[]) {
    readBookList(books, noOfBooks);
    readMemberList(members, noOfMembers);
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

int __librarianLogin(char passwd[]) {
    while (1) {
        char s[30];
        printf("Enter the password, enter -1 to exit: ");
        scanf("%s", s);
        if (!strcmp(s, "-1"))
            return -1;
        if (!strcmp(s, passwd))
            return 0;
        printf("You have entered the incorrect password.\n\n");
    }
}

int __memberLogin(struct member members[],int noOfMembers) {
    // returns -1 if the member wants to exit without logging in, 0 if they log in successfully
    while (1) {
	    int t;
	    char passwd[30];
	    printf("Enter your ID, enter -1 to exit: ");
	    scanf("%d", t);
	    printf("Enter your password: ");
	    scanf("%s", passwd);
	    if (t == -1)
		    return -1;
	    for (int i = 0; i < noOfMembers; i++) {
		    if (t == members[i].id && !strcmp(passwd, members[i].password))
			    return 0;
	    }
	    printf("You have entered the incorrect ID or password.\n\n");
    } 
}

int __librarianLoop() {
    // returns -1 to break

}

int __memberLoop() {
    // returns -1 to break

}

int __choose(char passwd[], struct member members[], int noOfMembers) {
    char choice;
    while (1) {
        printf("Enter 1 if you are a librarian and 2 if you are a member. Enter 0 to exit.:\n> ");
        scanf("%c", &choice);
        if (choice == '1') {
            int m = __librarianLogin(passwd);
            if (m == -1)
                return 0;
            while (!m)
                m = __librarianLoop();
        } else if (choice == '2') {
            int m = __memberLogin(members, noOfMembers);
            if (m == -1)
                return 0;
            while (!m)
                m = __memberLoop();
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
    code = __choose(passwd, members, noOfMembers);

    // ending running block
    __onClose(code, books, members, noOfBooks, noOfMembers);
}
