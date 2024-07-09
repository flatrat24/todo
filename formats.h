#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "defsAndStructs.h"

void formatCompletion(char *input, char *output) {
    *output = input[0];
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

void formatPriority(char *input, char *output) {
    *output = input[1];
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

void formatDate(char *input, date *output) {
    int day, month, year, n;
    sscanf(input, "%4d-%2d-%2d%n", &year, &month, &day, &n);
    output->year = year; output->month = month; output->day = day;
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

void formatContext(char *input, char *output) {
    int i = 1;
    while (input[i] != '\0') {
        output[i-1] = input[i];
        ++i;
    }
    output[i-1] = '\0';
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

/* int isContextFormat(char *input) { */
/*     char context[CONTEXTLENGTH]; */
/*     int n; */
/*     if (sscanf(input, "@%s%n", &context, &n) != 1) { */
/*         return 1; */
/*     } */
/*     if (input[n] != '\0') { */
/*         return 1; */
/*     } */
/*     return 0; */
/* } */

void formatProject(char *input, char *output) {
    int i = 1;
    while (input[i] != '\0') {
        output[i-1] = input[i];
        ++i;
    }
    output[i-1] = '\0';
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

/* int isProjectFormat(char *input) { */
/*     char project[PROJECTLENGTH]; */
/*     int n; */
/*     if (sscanf(input, "@%s%n", &project, &n) != 1) { */
/*         return 1; */
/*     } */
/*     if (input[n] != '\0') { */
/*         return 1; */
/*     } */
/*     return 0; */
/* } */
