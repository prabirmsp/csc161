/* 
CITATION
http://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm
*/


#include <stdio.h>
#include <ctype.h> 
#include <string.h>
#include <stdlib.h>

#define MAX_STR 100
#define MAX_BOOKS 5

struct item {
	char name [MAX_STR];
	int numBooks;
	char booksBorrowed [MAX_BOOKS] [MAX_STR];
	char dueDate [MAX_STR];
	struct item * next;
};

void getStringInput (char * str);

void checkout (struct item ** first);

void printItem (struct item * Item);

void printAllItems (struct item * first);

void search (struct item ** first);

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
		while (getchar() != '\n'); // clear any additional characters until end of line
		putchar('\n');

		switch (option) {
			case 'c': case 'C': // checkout
			checkout(&first);
			break;
			case 'p': case 'P': // print
			printAllItems(first);
			break;
			case 's': case 'S': // search
			search(&first);
			break;
			case 'r': case 'R': //  return
			returnBook(&first);
			break;
			case 'q': case 'Q': //  quit
				printf("Program terminated.\n");
				return 0;
			default:
			printf("\nThe input was invalid. Please try again.\n");
			break;
		}
	}
}


void getStringInput (char * str) {
	//scanf("%s", str);
	//while (getchar()!='\n');
	
	char c;
	int i = 0;
	while ((c = getchar()) != '\n') {
		str[i++] = c;
	}
	str[i] = 0;

	for (int j = 0; str[j]; j++) // convert to lowercase
		str[j] = tolower(str[j]);
}

void checkout (struct item ** first) {
	struct item * currentP;

	// get data from input
	char username[MAX_STR];
	printf("Username: ");
	getStringInput(username);
	currentP = *first;

	// search for the user in the list
	while (currentP && strcmp(username, currentP->name)) { // search for user
		currentP = currentP->next;
	}
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
			newItem->next = *first;
			*first = newItem;
		}
		else { // number of books is not between 1 and 5
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

	if (first) {
		printf("--- BEGIN USER LIST ---\n\n");
		currentP = first;
		while (currentP) { 
				printItem(currentP);
				currentP = currentP->next; // move to the next user on the list
		} 
		printf("--- END USER LIST ---\n");
	}
	else
		printf("There are no users with checked out books.\n");
}


void search (struct item ** first) {
	struct item * currentP;
	struct item * previousP1;
	struct item * previousP2;
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
		while ((i < currentP->numBooks) && strcmp(title, currentP->booksBorrowed[i]))
			i++;
		if (!strcmp(title, currentP->booksBorrowed[i])) { // checked out book found
			printf("booksoufn");
			if (currentP->numBooks == 1) { // if only 1 book checked out
				// DELETE USER
				if (currentP == *first) // user is first in list
					*first = currentP->next;
				else // user is not first in list
					previousP1->next = currentP->next;
				free(currentP); // delete user
				printf("This user has no more books checked out.\n");
			}
			else { // more than 1 book checked out
				printf("LLLSLS");
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