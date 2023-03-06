# C Project - Library Management System
A library management system made in the C programming language.

## Overview

This library management system is useful for both members and librarians. For members, it has the following functions:

1. Viewing the list of books available
2. Viewing the list of copies that they have issued
3. Searching for a book by title, author or genre
4. Issuing a book
5. Returning a book
6. Changing password

Similarly, for librarians, it has the following funcitons:

1. Viewing the list of books
2. Viewing the list of members
3. Searching for a book by title, author or genre
4. Searching for a member by name
5. Adding books or copies of an existing book
6. Registering and removing members
7. Changing password

## How it Works

On login, the user is asked whether they want to use the system as a registered member or a librarian.

```
Enter 1 if you are a librarian and 2 if you are a member. Enter 0 to exit.
```

The user will have to log in accordingly.

Next, they are offered prompts based on what they chose in the initial menu.

```
Enter the corresponding number to do the following:
1. View the list of available books
2. View the list of books issued by you
3. Search for a book by title, genre or author
4. Issue a book
5. Return a book
6. Change your password
7. Exit
> 1
+-----+----------------------------------------------------+------------------------------------------+----------------------+------------------+
| ID  | Name                                               | Author                                   | Genre                | Copies Available |
+-----+----------------------------------------------------+------------------------------------------+----------------------+------------------+
| 1   | Harry Potter and the Philosopher's Stone           | J K Rowling                              | Fantasy              | 4                |
| 2   | Sherlock Holmes: A Study in Scarlet                | Sir Arthur Conan Doyle                   | Detective Fiction    | 3                |
+-----+----------------------------------------------------+------------------------------------------+----------------------+------------------+

> 4
Enter the ID of the book you want to issue: 1
Book issued successfully.
```

To run the app, run the following commands in the terminal:

```
$ make main
$ ./a.out
```

Before committing, tell Harsh. And *make sure* it runs.
