#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"

// Made by Dhruv Kothari
member *getMemberByID(member members[], int n, int id) {
    /*A function that returns a pointer to the member that has its ID equal to the input
        ID. It returns a pointer to a new member with ID -1 if no such member is found.*/

    for (int i = 0; i < n; i++) {
        if (members[i].id == id)
            return &(members[i]);
    }
    member *voidMember=malloc(sizeof(member));
    voidMember->id = -1;
    voidMember->noOfCopiesIssued = 0;
    return voidMember;
}