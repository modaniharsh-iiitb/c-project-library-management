#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define MAX_ATTEMPTS 5

int __librarianLogin(char passwd[]) {
    while (1) {
        char s[30];
        printf("Enter the password, enter -1 to exit: ");
        scanf("%s", s);
        if (!strcmp(s, "-1"))
            return -1;
        if (!strcmp(s, passwd))
            return 0;
        printf("You have entered the incorrect password.\n\n");
    }
}

void changeLibrarianPassword(char passwd[]) {
    // to change password
    
    char old_password[30], new_password[30];
    int attempts_left = MAX_ATTEMPTS;  // initialize attempts left to max

    // prompt user to enter old password
    printf("Enter old password: ");
    fgets(old_password, sizeof(old_password), stdin);

    // remove trailing newline character from password
    old_password[strcspn(old_password, "\n")] = '\0';

    // loop until correct old password is entered or maximum attempts reached
    while (strcmp(old_password, passwd) != 0) {
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
    strcpy(passwd, new_password);
    printf("Password changed successfully.\n");
}

int __librarianLoop(struct book books[], int *noOfBooks, struct member members[], int *noOfMembers, char passwd[]) {

    int option;
	while(1) {
		scanf("%d",&option);
	    if (option == 1) // views list of books
			printBookList(books, *noOfBooks);
		else if (option == 2) // views list of members
		    printMemberList(members, *noOfMembers);	
		else if (option == 3) // allows librarian to add copies
		{


		}
		else if (option == 4) // allows librarian to remove copies
		{

		
		}
        else if (option == 5) // allows librarian to register members
		{


		}
        else if (option == 6) // allows librarian to deregister members
		{


		}
		else if (option == 7) // allows librarian to change password
            changeLibrarianPassword(passwd);
		else // option is any other number
			return -1;
	}
		
}