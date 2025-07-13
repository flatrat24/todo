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
  int isAlpha = (priorityInput[0] >= 65 && priorityInput[0] <= 90);
  int singleCharacter = (strlen(priorityInput) == 1);
  if (singleCharacter && isAlpha) != 0) {
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
