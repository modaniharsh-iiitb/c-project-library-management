#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define MAX_ATTEMPTS 5  // maximum number of attempts to enter old password

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
        printf("Incorrect password (%d attempts left).\n\n", attempts_left);

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