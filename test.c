trig

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DESCRIPTIONLENGTH 50
#define PROJECTLENGTH 15
#define CONTEXTLENGTH 15
#define MAXCONTEXTS 10
#define MAXPROJECTS 10
#define MAXITEMS 100

typedef int bool;
#define true 1
#define false 0

typedef char context[CONTEXTLENGTH];

typedef char project[PROJECTLENGTH];

typedef struct {
    int year;
    int month;
    int day;
} date;

typedef struct {
    bool complete;
    date completionDate;
    date creationDate;
    char priority;
    char description[DESCRIPTIONLENGTH];
    context *contexts[MAXCONTEXTS];
    project *projects[MAXPROJECTS];
    date dueDate;
} todoItem;

typedef struct {
    todoItem items[MAXITEMS];
    int count;
} todoList;

void formatDate(date *input, char *output) {
  sprintf(output, "%04d-%02d-%02d", input->year, input->month, input->day);
}

void setValuesOfDate(date *input, int year, int month, int day) {
  input->year = year;
  input->month = month;
  input->day = day;
}

void printContexts(context *input) {
  int i = 0;
  while (input[i] != NULL) {
    printf("%s, ", input[i++]);
  }
  printf("\n");
}

void printTodoArray(todoItem *(*itemArrayPointer)[], int index) {
  printf("Complete: %d\n", (*itemArrayPointer)[index]->complete);
  char temp[10];
  formatDate(&((*itemArrayPointer)[index]->completionDate), temp);
  printf("Completion Date: %s\n", temp);
  formatDate(&((*itemArrayPointer)[index]->creationDate), temp);
  printf("Creation Date: %s\n", temp);
  formatDate(&((*itemArrayPointer)[index]->dueDate), temp);
  printf("Due Date: %s\n", temp);
  printf("Priority: %c\n", (*itemArrayPointer)[index]->priority);
  printf("Description: %s\n", (*itemArrayPointer)[index]->description);
  /* printf("Contexts: %s\n", ); */
  /* printf("Projects: %s\n", ); */
}

int main() {
  // Initialize the todo-list data structure
  int itemArraySize = 0;
  int *itemArraySizePointer = &itemArraySize;
  todoItem *itemArray[MAXITEMS];
  for (int i = 0; i < MAXITEMS; ++i) {
    itemArray[i] = malloc(sizeof(todoItem));
  }
  todoItem *(*itemArrayPointer)[] = &itemArray;

  for (int i = 0; i < MAXCONTEXTS; ++i) {
    context temp;
    (*itemArrayPointer)[0]->contexts[i] = &temp;
  }

  for (int i = 0; i < MAXPROJECTS; ++i) {
    context temp;
    (*itemArrayPointer)[0]->projects[i] = &temp;
  }


  // Testing
  (*itemArrayPointer)[0]->complete = false;
  setValuesOfDate(&((*itemArrayPointer)[0]->completionDate), 2000, 12, 31);
  setValuesOfDate(&((*itemArrayPointer)[0]->creationDate), 1888, 12, 31);
  setValuesOfDate(&((*itemArrayPointer)[0]->dueDate), 1999, 12, 31);
  (*itemArrayPointer)[0]->priority = 'A';
  strcpy((*itemArrayPointer)[0]->description, "Hello, World!");
  printTodoArray(itemArrayPointer, 0);

  strcpy(*((*itemArrayPointer)[0]->contexts[0]), "One");
  printContexts(*((*itemArrayPointer)[0]->contexts));
}
