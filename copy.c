#include <stdlib.h>
#include <string.h>

#include "book.h"

// structure describing a copy of a book
struct copy {
    int bookID;
    int copyID;
    int isIssued;
    char dateIssued[10];
};