#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "member.h"
#define MAX_ATTEMPTS 5  // maximum number of attempts to enter old password

int addMember(struct member members[], int n, struct member member1) {
    // returns 0 whenever the member is added successfully and -1 whenever it is not
    // increment n whenever this function is called

    if (n >= 100) {
        printf("Too many members added already!\n");
        return -1;
    }
    // Copy the new member into the next available slot in the array
    strncpy(&members[n], &member1, sizeof(struct member));
    
    // Increment the count of members in the array
    return n + 1;
}

//to change password        

void change_password(struct member *m) {
    char old_password[30], new_password[30];
    int attempts_left = MAX_ATTEMPTS;  // initialize attempts left to max

    // prompt user to enter old password
    printf("Enter old password: ");
    fgets(old_password, sizeof(old_password), stdin);

    // remove trailing newline character from password
    old_password[strcspn(old_password, "\n")] = '\0';

    // loop until correct old password is entered or maximum attempts reached
    while (strcmp(old_password, m->password) != 0) {
        attempts_left--;  // decrement attempts left
        printf("Incorrect password (%d attempts left)\n", attempts_left);

        // check if maximum attempts reached
        if (attempts_left == 0) {
            printf("Maximum attempts reached. Password change aborted.\n");
            return;  // exit function without changing password
        }

        // prompt user to enter old password again
        printf("Enter old password: ");
        fgets(old_password, sizeof(old_password), stdin);

        // remove trailing newline character from password
        old_password[strcspn(old_password, "\n")] = '\0';
    }

    // if correct old password entered, prompt user to enter new password
    printf("Enter new password: ");
    fgets(new_password, sizeof(new_password), stdin);
    // remove trailing newline character from password
    new_password[strcspn(new_password, "\n")] = '\0';
    // update password in member struct with new password
    strcpy(m->password, new_password);
    printf("Password changed successfully.\n");
}