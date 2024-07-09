#define DESCRIPTIONLENGTH 50
#define PROJECTLENGTH 15
#define CONTEXTLENGTH 15
#define MAXPROJECTS 25
#define MAXCONTEXTS 25
#define MAXITEMS 100

typedef char context[CONTEXTLENGTH];

typedef char project[PROJECTLENGTH];

typedef struct {
    int year;
    int month;
    int day;
} date;

typedef struct {
    char completion;
    char priority;
    char description[DESCRIPTIONLENGTH];
    date creationDate;
    date completionDate;
    date dueDate;
    context contexts[MAXCONTEXTS];
    project projects[MAXPROJECTS];
} todoItem;

typedef struct {
    todoItem items[MAXITEMS];
    int count;
} todoList;
