#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Used for isupper()
#include "parseAndFormat.h"

void writeToFile(todoItem *(*itemArrayPointer)[], int *todoListSizePointer, char *filename) {
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    printf("Error opening file");
    return;
  } else {
    for (int i = 0; i < *todoListSizePointer; ++i) {
      char temp[200] = { '\0' };
      formatItem((*itemArrayPointer)[i], temp);
      fprintf(fp, "%s\n", temp);
      temp[0] = '\0';
    }
  }
  fclose(fp);
}

void readFromFile(char *filename, todoItem *(*itemArrayPointer)[], int *todoListSizePointer) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error opening file");
  } else {
    char line[200];
    int i = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
      line[strlen(line) - 1] = '\0';

      parseItem(line, (*itemArrayPointer)[i]);

      ++i;
      ++(*todoListSizePointer);
    }
  }
}

void printTodoList(todoItem *(*itemArrayPointer)[], int *todoListSizePointer) {
  for (int i = 0; i < *todoListSizePointer; ++i) {
    char temp[200] = { '\0' };
    formatItem((*itemArrayPointer)[i], temp);
    printf("%s\n", temp);
    temp[0] = '\0';
  }
}

void addTodoItem(todoItem *(*itemArrayPointer)[], int *todoListSizePointer) {
  if (*todoListSizePointer >= MAXITEMS) {
    printf("Maximum number of tasks in database.\n");
    return;
  } else {
    printf("Task description: ");
    char tempDescription[DESCRIPTIONLENGTH];
    if (fgets(tempDescription, sizeof(tempDescription), stdin) != NULL) {
      tempDescription[strlen(tempDescription) - 1] = '\0';
      strcpy((*itemArrayPointer)[*todoListSizePointer]->description, tempDescription);
    } else {
      printf("Error reading input.");
    }

    printf("Priority: ");
    char tempPriority[1];
    scanf("%s", tempPriority);
    (*itemArrayPointer)[*todoListSizePointer]->priority = tempPriority[0];

    printf("Context: ");
    char tempContext[CONTEXTLENGTH];
    scanf("%s", tempContext);
    strcpy((*itemArrayPointer)[*todoListSizePointer]->context, tempContext);

    printf("Project: ");
    char tempProject[PROJECTLENGTH];
    scanf("%s", tempProject);
    strcpy((*itemArrayPointer)[*todoListSizePointer]->project, tempProject);

    ++(*todoListSizePointer);
  }
}

void addTodoItem(todoItem *(*itemArrayPointer)[], int *todoListSizePointer) {
  ;
  // Only run if the database isn't already full.
  // Ask for a description of the task
  //  - Mandatory
  //  - Can't include @
  //  - Can't include +
  //  - Can't begin with 'x '
  //  - Can't begin with '(<Uppercase Letter>)'
  //  - Can't inlude '<str>:<str>' formatting
  // Ask for the priority of the task
  //  - Accepts any single alphabetical character
  //  - Can't be non-alphabetical
  //  - Can't be more than one character
  //  - If no characters, the attribute is not assigned
  // Ask for context
  //  - Single word, no other restrictions
  //  - If no characters, the attribute is not assigned
  // Ask for project
  //  - Single word, no other restrictions
  //  - If no characters, the attribute is not assigned
  // Ask for due-date:
  //  - Format in YYYY-MM-DD
  //  - Accept any non-number characters as delimiters
  //  - If no characters, the attribute is not assigned
  // Automatically assign a creation date
}

int main() {
  int todoListSize = 0;
  int *todoListSizePointer = &todoListSize;
  todoItem *itemArray[MAXITEMS];
  for (int i = 0; i < MAXITEMS; ++i) {
    itemArray[i] = malloc(sizeof(todoItem));
  }
  todoItem *(*itemArrayPointer)[] = &itemArray;

  readFromFile("todo.txt", itemArrayPointer, todoListSizePointer);

  addTodoItem(itemArrayPointer, todoListSizePointer);

  writeToFile(itemArrayPointer, todoListSizePointer, "todo.txt");

  printTodoList(itemArrayPointer, todoListSizePointer);
}
