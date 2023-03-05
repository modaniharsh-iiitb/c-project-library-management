// from copy.c
struct copy {
    int bookID;
    int copyID;
    int isIssued;
    char dateIssued[11];
    char dueDate[11];
};

// from book.c
struct book {
    int id;
    char name[50];
    char author[40];
    char genre[20];
    int noOfCopies;
    struct copy copies[5];
};

struct book *getBookByID(struct book books[], int n, int id);

int addCopy(struct book books[], int n, int id);

int removeCopy(struct book books[], int n, int id);

int addBook(struct book books[], int n, struct book book1);

int removeBook(struct book books[], int n, int index);

int copiesAvailable(struct book book1);

// from member.c
struct member {
    int id;
    char name[50];
    char password[30];
    int noOfCopiesIssued;
    struct copy *copiesIssued[5];
};

struct member *getMemberByID(struct member members[], int n, int id);

int addMember(struct member members[], int n, struct member member1);

int removeMember(struct member members[], int n, int index);

// from datefunctions.c
int isLeapYear(int year);

char *getDueDate(char dateIssued[]);

char *getNextDate(char date[]);

int compareDates(char date1[], char date2[]);

int diffBtwDates(char date1[], char date2[]);

// from librarianfunctions.c
int __librarianLogin(char passwd[]);

int __librarianLoop(struct book books[], int *noOfBooks, struct member members[], int *noOfMembers, char passwd[]);

// from memberfunctions.c
struct member __memberLogin(struct member members[], int noOfMembers);

int __memberLoop(struct book books[], int noOfBooks, struct member member1);

// from io.c
void readBookList(struct book books[], int *noOfBooks);

void readMemberList(struct member members[], int *noOfMembers, struct book books[], int noOfBooks);

void writeBookList(struct book books[], int noOfBooks);

void writeMemberList(struct member members[], int noOfMembers);

void printBookList(struct book books[], int noOfBooks);

void printMemberList(struct member members[], int noOfMembers);