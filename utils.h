// Made by Dhruv Kothari

// strucures
typedef struct copy {
    int bookID;
    int copyID;
    int isIssued;
    char dateIssued[11];
    char dueDate[11];
    int memberIDIssued;
} copy;

typedef struct book {
    int id;
    char name[50];
    char author[40];
    char genre[20];
    int noOfCopies;
    copy copies[5];
} book;

typedef struct member {
    int id;
    char name[50];
    char password[30];
    int noOfCopiesIssued;
    copy *copiesIssued[5];
} member;

// from book.c
book *getBookByID(book books[], int n, int id);

int addCopy(book *book1, int copyID);

int addBook(book books[], int *noOfBooks, book book1);

int copiesAvailable(book book1);

int removeBook(book books[], int *noOfBooks, int bookID);

int removeCopy(book books[], int *noOfBooks, book *book1, member members[], int noOfMembers, int copyID);

// from member.c
member *getMemberByID(member members[], int n, int id);

// from datefunctions.c
int isLeapYear(int year);

int isValidDate(char date[]);

char *getDueDate(char dateIssued[]);

char *getNextDate(char date[], int n);

int compareDates(char date1[], char date2[]);

int diffBtwDates(char date1[], char date2[]);

// from librarianfunctions.c
int __librarianLogin(char passwd[]);

int __librarianLoop(book books[], int *noOfBooks, member members[], int *noOfMembers, char passwd[]);

// from memberfunctions.c
member *__memberLogin(member members[], int noOfMembers);

int __memberLoop(book books[], int noOfBooks, member *member1);

void searchBook(book books[], int noOfBooks);

void displayIssuedBooks(member *member1, book books[], int noOfBooks, char currentDate[], int isLibrarianCalling);

// from io.c
void readBookList(book books[], int *noOfBooks, member members[], int noOfMembers);

void readMemberList(member members[], int *noOfMembers);

void writeBookList(book books[], int noOfBooks);

void writeMemberList(member members[], int noOfMembers);

void writePassword(char passwd[]);

void printBookList(book books[], int noOfBooks);

void printMemberList(member members[], int noOfMembers);