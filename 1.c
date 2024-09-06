#include<stdio.h>
#include<stdlib.h>
#include<string.h>  // Include the necessary header for strcpy

typedef struct node {
    char info[100];  // Changed from char to char array for strings
    int priHour;
    int priSec;
    int priMin;
    struct node *next;
} NODE;

typedef struct queue {
    NODE *head;
} QUEUE;

void initList(QUEUE *pq);
void AddEvent(QUEUE *pq, const char *event, int min, int sec, int hour);
void DeleteEvent(QUEUE *pq, char *event, int *min, int *sec, int *hour);
void ListEvents(QUEUE *pq);
void EditEvent(QUEUE *pq, const char *oldEvent, const char *newEvent, int newMin, int newSec, int newHour);

void initList(QUEUE *pq) {
    pq->head = NULL;
}

void AddEvent(QUEUE *pq, const char *event, int min, int sec, int hour) {
    NODE *newNode = malloc(sizeof(NODE));
    strcpy(newNode->info, event);  // strcpy now works since info is a char array
    newNode->priHour = hour;
    newNode->priMin = min;
    newNode->priSec = sec;
    newNode->next = NULL;

    NODE *p = pq->head;
    NODE *q = NULL;

    while (p != NULL && p->priHour < newNode->priHour && p->priMin < newNode->priMin && p->priSec < newNode->priSec) {
        q = p;
        p = p->next;
    }

    if (q == NULL) {
        newNode->next = pq->head;
        pq->head = newNode;
    } else {
        newNode->next = p;
        q->next = newNode;
    }
}

void DeleteEvent(QUEUE *pq, char *event, int *min, int *sec, int *hour) {
    NODE *p = pq->head;
    strcpy(event, p->info);  // Copy event name as string
    *hour = p->priHour;
    *min = p->priMin;
    *sec = p->priSec;
    pq->head = pq->head->next;

    free(p);
}

void ListEvents(QUEUE *pq) {
    NODE *current = pq->head;

    if (current == NULL) {
        printf("Event list is empty.\n");
        return;
    }

    printf("List of Events:\n");
    while (current != NULL) {
        printf("Event: %s\n", current->info);  // Print event as string
        printf("Time: %02d:%02d:%02d\n", current->priHour, current->priMin, current->priSec);
        current = current->next;
    }
}

void EditEvent(QUEUE *pq, const char *oldEvent, const char *newEvent, int newMin, int newSec, int newHour) {
    NODE *current = pq->head;

    while (current != NULL) {
        if (strcmp(current->info, oldEvent) == 0) {  // Use strcmp for string comparison
            strcpy(current->info, newEvent);  // Use strcpy to copy the new event name
            current->priHour = newHour;
            current->priMin = newMin;
            current->priSec = newSec;
            break;
        }
        current = current->next;
    }
}

int main() {
    QUEUE eventQueue;
    initList(&eventQueue);

    AddEvent(&eventQueue, "Event A", 10, 15, 9);
    AddEvent(&eventQueue, "Event B", 30, 45, 11);
    AddEvent(&eventQueue, "Event C", 20, 0, 10);

    ListEvents(&eventQueue);

    EditEvent(&eventQueue, "Event B", "Event X", 35, 50, 11);

    ListEvents(&eventQueue);

    return 0;
}
