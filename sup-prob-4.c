
    /***********************************************************************
     * Name: Prabir Pradhan                                                *
     * Box:  #4136                                                         *
     * Assignment name: Supplemental Problem 4 - Library Book Borrowing    *
     * Assignment for: April 20, 2015                                      *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *     Documentation for 'strcmp()'                                    *
     *        <http://www.tutorialspoint.com/c_standard_library/           *
     *         c_function_strcmp.htm>                                      *
     *   Help obtained:                                                    *
     *     [None Additional]                                               *
     *   My/our signature(s) below confirms that the above list of sources *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                                                                     *
     *                                                                     *
     *   Signature:                                                        *
     *                                                                     *
     ***********************************************************************/

#include <stdio.h>
#include <ctype.h> 
#include <string.h>
#include <stdlib.h>

#define MAX_STR 100 // length of all strings
#define MAX_BOOKS 5 // maximum number of books that can be checked out

struct item {
	char name [MAX_STR];
	int numBooks;
	char booksBorrowed [MAX_BOOKS] [MAX_STR];
	char dueDate [MAX_STR];
	struct item * next;
};

/* Procedure: getStringInput
 * Parameters: str, a pointer to a char array;
 * Purpose: get a string input from input stream and store it in str;
 * Preconditions: [None Additional]
 * Postconditions: the string stored in str is in all lowercase;
 */
void getStringInput (char * str);

/* Procedure: checkout
 * Parameters: first, a pointer to a pointer to the first item in the 
 *   list of items;
 * Purpose: add a new item to the front of the list after getting details 
 *   from user input;
 * Preconditions: [None Additional]
 * Postconditions: a new item is allocated in memory;
 */
void checkout (struct item ** first);

/* Procedure: printItem
 * Parameters: Item, a pointer to an item; 
 * Purpose: print the details of the item pointed to by Item to 
 *   the output stream;
 * Preconditions: Item is not NULL;
 * Postconditions: [None Additional]
 */
void printItem (struct item * Item);

/* Procedure: printAllItems
 * Parameters: first, a pointer to the first item in the list of items;
 * Purpose: print the details of all of the items in the list of items
 *   to the output stream;
 * Preconditions: [None Additional]
 * Postconditions: [None Additional]
 */
void printAllItems (struct item * first);

/* Procedure: search
 * Parameters: first, a pointer to a pointer to the first item in the 
 *   list of items;
 * Purpose: find and print the details of a specific item in the list
 *   of items;
 * Preconditions: [None Additional]
 * Postconditions: if the searched user is found, the item containing 
 *   the user's data is shifted one place towards the the beginning of
 *   the list; if the searched user is already first, no changes are made;
 */
void search (struct item ** first);

/* Procedure: returnBook
 * Parameters: first, a pointer to a pointer to the first item in the 
 *   list of items;
 * Purpose: remove a specific string (book title) from the array 
 *   booksBorrowed in a specific item;
 * Preconditions: [None Additional]
 * Postconditions: if the removed book is the only book in booksBorrowed,
 *   the item is deleted; if the removed book is not the last non-NULL 
 *   string in booksBorrowed, the books proceeding the removed book in
 *   booksBorrowed are moved one place towards the beginning of the array;
 */
void returnBook (struct item ** first);

int main () {
	// print title
	printf("\nLibrary Books - Supplemental Problem 4\n"
		   "    by Prabir Pradhan\n");

	struct item * first = NULL; // pointer to the first item in the list

	while (1) { // run until the program is terminated

		// print menu options
		printf("\n Library Checkout  Options:\n"
			   " --------------------------\n"
   			   "   C:  Check out 1-5 books (if no books currently checked out)\n"
   			   "   P:  Print all Residents with Checked Out Books\n"
   			   "   S:  Search for User\n"
   			   "   R:  Return a Book\n"
   			   "   Q:  Quit\n\n");
		printf("Enter Option: ");
		char option = getchar(); // get option input
		while (getchar() != '\n'); // clear input stream
		putchar('\n');

		switch (option) {
			case 'c': // checkout
			checkout(&first);
			break;
			case 'p': // print
			printAllItems(first);
			break;
			case 's': // search
			search(&first);
			break;
			case 'r': //  return
			returnBook(&first);
			break;
			case 'q': //  quit
				printf("Program terminated.\n");
				return 0;
			default:
			printf("\nThe input was invalid. Please try again.\n");
			break;
		}
	}
}

void getStringInput (char * str) {
	char c;
	int i = 0;
	while (((c = getchar()) != '\n') && i < MAX_STR-1)
		str[i++] = c; // store input in str
	str[i] = 0; // end the str with NULL

	for (int j = 0; str[j]; j++)
		str[j] = tolower(str[j]); // convert to lowercase
}

void checkout (struct item ** first) {
	struct item * currentP;

	// get data from input
	char username[MAX_STR];
	printf("Username: ");
	getStringInput(username);
	currentP = *first;

	// search for the user in the list
	while (currentP && strcmp(username, currentP->name)) // search for user
		currentP = currentP->next;

	if (currentP && !strcmp(username, currentP->name)) { // if existing user found
			printf("Existing user found with %d books checked out.\n"
				   "Return all books to check out more books.\n", currentP->numBooks);
	}
	else { // if no existing user found - create new user
		printf("Number of books to check out (1-%d): ", MAX_BOOKS);
		int books;
		scanf("%d", &books);
		while (getchar() != '\n'); // clear input stream until newline
		if (books > 0 && books <= MAX_BOOKS) {
			struct item * newItem = (struct item *) malloc(sizeof(struct item)); // create new item
			strcpy(newItem->name, username); // set the name
			newItem->numBooks = books; // set number of books checked out
			for (int i = 0; i < books; i++) { // set book titles
				printf("Title of book %d: ", i+1);
				getStringInput(newItem->booksBorrowed[i]);
			}
			printf("Enter due date: ");
			getStringInput(newItem->dueDate); // set due date
			newItem->next = *first; // set current first item as second
			*first = newItem; // set newItem as the first item
		}
		else { // number of books is not between 1 and MAX_BOOKS
			printf("You cannot check out that many books.\n");
		}
	}
}

void printItem (struct item * Item) {
	printf(" * User: %s\n", Item->name); 
	printf("     Books Checked Out: %d\n", Item->numBooks);
	for (int i = 0; i < Item->numBooks; i++) 
		printf("       - Book %d: %s\n", i+1, Item->booksBorrowed[i]);
	printf("     Due Date: %s\n\n", Item->dueDate);
}

void printAllItems (struct item * first) {
	struct item * currentP;

	if (first) { // if list is not empty
		printf("--- BEGIN USER LIST ---\n\n");
		currentP = first;
		while (currentP) { 
				printItem(currentP);
				currentP = currentP->next; // move to the next user on the list
		} 
		printf("--- END USER LIST ---\n");
	}
	else // empty list
		printf("There are no users with checked out books.\n");
}


void search (struct item ** first) {
	struct item * currentP; // pointer to current item
	struct item * previousP1; // pointer to previous item
	struct item * previousP2; // pointer to second previous item

	// get name input
	char username[MAX_STR];
	printf("Username: ");
	getStringInput(username);
	currentP = *first;
	previousP1 = (struct item *) *first;

	// search for the user in the list
	while (currentP && strcmp(username, currentP->name)) {
		// move to next item
		previousP2 = previousP1;
		previousP1 = currentP;
		currentP = currentP->next;
	}

	if (currentP && !strcmp(username, currentP->name)) { // if existing user found
		printf("\nUser Info\n---------\n");
		printItem(currentP); // print the user's info
		if (currentP != *first) { // user is not already first
			previousP1->next = currentP->next;
			currentP->next = previousP1;
			if (previousP1 == *first) // user is second on list
				*first = currentP;
			else
				previousP2->next = currentP;
		}
	}
	else 
		printf("No user found by the name \"%s\".\n", username);
}

void returnBook (struct item ** first) {
	struct item * currentP;
	struct item * previousP1;

	// get data input
	char username[MAX_STR];
	printf("Username: ");
	getStringInput(username);
	currentP = *first;

	// search for the user in the list
	while (currentP && strcmp(username, currentP->name)) {
		// move to the next item
		previousP1 = currentP;
		currentP = currentP->next;
	}

	if (currentP && !strcmp(username, currentP->name)) { // if existing user found
		char title [MAX_STR];
		printf("Title: ");
		getStringInput(title);
		int i = 0;
		// search for book in booksBorrowed array
		while ((i < currentP->numBooks) && strcmp(title, currentP->booksBorrowed[i]))
			i++;
		if (!strcmp(title, currentP->booksBorrowed[i])) { // checked out book found
			if (!(currentP->numBooks-1)) { // if only 1 book checked out
				// DELETE USER
				if (currentP == *first) // user is first in list
					*first = currentP->next;
				else // user is not first in list
					previousP1->next = currentP->next;
				free(currentP); // delete item
				printf("This user has no more books checked out.\n");
			}
			else { // more than 1 book checked out
				if (i != currentP->numBooks-1) { // if it's not the last book in array
					while (i < currentP->numBooks-1) { 
						for(int j = 0; j < MAX_STR; j++) // shift the book titles down
							currentP->booksBorrowed[i][j] = currentP->booksBorrowed[i+1][j];
						i++;
					}
				}
				for (int j = 0; j < MAX_STR; j++) // delete the last book title
					currentP->booksBorrowed[i][j] = 0;
				currentP->numBooks = currentP->numBooks-1;
				printf("The book \"%s\" has been returned.\n", title);
			}
		}
		else // book not found
			printf("That book was not found.\n");
		
	}
	else // user not found
		printf("There are no users by that name. \n");
}