#include <stdlib.h>
#include <string.h>

// structure describing a copy of a book
struct copy
{
    int bookID;
    int copyID;
    int isIssued;
    char dateIssued[11];
    char dueDate[11];
};