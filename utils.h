// from book.c
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

// from copy.c
struct copy {
    int bookID;
    int copyID;
    int isIssued;
    char dateIssued[11];
    char dueDate[11];
};

// from member.c
struct member {
    int id;
    char name[50];
    char password[30];
    int noOfCopiesIssued;
    struct copy *copiesIssued;
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

int __librarianLoop();