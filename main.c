#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define maxLength 50
#define maxItems 100

typedef struct {
    char task[maxLength];
    int completed;
} todoItem;

typedef struct {
    todoItem items[maxItems];
    int count;
} todoList;

void writeToFile(todoList *list, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    } else {
        for (int i = 0; i < list->count; ++i) {
            fprintf(fp, "%d, %s\n", list->items[i].completed, list->items[i].task);
        }
    }
    fclose(fp);
}

void readFromFile(todoList *list, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    } else {
        list->count = 0;
        while (fscanf(fp, "%d, %[^\n]\n", &list->items[list->count].completed, list->items[list->count].task) == 2) {
            list->count ++;
            if (list->count >= maxItems) {
                break;
            }
        }
    }
    fclose(fp);
}

void addTask(todoList *list, const char *task) {
    if (list->count >= maxLength) {
        printf("Max number of tasks reached.");
        return;
    } else {
        strcpy(list->items[list->count].task, task);
        list->items[list->count].completed = 0;
        list->count ++;
    }
}

void removeTask(todoList *list, const int index) {
    if (list->count == 0 ) {
        printf("Todo list is currently empty.");
        return;
    } else if (index < 0 || index > list->count) {
        printf("Invalid index.");
        return;
    } else {
        list->count --;
        for (int i = index; i < list->count; ++i) {
            strcpy(list->items[index].task, list->items[index+1].task);
            list->items[i].completed = list->items[i+1].completed;
        }
    }
}

void markComplete(todoList *list, const int index) {
    if (list->count == 0 ) {
        printf("Todo list is currently empty.");
        return;
    } else if (index < 0 || index > list->count) {
        printf("Invalid index.");
        return;
    } else {
        list->items[index].completed = 1;
    }
}

void markIncomplete(todoList *list, const int index) {
    if (list->count == 0 ) {
        printf("Todo list is currently empty.");
        return;
    } else if (index < 0 || index > list->count) {
        printf("Invalid index.");
        return;
    } else {
        list->items[index].completed = 0;
    }
}

void printList(todoList *list) {
    for (int i = 0; i < list->count; ++i) {
        printw("%d. [%c] - %s\n", i+1, list->items[i].completed ? 'x' : ' ', list->items[i].task);
    }
}

int main() {
    todoList todoList;
    todoList.count = 0;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    char fileName[] = "tasks.txt";
    readFromFile(&todoList, fileName);

    int choice;
    char newTask[maxLength];

    do {
        clear();
        printw("<--- Manage Your Tasks --->\n");
        printw(". . . . . . . . . . . . . .\n");
        for (int i = 0; i < todoList.count; ++i) {
            printw("%d. [%c] - %s\n", i+1, todoList.items[i].completed ? 'x' : ' ', todoList.items[i].task);
        }
        printw("\n\n");
        printw("1 -> Add new task.\n");
        printw("2 -> Remove task.\n");
        printw("3 -> Mark as complete.\n");
        printw("4 -> Mark as incomplete.\n");
        printw("5 -> Save and quit.\n");
        printw("\nEnter your choice: ");
        refresh();

        echo();
        scanw("%d", &choice);
        noecho();
        refresh();

        switch (choice) {
            case 1:
                clear();
                for (int i = 0; i < todoList.count; ++i) {
                    printw("%d. [%c] - %s\n", i+1, todoList.items[i].completed ? 'x' : ' ', todoList.items[i].task);
                }
                printw("Add new task: \n");
                echo();
                getstr(newTask);
                noecho();
                addTask(&todoList, newTask);
                break;
            case 2:
                clear();
                for (int i = 0; i < todoList.count; ++i) {
                    printw("%d. [%c] - %s\n", i+1, todoList.items[i].completed ? 'x' : ' ', todoList.items[i].task);
                }
                printw("Remove task (index): \n");
                echo();
                scanw("%d", &choice);
                noecho();
                removeTask(&todoList, choice - 1);
                refresh();
                break;
            case 3:
                clear();
                for (int i = 0; i < todoList.count; ++i) {
                    printw("%d. [%c] - %s\n", i+1, todoList.items[i].completed ? 'x' : ' ', todoList.items[i].task);
                }
                printw("\n");
                printw("Mark as complete: \n");
                echo();
                scanw("%d", &choice);
                noecho();
                markComplete(&todoList, choice - 1);
                refresh();
                break;
            case 4:
                clear();
                for (int i = 0; i < todoList.count; ++i) {
                    printw("%d. [%c] - %s\n", i+1, todoList.items[i].completed ? 'x' : ' ', todoList.items[i].task);
                }
                printw("\n");
                printw("Mark as complete: \n");
                echo();
                scanw("%d", &choice);
                noecho();
                markIncomplete(&todoList, choice - 1);
                refresh();
                break;
        };

    } while (choice != 5);

    writeToFile(&todoList, fileName);

    endwin();
    return 0;
}
