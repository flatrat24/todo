#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "defsAndStructs.h"

todoItem initializeTodoItem() {
  todoItem returnItem;
  returnItem.completion = '\0';
  returnItem.priority = '\0';
  strcpy(returnItem.description, "");
  returnItem.creationDate.year = 0;
  returnItem.creationDate.month = 0;
  returnItem.creationDate.day = 0;
  returnItem.completionDate.year = 0;
  returnItem.completionDate.month = 0;
  returnItem.completionDate.day = 0;
  returnItem.dueDate.year = 0;
  returnItem.dueDate.month = 0;
  returnItem.dueDate.day = 0;
  strcpy(returnItem.context, "");
  strcpy(returnItem.project, "");
  return returnItem;
}

void parseCompletion(char *input, char *output) {
  *output = input[0];
}

void formatCompletion(char input, char output[]) {
  if (input == 'x') {
    strcpy(output, "x");
  }
}

int isCompletionFormat(char *input) {
  char completion;
  int n;
  if (sscanf(input, "%c%n", &completion, &n) != 1) {
    return 1;
  }
  if (completion != 'x') {
    return 1;
  }
  if (input[n] != '\0') {
    return 1;
  }
  return 0;
}

void parseDate(char *input, date *output) {
  int day, month, year, n;
  sscanf(input, "%4d-%2d-%2d%n", &year, &month, &day, &n);
  output->year = year; output->month = month; output->day = day;
}

void formatDate(date *input, char *output) {
  sprintf(output, "%04d-%02d-%02d", input->year, input->month, input->day);
}

int isDateFormat(char *input) {
  int day, month, year, n;
  if (sscanf(input, "%4d-%2d-%2d%n", &year, &month, &day, &n) != 3) {
    return 1;
  }
  if (input[n] != '\0') {
    return 1;
  }
  return 0;
}

void parsePriority(char *input, char *output) {
  *output = input[1];
}

void formatPriority(char input, char *output) {
  sprintf(output, "(%c)", input);
}

int isPriorityFormat(char *input) {
  char priority;
  int n;
  if (sscanf(input, "(%c)%n", &priority, &n) != 1) {
    return 1;
  }
  if (isupper(priority) == 0) {
    return 1;
  }
  if (input[n] != '\0') {
    return 1;
  }
  return 0;
}

void parseContext(char *input, char *output) {
  input++;
  strcpy(output, input);
}

void formatContext(char *input, char *output) {
  sprintf(output, "@%s", input);
}

int isContextFormat(char *input) {
  int i = 0;
  if (input[i++] != '@') {
    return 1;
  }
  while (input[i] != '\0') {
    if (isspace(input[i++]) != 0) {
      return 1;
    }
  }
  return 0;
}

void parseProject(char *input, char *output) {
  input++;
  strcpy(output, input);
}

void formatProject(char *input, char *output) {
  sprintf(output, "+%s", input);
}

int isProjectFormat(char *input) {
  int i = 0;
  if (input[i++] != '+') {
    return 1;
  }
  while (input[i] != '\0') {
    if (isspace(input[i++]) != 0) {
      return 1;
    }
  }
  return 0;
}

int isDueDateFormat(char *input) {
  char date[10];
  int n;
  if (sscanf(input, "due:%s%n", date, &n) != 1) {
    return 1;
  }
  return isDateFormat(date);
}

void formatDueDate(date *input, char *output) {
  sprintf(output, "due:%04d-%02d-%02d", input->year, input->month, input->day);
}

void parseDueDate(char *input, date *output) {
  int day, month, year, n;
  sscanf(input, "due:%4d-%2d-%2d%n", &year, &month, &day, &n);
  output->year = year; output->month = month; output->day = day;
}

void parseItem(char *input, todoItem *output) {
  char description[DESCRIPTIONLENGTH] = {'\0'};

  char *token = strtok(input, " ");
  if (isCompletionFormat(token) == 0) {
    parseCompletion(token, &output->completion);
    token = strtok(NULL, " ");
  } else {
    output->completion = 'o';
  }
  if (isDateFormat(token) == 0) {
    if (output->completion == 'x') {
      parseDate(token, &output->completionDate);
      token = strtok(NULL, " ");
      if (isPriorityFormat(token) == 0) {
        parsePriority(token, &output->priority);
        token = strtok(NULL, " ");
        if (isDateFormat(token) == 0) {
          parseDate(token, &output->creationDate);
          token = strtok(NULL, " ");
        }
      }
    } else if (output->completion == 'o') {
      parseDate(token, &output->creationDate);
      token = strtok(NULL, " ");
    }
  } else if (isPriorityFormat(token) == 0) {
    parsePriority(token, &output->priority);
    token = strtok(NULL, " ");
    if (isDateFormat(token) == 0) {
      parseDate(token, &output->creationDate);
      token = strtok(NULL, " ");
    }
  }
  while (token != NULL) {
    if (isContextFormat(token) == 0) {
      parseContext(token, output->context);
    } else if (isProjectFormat(token) == 0) {
      parseProject(token, output->project);
    } else if (isDueDateFormat(token) == 0) {
      parseDueDate(token, &output->dueDate);
    } else if (strlen(description) + strlen(token) <= DESCRIPTIONLENGTH) {
      strcat(description, token);
      strcat(description, " ");
    }
    token = strtok(NULL, " ");
  }

  description[strlen(description) - 1] = '\0';
  strcpy(output->description, description);
}

void formatItem(todoItem *item, char *output) {
  if (item->completion == 'x') {
    char temp[1];
    formatCompletion(item->completion, temp);
    strcat(output, temp);
    strcat(output, " ");
    if (item->completionDate.year != 0) {
      char temp[10];
      formatDate(&item->completionDate, temp);
      strcat(output, temp);
      strcat(output, " ");
      if (item->creationDate.year != 0) {
        char temp[10];
        formatDate(&item->creationDate, temp);
        strcat(output, temp);
        strcat(output, " ");
      }
    }
  }
  if (item->priority != '\0') {
    char temp[1];
    formatPriority(item->priority, temp);
    strcat(output, temp);
    strcat(output, " ");
  }
  if (strcmp(item->description, "") != 0) {
    strcat(output, item->description);
    strcat(output, " ");
  }
  if (strcmp(item->context, "") != 0) {
    char temp[CONTEXTLENGTH];
    formatContext(item->context, temp);
    strcat(output, temp);
    strcat(output, " ");
  }
  if (strcmp(item->project, "") != 0) {
    char temp[PROJECTLENGTH];
    formatProject(item->project, temp);
    strcat(output, temp);
    strcat(output, " ");
  }
  if (item->dueDate.year != 0) {
    char temp[10];
    formatDueDate(&item->dueDate, temp);
    strcat(output, temp);
    strcat(output, " ");
  }
}
