#include <stdlib.h>
#include <string.h>

#include "utils.h"

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

int __librarianLoop() {
    // returns -1 to break
    int option;
    while (1) {
        scanf("%d", &option);
        if (option == 1) // views list of available books
        {
        }
        else if (option == 2) // allows members to view list of copies issued, due dates and fine if any
        {
        }
        else if (option == 3) // allows members to issue and return books
        {
        }
        else if (option == 4) // get issue date and calculate return date and fine due if necessary on issue and return
        {
        }
        else if (option == 5) // allows members to change password
        {
        }
        else if (option == 6) //exit
            return -1;
        else
            printf("No such option\n");
    }
}

