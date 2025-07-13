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
