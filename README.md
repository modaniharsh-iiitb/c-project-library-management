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
```
### **2. View the list of books issued by you**

This function looks at the current member's list of copies issued by them, and displays their details in a tabulated format.

```
```

### **3. Search for a book by title, genre or author**

This function inputs search keywords and checks against every book's title, author and genre to see whether the input keywords are present in them. If yes, the search results are displayed in a tabulated format.

```
```

### **4. Issue a book**

This function inputs a book ID (one can refer to the table created by command 1) and checks whether
1. The book ID exists
2. One of the copies of that book is available

If yes, it issues the book to the user.

If the user wants to cancel the operation, they can enter -1 as the book ID.

```
```

**Note:** One member can issue only up to 5 copies at a time.

### **5. Return a book**

First, this function checks whether the member has any copies issued. If not, it exits the function.

Next, this function inputs a book ID (the member can refer to the table created by command 2) and checks whether the given book ID matches with the ID of one of the books that the member has issued.

It also checks whether there is any fine due using the due date and the current date. The user is asked to pay the fine and the book will not be returned unless the borrower pays the fine on the spot.

```
```

**Note:** The rate of fine is Rs. 5 * number of days due.

### **6. Change Password**

This function asks for the old password until the password matches with the current password of the member. Then it allows the member to input a new password, which is stored as their current password.

```
```

**Note**: A maximum of 5 attempts to enter the old password is allowed.

## Librarians

### **1. Viewing the list of books**

This function works the same way as "View the list of available books" does in the functionality for Members.

### **2. View the list of members**

This function allows the librarian to see the details of each member in tabulated format, along with the number of copies they have issued.

```
```

### **3. Search for a book by title, genre or author**

This function works the same way as "Search for a book by title, author or genre" does in the functionality for Members.

### **4. Search for a member by name**

This function inputs search keywords and checks against every member's name to see whether the input keywords are present in them. If yes, the search results are displayed in a tabulated format.

```
```

### **5. Add a book or a copy of a book**

First, this function asks the librarian whether they want to add copies of a new book or add a single copy of a book already in the library.

If the librarian asked to add a new book, the details of the book and the number of copies that the librarian wishes to add are input. The book is added accordingly.

If the librarian asked to add a copy, the book ID of the existing book (the librarian can refer to the table made by command 1 or 3) and the copy ID of the copy to be added are input. The copy is added accordingly.

```
```

**Note:** The maximum number of books that can be added to the library is 100, and the maximum number of copies of a single book that can be added is 5.

### **6. Remove a book or a copy of a book**

First, this function asks the librarian whether they want to remove all copies or remove a single copy of a book.

If the librarian asked to remove all copies, the book ID is input. The book is removed.

If the librarian asked to remove a single copy, the book ID of the existing book and the copy ID of the copy to be removed are input. The copy is added accordingly.

```
```

**Note:** Copies of books cannot be removed if they are issued to a member. Similarly, books altogether cannot be removed if even one of the copies is issued to a member.

### **7. Register a new member**

This function allows the librarian to input the details of a new member and add them to the library system.

```
```

**Note:** The maximum number of members that can be added to the library system is 100.

### **8. Remove a member**

This function allows the librarian to input the ID of the member to be removed from the library system. If the member ID does not match with any of the IDs of the existing members, it exits. Otherwise it removes the corresponding member.

```
```

**Note:** The librarian cannot remove a member that has books issued against them.

### **9. Change Password**

This function works the same way as "Change Password" does in the functionality for Members. The only difference is that there is only one librarian and only one password for them, whereas each member has a unique password.

### **10. View books issued by a member**

This function allows the librarian to see the list of books that a single member has issued from the library. It takes the member ID as input.

If the member ID matches with one of the IDs of the existing members, it displays the details of the copies issued by the member, along with the fine due on the same.

If not, it exits.

```
```

## Running the app

To run the app, run the following commands in the terminal:

```
$ make main
$ ./a.out
```

Follow the prompts in the terminal.

## Contributions

Contributions are mentioned in the comments within the code, but here is an overview:

### 1. IMT2022010 Divyam Sareen

### datefunctions.c
1. `int isLeapYear(int year)`
2. `void dateConverter(char *date, int *day, int *month, int *year)`
3. `int between0and9(char a)`
4. `int isValidDate(char date[])`

### memberfunctions.c
1. `member *__memberLogin(member members[], int noOfMembers)`

### librarianfunctions.c
1. `int __librarianLogin(char passwd[])`

### 2. IMT2022019 Daksh Rajesh

### <span color="#00ff00">io.c</span>
1. `void writePassword(char passwd[])`
2. `void printBookList(book books[], int noOfBooks)`
3. `void printMemberList(member members[], int noOfMembers)`

### librarianfunctions.c
1. `int __librarianLoop(book books[], int *noOfBooks, member members[], int *noOfMembers, char passwd[])`

### memberfunctions.c
1. `int __memberLoop(book books[], int noOfBooks, member *member1)`

### 3. IMT2022028 Nikita Kiran



### 4. IMT2022055 Harsh Modani
### 5. IMT2022114 Dhruv Kothari
### 6. IMT2022502 Aryan Mishra
