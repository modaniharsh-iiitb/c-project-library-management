#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"

// structure describing a member
struct member {
    int id;
    char name[50];
    int noOfCopiesIssued;
    struct copy copiesIssued[5];
};

struct member getMemberByID(struct member members[], int n, int id);

int addMember(struct member members[], int n, struct member member1);

int removeMember(struct member members[], int n, int index);