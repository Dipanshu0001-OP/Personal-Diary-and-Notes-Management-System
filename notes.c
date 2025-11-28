#include "notes.h"

struct Note* addNote(struct Note *head) {
    struct Note *newNode = (struct Note*)malloc(sizeof(struct Note));
    printf("Enter your note: ");
    fgets(newNode->text, sizeof(newNode->text), stdin);
    newNode->text[strcspn(newNode->text, "\n")] = '\0';
    newNode->next = NULL;

    if (head == NULL)
        return newNode;

    struct Note *temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;

    return head;
}

void viewNotes(struct Note *head) {
    int count = 1;
    while (head) {
        printf("Note %d: %s\n", count++, head->text);
        head = head->next;
    }
}

struct Note* deleteLastNote(struct Note *head) {
    if (head == NULL) return NULL;
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    struct Note *temp = head;
    while (temp->next->next)
        temp = temp->next;
    free(temp->next);
    temp->next = NULL;
    return head;
}

void saveNotesToFile(struct Note *head, FILE *fp) {
    while (head) {
        fprintf(fp, "%s\n", head->text);
        head = head->next;
    }
}

struct Note* loadNotesFromFile(struct Note *head) {
    FILE *fp = fopen("notes.txt", "r");
    if (!fp) return NULL;

    char line[200];
    while (fgets(line, sizeof(line), fp)) {
        struct Note *newNode = (struct Note*)malloc(sizeof(struct Note));
        line[strcspn(line, "\n")] = '\0';
        strcpy(newNode->text, line);
        newNode->next = NULL;

        if (head == NULL)
            head = newNode;
        else {
            struct Note *temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
        }
    }
    fclose(fp);
    return head;
}

void freeNotes(struct Note *head) {
    while (head) {
        struct Note *temp = head;
        head = head->next;
        free(temp);
    }
}
