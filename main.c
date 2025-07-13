#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parseAndFormat.h"
#include "createItem.h"
#include "helperFunctions.h"

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

int addTodoItem(todoItem *(*itemArrayPointer)[], int *todoListSizePointer) {
  if (*todoListSizePointer >= MAXITEMS) {
    printf("Todo list full, consider getting some shit done.");
  } else {
    char buffer[100]; // TODO: Find a better value for the length. Possibly malloc()?

    char description[DESCRIPTIONLENGTH];
    printf("Task Description: ");
    if (fgets(buffer, sizeof(description), stdin)) {
      char lastChar = buffer[strlen(buffer) - 1];
      buffer[strlen(buffer) - 1] = '\0';
      if (lastChar != '\n') {
        clearInputBuffer();
        printf("Error: Input too long.\n");
        return 1;
      } else if ((validDescriptionInput(buffer) != true)) {
        printf("Error: Formatting conflicts.\n");
        return 1;
      } else {
        strcpy(description, buffer);
      }
    } else {
      printf("Error: Couldn't read input.");
    }
    buffer[0] = '\0';

    char priority;
    printf("Task Priority: ");
    if (fgets(buffer, sizeof(priority+1), stdin)) {
      char lastChar = buffer[strlen(buffer) - 1];
      buffer[strlen(buffer) - 1] = '\0';
      if (lastChar != '\n') {
        clearInputBuffer();
        printf("Error: Input too long.\n");
        return 1;
      } else if ((validPriorityInput(buffer) == false)) {
        printf("Error: Formatting conflicts.\n");
        return 1;
      } else {
        priority = buffer[0];
      }
    } else {
      printf("Error: Couldn't read input.");
    }
    buffer[0] = '\0';

    char project[PROJECTLENGTH];
    printf("Task Priority: ");
    if (fgets(buffer, sizeof(project), stdin)) {
      char lastChar = buffer[strlen(buffer) - 1];
      buffer[strlen(buffer) - 1] = '\0';
      if (lastChar != '\n') {
        clearInputBuffer();
        printf("Error: Input too long.\n");
        return 1;
      } else if ((validProjectInput(buffer) != true)) {
        printf("Error: Formatting conflicts.\n");
        return 1;
      } else {
        strcpy(project, buffer);
      }
    } else {
      printf("Error: Couldn't read input.");
    }
    buffer[0] = '\0';

    char context[CONTEXTLENGTH];
    printf("Task Context: ");
    if (fgets(buffer, sizeof(context), stdin)) {
      char lastChar = buffer[strlen(buffer) - 1];
      buffer[strlen(buffer) - 1] = '\0';
      if (lastChar != '\n') {
        clearInputBuffer();
        printf("Error: Input too long.\n");
        return 1;
      } else if ((validContextInput(buffer) != true)) {
        printf("Error: Formatting conflicts.\n");
        return 1;
      } else {
        strcpy(context, buffer);
      }
    } else {
      printf("Error: Couldn't read input.");
    }
    buffer[0] = '\0';
  }
}

int main() {
  int todoArraySize = 0;
  int *todoArraySizePointer = &todoArraySize;
  todoItem *itemArray[MAXITEMS];
  for (int i = 0; i < MAXITEMS; ++i) {
    itemArray[i] = malloc(sizeof(todoItem));
  }
  todoItem *(*itemArrayPointer)[] = &itemArray;

  (*itemArrayPointer)[0]->complete = 0;
  printf("%d\n", (*itemArrayPointer)[0]->complete);

  for (int i = 0; i < MAXCONTEXTS; ++i) {
    context temp;
    (*itemArrayPointer)[0]->contexts[i] = &temp;
  }
  for (int i = 0; i < MAXPROJECTS; ++i) {
    context temp;
    (*itemArrayPointer)[0]->projects[i] = &temp;
  }
}
