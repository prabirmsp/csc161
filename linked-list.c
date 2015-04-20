/* A program shell  to maintain a linked list of names */

/* library for standard I/O */
#include <stdio.h>

/* library for memory allocation */
#include <stdlib.h>

/* Maximum length of names */
#define strMax 20

struct node
{ char data [strMax];
  struct node * next;
};

/* function prototypes, listed in alphabetical order */

void addName(struct node ** firstPtr);
/* pre-condition:  firstPtr points to the pointer
                   designating the head of a list
  post-condition:  a name is read and
                   inserted into the list at a designated place
*/

void countList (struct node * first);
/* pre-condition:  first designates the first node of a list 
  post-condition:  the number of items on the lsit is counted and printed
                   the list itself is unchanged
*/

void deleteName(struct node ** firstPtr);
/* pre-condition:  firstPtr points to the pointer designating the head of a list
  post-condition:  a name is read and
                   that name is deleted from the list
*/

void print(struct node * first);
/* pre-condition:  first designates the first node of a list 
  post-condition:  The items on the list are printed from first to last
                   the list itself is unchanged
  note:  processing proceeds iteratively
*/

void printRec(struct node * first);
/* pre-condition:  first designates the first node of a list 
  post-condition:  The items on the list are printed from first to last
                   the list itself is unchanged
  note:  processing proceeds recursively
*/

void printLast (struct node * first);
/* pre-condition:  first designates the first node of a list 
  post-condition:  the last item on the list is printed; 
                   the list itself is unchanged
  note:  processing proceeds iteratively
*/

void printLastRec (struct node * first);
/* pre-condition:  first designates the first node of a list 
  post-condition:  the last item on the list is printed; 
                   the list itself is unchanged
  note:  processing proceeds recursively
*/

void printReverse (struct node * first);
/* pre-condition:  first designates the first node of a list 
  post-condition:  The items on the list are printed from last to first
                   the list itself is unchanged
*/

void putFirst (struct node ** firstPtr);
/* pre-condition:  first designates the first node of a list 
  post-condition:  a name is read, located on the list,
                   and placed at the beginning of the list
  note:  processing proceeds iteratively
*/

int main (void) {
  /* program to coordinate the menu options and calls the requested function */

  struct node * first = NULL;   /* pointer to the first list item */
  char option[strMax];          /* user response to menu selection */

  printf ("Program to Maintain a List of Names\n");

  while (1) {
    /* print menu options */
    printf ("Options available\n");
    printf ("I - Insert a name into the list\n");
    printf ("D - Delete a name from the list\n");
    printf ("C - Count the number of items on the list\n");
    printf ("F - Move an item to the front of the list\n");
    printf ("L - Print the last item on the list (iteratively)\n");
    printf ("M - Print the last item on the list (recursively)\n");
    printf ("P - Print the names on the list (iteratively)\n");
    printf ("S - Print the names on the list (recursively)\n");
    printf ("R - Print the names in reverse order\n");
    printf ("Q - Quit\n");

    /* determine user selection */
    printf ("Enter desired option: ");
    scanf ("%s", option);
    
    switch (option[0])
      { case 'I':
        case 'i': 
          addName(&first);
          break;
        case 'D':
        case 'd': 
          deleteName(&first);
          break;
        case 'C':
        case 'c': 
          countList(first);
          break;
        case 'F':
        case 'f': 
          putFirst(&first);
          break;
        case 'L':
        case 'l': 
          printLast(first);
          break;
        case 'M':
        case 'm': 
          printLastRec(first);
          break;
        case 'P':
        case 'p': 
          print(first);
          break;
        case 'S':
        case 's': 
          printRec(first);
          break;
        case 'R':
        case 'r': 
          printReverse(first);
          break;
        case 'Q':
        case 'q':
          printf ("Program terminated\n");
          return 0;
          break;
        default: printf ("Invalid Option - Try Again!\n");
          continue;
      }
  }
}
        
void addName(struct node ** firstPtr) {
/* pre-condition:  firstPtr points to the pointer designating the head of a list
  post-condition:  a name is read and
                   inserted into the list at a designated place
*/

  char oldName [strMax];
  struct node * newNode = (struct node *) malloc(sizeof(struct node));
  struct node * listPtr;
  struct node * prevPtr;

   printf ("Enter name to be inserted into list: ");
   scanf ("%s", newNode->data);

   if (*firstPtr == NULL) {
     /* insert name's node at start of list */
     newNode->next = *firstPtr;
     *firstPtr = newNode;
   }
  
   else {
     printf ("Enter old name which new name should preceed, \n");
     printf ("or enter ? if new name should be placed last\n");
     scanf ("%s", oldName);

     if (strcmp (oldName, (*firstPtr)->data) == 0) {
       /* insert name's node at start of list */
       newNode->next = *firstPtr;
       *firstPtr = newNode;
     }
     else {
       /* insert name's node after start of the list */
       
       /* start at beginning of list */
       listPtr = (*firstPtr)->next;  /* the current node to search */
       prevPtr = *firstPtr;          /* the node behind listPtr */
       
       while (listPtr && (strcmp (oldName, listPtr->data) != 0)) {
         prevPtr = listPtr;
         listPtr = prevPtr->next;
       }

       newNode->next = prevPtr->next;
       prevPtr->next = newNode;
     }
   }
   printf ("%s inserted into the list\n\n", newNode->data);
}

void countList (struct node * first) {
/* pre-condition:  first designates the first node of a list 
  post-condition:  the number of items on the lsit is counted and printed
                   the list itself is unchanged
*/

  int counter = 0;
  struct node * list = first;
  while (list != NULL)
    {
      counter ++;
      list = list->next;
    }
  printf (" The list contains: %d items \n", counter);
}

void deleteName(struct node ** firstPtr) {
/* pre-condition:  firstPtr points to the pointer designating the head of a list
  post-condition:  a name is read and
                   that name is deleted from the list
*/
  char name [strMax];
  struct node * listPtr;
  struct node * prevPtr;

  if (*firstPtr) {
    printf ("Enter name to be deleted: ");
    scanf ("%s", name);

    if (strcmp (name, (*firstPtr)->data) == 0) {
      /* remove first item on list */
      listPtr = *firstPtr;
      *firstPtr = (*firstPtr)->next;
      free(listPtr);
      printf ("%s removed as first item on list\n\n", name);
    }
    else {
      /* item to remove is not at beginning of list */
      /* start at beginning of list */
      listPtr = (*firstPtr)->next;  /* the current node to search */
      prevPtr = *firstPtr;          /* the node behind listPtr */

      while (listPtr && (strcmp (name, listPtr->data) != 0)) {
        prevPtr = listPtr;
        listPtr = prevPtr->next;
      }
             
      if (listPtr) {
        /* remove item from list */
        prevPtr->next = listPtr->next;
        free (listPtr);
        printf ("%s deleted from list\n\n", name);
      }
      else {
        printf ("%s not found on list\n\n", name);
      }
    } /* end processing of name */
  }
  else {
    printf ("List is empty - no deletions are possible\n");
  } 
}

void print(struct node * first){
/* pre-condition:  first designates the first node of a list 
  post-condition:  The items on the list are printed from first to last
                   the list itself is unchanged
  note:  processing proceeds iteratively
*/    
  struct node * listElt = first;
  printf ("The names on the list are:\n\n");

  while (listElt) {
    printf ("%s\n", listElt->data);
    listElt = listElt->next;
  }

  printf ("\nEnd of List\n\n");
}

void printRec(struct node * first) {
/* pre-condition:  first designates the first node of a list 
  post-condition:  The items on the list are printed from first to last
                   the list itself is unchanged
                   note:  processing proceeds recursively
*/ 
  if (first) { // if the list is not NULL
    printf("%s\n", first->data);
    if (first->next)
      printRec(first->next);
  }
  else 
    printf("The list has no elements.\n\n");
}

void printLast (struct node * first) {
/* pre-condition:  first designates the first node of a list 
  post-condition:  the last item on the list is printed; 
                   the list itself is unchanged
  note:  processing proceeds iteratively
*/

  struct node * list = first;
  if (list == NULL)
    printf("LIST IS NULL\n");
  else {
    while (list->next != NULL)
      {
        list = list->next;
      }
    printf("LAST: %s\n", list->data);
  }



  printf ("Function printLast is not implemented at present\n\n");
}

void printLastRec (struct node * first) {
  /* pre-condition:  first designates the first node of a list 
     post-condition:  the last item on the list is printed; 
     the list itself is unchanged
     note:  processing proceeds recursively
  */
  if (first) { // if the list is not NULL
    if (first->next)
      printLastRec(first->next);
    else 
      printf("\nLast element: %s\n", first->data);
  }
  else 
    printf("The list has no elements.\n\n");
}

void printReverse (struct node * first) {
  /* pre-condition:  first designates the first node of a list 
     post-condition:  The items on the list are printed from last to first
     the list itself is unchanged
  */
  if (first) { // if the list is not NULL
    if (first->next)
      printReverse(first->next);
    printf("%s\n", first->data);
  }
  else 
    printf("The list has no elements.\n\n");
}

void putFirst (struct node ** firstPtr) {
/* pre-condition:  first designates the first node of a list 
  post-condition:  a name is read, located on the list,
                   and placed at the beginning of the list
*/
 char name [strMax];
  struct node * listPtr;
  struct node * prevPtr;

  if (*firstPtr) {
    printf ("Enter name to put first: ");
    scanf ("%s", name);

    if (strcmp (name, (*firstPtr)->data) == 0) {
      printf ("%s is already the first item on list\n\n", name);
    }
    else {
      /* item to move is not at beginning of list */
      /* start at beginning of list */
      listPtr = (*firstPtr)->next;  /* the current node to search */
      prevPtr = *firstPtr;          /* the node behind listPtr */

      while (listPtr && (strcmp (name, listPtr->data) != 0)) {
        prevPtr = listPtr;
        listPtr = prevPtr->next;
      }
             
      if (listPtr) {
        // skip the item that was moved to first
        if (listPtr->next) { // if the moved item is not the last element
          prevPtr->next = listPtr->next;
        }
        else prevPtr->next = NULL;
        
        // set next the previous first element as second
        listPtr->next = *firstPtr;

        // set element as first in the list
        *firstPtr = listPtr;
        
        printf ("%s moved to the first item on list\n\n", name);
      }
      else {
        printf ("%s not found on list\n\n", name);
      }
    } /* end processing of name */
  }
  else {
    printf ("List is empty - no moves are possible\n");
  } 
}

 


