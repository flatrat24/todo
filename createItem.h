#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Used for isupper()

typedef int bool;
#define true 1
#define false 0

int validContextInput (char *contextInput) {
  if (contextInput[0] != '@') {
    return false;
  }

  char *token = strtok(contextInput, " ");
  if (strtok(NULL, " ") != NULL) {
    return false;
  }

  return true;
}

int validProjectInput (char *projectInput) {
  if (projectInput[0] != '+') {
    return false;
  }

  char *token = strtok(projectInput, " ");
  if (strtok(NULL, " ") != NULL) {
    return false;
  }

  return true;
}

int validKeyValueInput (char *keyValueInput) {
  char *token = strtok(keyValueInput, " ");
  if (strtok(NULL, " ") != NULL) {
    return false;
  }

  int colonCount = 0;
  for (int i = 0; i < strlen(token); ++i) {
    if (token[i] == ':') {
      ++colonCount;
      if (colonCount > 1) {
        return false;
      }
    }
  }

  if (colonCount == 1) {
    return true;
  } else {
    return false;
  }
}

int validPriorityInput (char *priorityInput) {
  if (strlen(priorityInput) == 1 && isalpha(priorityInput[0]) != 0) {
    return true;
  } else {
    return false;
  }
}

int validDescriptionInput(char *descriptionInput) {
  char *token = strtok(descriptionInput, " ");

  do {
    int ConflictWithOtherTypes = validPriorityInput(token) || validProjectInput(token) || validContextInput(token) || validKeyValueInput(token);
    if (ConflictWithOtherTypes) {
      return false;
    }
  } while (strtok(NULL, " ") != NULL);

  return true;
}


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
