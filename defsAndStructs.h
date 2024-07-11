#define DESCRIPTIONLENGTH 50
#define PROJECTLENGTH 15
#define CONTEXTLENGTH 15
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
    date completionDate;
    date creationDate;
    char priority;
    char description[DESCRIPTIONLENGTH];
    char context[CONTEXTLENGTH];
    char project[PROJECTLENGTH];
    date dueDate;
} todoItem;

typedef struct {
    todoItem items[MAXITEMS];
    int count;
} todoList;
