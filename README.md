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

Similarly, for librarians, it has the following functions:

1. Viewing the list of books
2. Viewing the list of members
3. Searching for a book by title, author or genre
4. Searching for a member by name
5. Adding or removing books or copies of an existing book
6. Registering and removing members
7. Changing password

## How it Works

On login, the user is asked whether they want to use the system as a registered member or a librarian.

```
Enter 1 if you are a librarian and 2 if you are a member. Enter 0 to exit.
>
```

The user will have to log in accordingly.

Next, they are offered prompts based on what they chose in the initial menu.

#### **For member:**
```
Enter the corresponding number to do the following:
1. View the list of available books
2. View the list of books issued by you
3. Search for a book by title, genre or author
4. Issue a book
5. Return a book
6. Change your password
7. Exit
> 
```

#### **For librarian:**
```
Enter the corresponding number to do the following:
1. View the list of books
2. View the list of members
3. Search for a book by title, author or genre
4. Search for a member by name
5. Add a book or a copy of a book
6. Remove a book or a copy of a book
7. Register a new member
8. Remove a member
9. Change your password
10. View books issued by a member
0. Exit
```

Each of the functions that can be performed by the members and librarians respectively is explained further below.

## Members

### **1. View the list of available books**

This function allows the member to see the details of each book in tabulated format, along with the number of copies of each book available for issue.

```
+-----+----------------------------------------------------+------------------------------------------+----------------------+--------------+------------------+
| ID  | Name                                               | Author                                   | Genre                | Total Copies | Copies Available |
+-----+----------------------------------------------------+------------------------------------------+----------------------+--------------+------------------+
|   1 | Harry Potter and the Philosopher's Stone           | J. K. Rowling                            | Fantasy              |            4 |                4 |
|   2 | Sherlock Holmes: A Study in Scarlet                | Sir Arthur Conan Doyle                   | Detective/Mystery    |            3 |                2 |
|   3 | The Book Thief                                     | Marcus Zusak                             | Historical Fiction   |            4 |                4 |
|   4 | Life is What You Bake It                           | Vallery Lomas                            | Cookbook             |            2 |                1 |
|   5 | The Shining                                        | Stephen King                             | Horror               |            5 |                3 |
|   6 | The Da Vinci Code                                  | Dan Brown                                | Mystery/Thriller     |            2 |                1 |
|   7 | 7 Habits of Highly Effective People                | Stephen R. Covey                         | Self-Help            |            3 |                3 |
+-----+----------------------------------------------------+------------------------------------------+----------------------+--------------+------------------+
```

### **2. View the list of books issued by you**

This function looks at the current member's list of copies issued by them, and displays their details in a tabulated format.

```
> 2
+-----+----------------------------------------------------+--------------------------------+--------------------------------+------------------+
| ID  | Name                                               | Date of Issue                  | Due Date                       | Fine Due         |
+-----+----------------------------------------------------+--------------------------------+--------------------------------+------------------+
|   2 | Sherlock Holmes: A Study in Scarlet                | 06/03/2023                     | 13/03/2023             Overdue | Rs.            5 |
|   5 | The Shining                                        | 06/03/2023                     | 13/03/2023             Overdue | Rs.            5 |
+-----+----------------------------------------------------+--------------------------------+--------------------------------+------------------+

Total fine = Rs. 10
```

### **3. Search for a book by title, genre or author**

This function inputs search keywords and checks against every book's title, author and genre to see whether the input keywords are present in them. If yes, the search results are displayed in a tabulated format.

```
> 3
Enter search keyword (title, author, genre): Book
+-----+----------------------------------------------------+------------------------------------------+----------------------+--------------+------------------+
| ID  | Name                                               | Author                                   | Genre                | Total Copies | Copies Available |
+-----+----------------------------------------------------+------------------------------------------+----------------------+--------------+------------------+
|   3 | The Book Thief                                     | Marcus Zusak                             | Historical Fiction   |            4 |                4 |
+-----+----------------------------------------------------+------------------------------------------+----------------------+--------------+------------------+
```

### **4. Issue a book**

This function inputs a book ID (one can refer to the table created by command 1) and checks whether
1. The book ID exists
2. One of the copies of that book is available

If yes, it issues the book to the user.

If the user wants to cancel the operation, they can enter -1 as the book ID.

```
> 4
Enter the ID of the book you want to issue (enter -1 to cancel): 6
Book issued successfully.
```

**Note:** One member can issue only up to 5 copies at a time.

### **5. Return a book**

First, this function checks whether the member has any copies issued. If not, it exits the function.

Next, this function inputs a book ID (the member can refer to the table created by command 2) and checks whether the given book ID matches with the ID of one of the books that the member has issued.

It also checks whether there is any fine due using the due date and the current date. The user is asked to pay the fine and the book will not be returned unless the borrower pays the fine on the spot.

```
> 5
Enter the ID of the book you want to return: 5
This book is overdue by 1 day(s). You need to pay a fine of Rs. 5.
Pay fine? (y/n): y
Fine paid successfully.
Book returned successfully.
```

**Note:** The rate of fine is Rs. 5 * number of days due.

### **6. Change Password**

This function asks for the old password until the password matches with the current password of the member. Then it allows the member to input a new password, which is stored as their current password.

```
> 6
Enter old password: efgh
Incorrect password (4 attempts left).

Enter old password: abcd
Enter new password: ijkl 
Password changed successfully.
```

**Note**: A maximum of 5 attempts to enter the old password is allowed.

## Librarians

### **1. Viewing the list of books**

This function works the same way as "View the list of available books" does in the functionality for Members.

### **2. View the list of members**

This function allows the librarian to see the details of each member in tabulated format, along with the number of copies they have issued.

```
+-----+----------------------------------------------------+---------------+
| ID  | Name                                               | Copies Issued |
+-----+----------------------------------------------------+---------------+
|   1 | Harsh Modani                                       |             1 |
|   2 | Aryan Mishra                                       |             0 |
|   3 | Nikita Kiran                                       |             2 |
|   4 | Daksh Rajesh                                       |             0 |
|   5 | Divyam Sareen                                      |             1 |
|   6 | Dhruv Kothari                                      |             1 |
+-----+----------------------------------------------------+---------------+
```

### **3. Search for a book by title, genre or author**

This function works the same way as "Search for a book by title, author or genre" does in the functionality for Members.

### **4. Search for a member by name**

This function inputs search keywords and checks against every member's name to see whether the input keywords are present in them. If yes, the search results are displayed in a tabulated format.

```
> 4
Enter member name: Harsh
+-----+----------------------------------------------------+---------------+
| ID  | Name                                               | Copies Issued |
+-----+----------------------------------------------------+---------------+
|   1 | Harsh Modani                                       |             1 |
+-----+----------------------------------------------------+---------------+
```

### **5. Add a book or a copy of a book**

First, this function asks the librarian whether they want to add copies of a new book or add a single copy of a book already in the library.

If the librarian asked to add a new book, the details of the book and the number of copies that the librarian wishes to add are input. The book is added accordingly.

If the librarian asked to add a copy, the book ID of the existing book (the librarian can refer to the table made by command 1 or 3) and the copy ID of the copy to be added are input. The copy is added accordingly.

```
> 5
Enter the corresponding number to do the following:
1. Add a new book
2. Add copies to an existing book
> 1
Enter the book ID: 8
Enter the title of the book: Pride and Prejudice
Enter the author of the book: Jane Austen
Enter the genre of the book: Novel of manners
Enter the number of copies of the book: 4
Successfully added 4 copies of the book "Pride and Prejudice" to the collection.
```

**Note:** The maximum number of books that can be added to the library is 100, and the maximum number of copies of a single book that can be added is 5.

### **6. Remove a book or a copy of a book**

First, this function asks the librarian whether they want to remove all copies or remove a single copy of a book.

If the librarian asked to remove all copies, the book ID is input. The book is removed.

If the librarian asked to remove a single copy, the book ID of the existing book and the copy ID of the copy to be removed are input. The copy is added accordingly.

```
> 6      
Enter the corresponding number to do the following:
1. Remove a book
2. Remove a copy of a book
> 2
Enter the ID of the book: 5
Enter the ID of the copy that is to be removed: 4
Successfully removed the copy.
```

**Note:** Copies of books cannot be removed if they are issued to a member. Similarly, books altogether cannot be removed if even one of the copies is issued to a member.

### **7. Register a new member**

This function allows the librarian to input the details of a new member and add them to the library system.

```
> 7
Enter member ID: 8
Enter member name: Shiven Phogat
Enter member password: asdf
Successfully added member "Shiven Phogat".
```

**Note:** The maximum number of members that can be added to the library system is 100.

### **8. Remove a member**

This function allows the librarian to input the ID of the member to be removed from the library system. If the member ID does not match with any of the IDs of the existing members, it exits. Otherwise it removes the corresponding member.

```
> 8
Enter member ID: 4
Successfully removed member.
```

**Note:** The librarian cannot remove a member that has books issued against them.

### **9. Change Password**

This function works the same way as "Change Password" does in the functionality for Members. The only difference is that there is only one librarian and only one password for them, whereas each member has a unique password.

### **10. View books issued by a member**

This function allows the librarian to see the list of books that a single member has issued from the library. It takes the member ID as input.

If the member ID matches with one of the IDs of the existing members, it displays the details of the copies issued by the member, along with the fine due on the same.

If not, it exits.

```
> 10
Enter member ID: 5
Enter the date in DD/MM/YYYY format: 10/03/2023
+-----+----------------------------------------------------+--------------------------------+--------------------------------+------------------+
| ID  | Name                                               | Date of Issue                  | Due Date                       | Fine Due         |
+-----+----------------------------------------------------+--------------------------------+--------------------------------+------------------+
|   4 | Life is What You Bake It                           | 04/03/2023                     | 11/03/2023                     | Rs.            0 |
+-----+----------------------------------------------------+--------------------------------+--------------------------------+------------------+

Total fine = Rs. 0
```

## Running the app

To run the app, run the following commands in the terminal:

```
$ make main
$ ./a.out
```

Follow the prompts in the terminal.

**Note:** `make` does not work in a Windows-based terminal (CMD or PowerShell). Here, use the following command:

```
> gcc main.c book.c member.c io.c datefunctions.c librarianfunctions.c memberfunctions.c
> .\a.exe
```

## Contributions

Contributions are mentioned in the comments within the code, but here is an overview:

### 1. IMT2022010 Divyam Sareen

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">datefunctions.c</span>
</summary>
<br>

1. `int isLeapYear(int year)`
2. `void dateConverter(char *date, int *day, int *month, int *year)`
3. `int between0and9(char a)`
4. `int isValidDate(char date[])`
</details>

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">librarianfunctions.c</span>
</summary>
<br>

1. `int __librarianLogin(char passwd[])`
</details>

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">memberfunctions.c</span>
</summary>
<br>

1. `member *__memberLogin(member members[], int noOfMembers)`
</details>

### 2. IMT2022019 Daksh Rajesh

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">io.c</span>
</summary>
<br>

1. `void writePassword(char passwd[])`
2. `void printBookList(book books[], int noOfBooks)`
3. `void printMemberList(member members[], int noOfMembers)`
</details>

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">librarianfunctions.c</span>
</summary>
<br>

1. `int __librarianLoop(book books[], int *noOfBooks, member members[], int *noOfMembers, char passwd[])`
</details>

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">datefunctions.c</span>
</summary>
<br>

### memberfunctions.c
1. `int __memberLoop(book books[], int noOfBooks, member *member1)`
</details>

### 3. IMT2022028 Nikita Kiran

<span style="font-size=18px; font-weight=bold;">Makefile</span>

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">datefunctions.c</span>
</summary>
<br>

1. `char *getNextDate(char date[], int n)`
2. `char *getDueDate(char dateIssued[])`
3. `int compareDates(char date1[], char date2[])`
4. `int diffBtwDates(char date1[], char date2[])`
</details>

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">librarianfunctions.c</span>
</summary>
<br>

1. `void callAddBook(book books[], int *noOfBooks)`
2. `void removeMember(member members[], int *noOfMembers)`
3. `void searchMember(member members[], int noOfMembers)`
</details>

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">memberfunctions.c</span>
</summary>
<br>

1. `void issueBook(member *member1, book books[], int noOfBooks, char date[])`
2. `void returnBook(member *member1, book books[], int noOfBooks, char currDate[])`
3. `void displayIssuedBooks(member *member1, book books[], int noOfBooks, char currentDate[], int isLibrarianCalling)`
</details>

### 4. IMT2022055 Harsh Modani

<span style="font-size=18px; font-weight=bold;">README.md</span>

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">io.c</span>
</summary>
<br>

1. `void readMemberList(member members[], int *noOfMembers, book books[], int noOfBooks)`
2. `void readBookList(book books[], int *noOfBooks, member members[], int noOfMembers)`
3. `void writeBookList(book books[], int noOfBooks)`
4. `void writeMemberList(member members[], int noOfMembers)`
</details>

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">libraryfunctions.c</span>
</summary>
<br>

1. `void callRemoveBook(book books[], int *n, member members[], int noOfMembers)`
2. `void addMember(member members[], int *noOfMembers)`
</details>

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">memberfunctions.c</span>
</summary>
<br>

1. `void searchBook(book books[], int noOfBooks)`
</details>

### 5. IMT2022114 Dhruv Kothari

<span style="font-size=18px; font-weight=bold;">utils.h</span>

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">book.c</span>
</summary>
<br>

1. `book *getBookByID(book books[], int n, int id)`
2. `int addCopy(book *book1, int copyID)`
3. `int addBook(book books[], int *noOfBooks, book book1)`
4. `int copiesAvailable(book book1)`
</details>

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">member.c</span>
</summary>
<br>

1. `member *getMemberByID(member members[], int n, int id);`
</details>

### 6. IMT2022502 Aryan Mishra

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">librarianfunctions.c</span>
</summary>
<br>

1. `void changeLibrarianPassword(char passwd[])`
</details>

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">memberfunctions.c</span>
</summary>
<br>
1. `void changePassword(member *m)`
</details>

<details>
<summary>
<span style="font-size=18px; font-weight=bold;">main.c</span>
</summary>
<br>

1. `void __onInit(int *noOfBooks, int *noOfMembers, book books[], member members[], char password[])`
2. `void __onClose(book books[], member members[], int noOfBooks, int noOfMembers, char passwd[])`
3. `void __choose(char passwd[], member members[], int *noOfMembers, book books[], int *noOfBooks)`
4. `void main()` - the main function
</details>