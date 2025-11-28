#ifndef NOTES_H
#define NOTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Note {
    char text[200];
    struct Note *next;
};

struct Note* addNote(struct Note *head);
void viewNotes(struct Note *head);
struct Note* deleteLastNote(struct Note *head);
void saveNotesToFile(struct Note *head, FILE *fp);
struct Note* loadNotesFromFile(struct Note *head);
void freeNotes(struct Note *head);

#endif
