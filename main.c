#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 50
#define MAXITEMS 100

typedef struct {
    char task[MAXLENGTH];
    int completed;
} todoItem;

typedef struct {
    todoItem items[MAXITEMS];
    int count;
} todoList;

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
            fprintf(fp, "%d, %s\n", todoList->items[i].completed, todoList->items[i].task);
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
        while (fscanf(fp, "%d, %[^\n]\n", &todoList->items[todoList->count].completed, todoList->items[todoList->count].task) == 2) {
            todoList->count ++;
            if (todoList->count >= MAXITEMS) {
                break;
            }
        }
    }
    fclose(fp);
}

void addTask(todoList *todoList, const char *task) {
    if (todoList->count >= MAXLENGTH) {
        printf("Max number of tasks reached.");
        return;
    } else {
        strcpy(todoList->items[todoList->count].task, task);
        todoList->items[todoList->count].completed = 0;
        todoList->count ++;
    }
}

void removeTasks(todoList *todoList, int taskIndicies[MAXLENGTH], const int n) {
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
                    strcpy(todoList->items[j].task, todoList->items[j+1].task);
                    todoList->items[j].completed = todoList->items[j+1].completed;
                }
                todoList->count --;
            }
            previousIndex = taskIndicies[i];
        }
    }
}

void toggleComplete(todoList *todoList, int taskIndicies[MAXLENGTH], const int n) {
    qsort(taskIndicies, n, sizeof(int), ascendingOrder);
    for (int i = 0; i < n; ++i) {
        if (todoList->count == 0 ) {
            printf("Todo todoList is currently empty.");
        } else if (taskIndicies[i] < 0 || taskIndicies[i] >= todoList->count) {
            printf("Invalid index.");
        } else {
            if (todoList->items[taskIndicies[i]].completed == 0) {
                todoList->items[taskIndicies[i]].completed = 1;
            } else {
                todoList->items[taskIndicies[i]].completed = 0;
            }
        }
    }
}

void printList(todoList *todoList) {
    for (int i = 0; i < todoList->count; ++i) {
        printw("%d. [%c] - %s\n", i+1, todoList->items[i].completed ? 'x' : ' ', todoList->items[i].task);
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
    char newTask[MAXLENGTH];

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
                int taskIndicies[MAXLENGTH];
                char *token = strtok(input, " ");
                while (token != NULL && n < MAXLENGTH) {
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
                int taskIndicies[MAXLENGTH];
                char *token = strtok(input, " ");
                while (token != NULL && n < MAXLENGTH) {
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
