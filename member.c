#include <stdlib.h>
#include <string.h>

#include "utils.h"

// structure describing a member
struct member {
    int id;
    char name[50];
    char password[30];
    int noOfCopiesIssued;
    struct copy *copiesIssued;
};

struct member *getMemberByID(struct member members[], int n, int id) {
    // returns member with ID -1 whenever it is not found

    for (int i = 0; i < n; i++) {
        if (members[i].id == id)
            return &(members[i]);
    }
    struct member *voidMember=malloc(sizeof(struct member));
    voidMember->id = -1;
    return voidMember;
}

int addMember(struct member members[], int n, struct member member1) {
    // returns 0 whenever the member is added successfully and -1 whenever it is not
    // increment n whenever this function is called

    if (n >= 100) {
        printf("Too many members added already!\n");
        return -1;
    }
    members[n] = member1;
    return 0;
}

int removeMember(struct member members[], int n, int index) {
    // returns 0 whenever the member is removed successfully and -1 whenever it is not
    // decrement n whenever this function is called

    if (n == 0) {
        printf("No members present; members cannot be removed!\n");
        return -1;
    }
    if (index < 0 || index >= n) {
        printf("Index is too large; there are only %d members!\n", n);
        return -1;
    }
    for (int i = index; i < n; i++) {
        members[i] = members[i+1];
    }
    return 0;
}