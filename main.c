#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Used for todo.txt dates
#include <ctype.h> // Used for isupper()
#include "formats.h"
/* #include "defsAndStructs.h" */

int descendingOrder(const void *a, const void *b) {
    return -1 * ((*(int*)a - *(int*)b));
}

int ascendingOrder(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void writeToFile(todoList *todoList, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    } else {
        for (int i = 0; i < todoList->count; ++i) {
            fprintf(fp, "%c, %s\n", todoList->items[i].completion, todoList->items[i].description);
        }
    }
    fclose(fp);
}

void readFromFile(todoList *todoList, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    } else {
        todoList->count = 0;
        while (fscanf(fp, "%c, %[^\n]\n", &todoList->items[todoList->count].completion, todoList->items[todoList->count].description) == 2) {
            todoList->count ++;
            if (todoList->count >= MAXITEMS) {
                break;
            }
        }
    }
    fclose(fp);
}

/*todoItem createTask(char *input) { */
/*    todoItem returnItem; */
/*    context contexts[MAXCONTEXTS]; */
/*    project projects[MAXPROJECTS]; */

/*    char *token = strtok(input, " "); */
/*    char *tempList[50]; // 50 is a temp value until I use malloc() */
/*    int n; */
/*    for (n = 0; token != NULL; ++n) { */
/*        tempList[n] = token; */
/*        token = strtok(NULL, " "); */
/*    } */

/*    for (int i = 0; i < n; ++i) { */
/*        if (isDateFormat(tempList[i]) == 0) { */
/*            returnItem.creationDate = formatDate(tempList[i]); */
/*        } */
/*        /1* */
/*        if (item is a date) { */
/*            if (first date encountered) { */
/*                save current date to date created */
/*            } else if (second date encountered in a row) { */
/*                transfer date created to date completed */
/*                save current date to date created */
/*            } */
/*        } else if (item starts with @) { */
/*            add item to contexts list */
/*        } else if (item starts with +) { */
/*            save item to projects list */
/*        } else { */
/*            add item to description */
/*        } */
/*        *1/ */
/*    } */


/*    return returnItem; */
/*} */

void addTask(todoList *todoList, const char *description) {
    if (todoList->count >= DESCRIPTIONLENGTH) {
        printf("Max number of tasks reached.");
        return;
    } else {
        strcpy(todoList->items[todoList->count].description, description);
        todoList->items[todoList->count].completion = 'o';
        todoList->count ++;
    }
}

void removeTasks(todoList *todoList, int taskIndicies[DESCRIPTIONLENGTH], const int n) {
    qsort(taskIndicies, n, sizeof(int), descendingOrder);
    int previousIndex = '\0';
    for (int i = 0; i < n; ++i) {
        if (taskIndicies[i] != previousIndex) {
            if (todoList->count == 0 ) {
                printf("Todo list is currently empty.");
            } else if (taskIndicies[i] < 0 || taskIndicies[i] >= todoList->count) {
                printf("Invalid index.");
            } else {
                for (int j = taskIndicies[i]; j < todoList->count; ++j) {
                    strcpy(todoList->items[j].description, todoList->items[j+1].description);
                    todoList->items[j].completion = todoList->items[j+1].completion;
                }
                todoList->count --;
            }
            previousIndex = taskIndicies[i];
        }
    }
}

void toggleComplete(todoList *todoList, int taskIndicies[DESCRIPTIONLENGTH], const int n) {
    qsort(taskIndicies, n, sizeof(int), ascendingOrder);
    for (int i = 0; i < n; ++i) {
        if (todoList->count == 0 ) {
            printf("Todo todoList is currently empty.");
        } else if (taskIndicies[i] < 0 || taskIndicies[i] >= todoList->count) {
            printf("Invalid index.");
        } else {
            if (todoList->items[taskIndicies[i]].completion == 'o') {
                todoList->items[taskIndicies[i]].completion = 'x';
            } else {
                todoList->items[taskIndicies[i]].completion = 'o';
            }
        }
    }
}

void printList(todoList *todoList) {
    for (int i = 0; i < todoList->count; ++i) {
        printw("%d. [%c] - %s\n", i+1, (todoList->items[i].completion == 'x') ? 'x' : 'o', todoList->items[i].description);
    }
}

int main() {
    todoList todoList;
    todoList.count = 0;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    char fileName[] = "todo.txt";
    readFromFile(&todoList, fileName);

    int choice;
    char newTask[DESCRIPTIONLENGTH];

    do {
        clear();
        printw("<--- Manage Your Tasks --->\n");
        printw(". . . . . . . . . . . . . .\n");
        printList(&todoList);
        printw("\n\n");
        printw("1 -> Add new task.\n");
        printw("2 -> Remove task.\n");
        printw("3 -> Mark as complete.\n");
        printw("4 -> Save and quit.\n");
        printw("\nEnter your choice: ");
        refresh();

        echo();
        scanw("%d", &choice);
        noecho();
        refresh();

        switch (choice) {
            case 1: {
                clear();
                printList(&todoList);
                printw("Add new task: \n");
                echo();
                getstr(newTask);
                noecho();
                addTask(&todoList, newTask);
                break;
            }
            case 2: {
                /* Display current status of the todolist for the user */
                clear();
                printList(&todoList);
                printw("Remove tasks (index): \n");

                /* Get input from user formatted into a list of ints */
                char input[512]; // TODO: Replace 512 with a better value
                echo();
                getstr(input);
                noecho();
                refresh();
                clear();

                int n = 0;
                int taskIndicies[DESCRIPTIONLENGTH];
                char *token = strtok(input, " ");
                while (token != NULL && n < DESCRIPTIONLENGTH) {
                    taskIndicies[n++] = (atoi(token)) - 1;
                    token = strtok(NULL, " ");
                }

                removeTasks(&todoList, taskIndicies, n);

                refresh();
                break;
            }
            case 3: {
                /* Display current status of the todolist for the user */
                clear();
                printList(&todoList);
                printw("Toggle completion status (index): \n");

                /* Get input from user formatted into a list of ints */
                char input[512]; // TODO: Replace 512 with a better value
                echo();
                getstr(input);
                noecho();
                refresh();
                clear();

                int n = 0;
                int taskIndicies[DESCRIPTIONLENGTH];
                char *token = strtok(input, " ");
                while (token != NULL && n < DESCRIPTIONLENGTH) {
                    taskIndicies[n++] = (atoi(token)) - 1;
                    token = strtok(NULL, " ");
                }

                toggleComplete(&todoList, taskIndicies, n);

                refresh();
                break;
            }
        };

    } while (choice != 4);

    writeToFile(&todoList, fileName);

    endwin();
    return 0;
}
