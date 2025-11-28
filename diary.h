#ifndef DIARY_H
#define DIARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Diary {
    char date[20];
    char entry[200];
    struct Diary *left, *right;
};

struct Diary* addDiaryEntry(struct Diary *root);
void viewDiary(struct Diary *root);
struct Diary* searchDiary(struct Diary *root, char date[]);
struct Diary* deleteDiaryEntry(struct Diary* root, char date[]);
struct Diary* minValueNode(struct Diary* node);
void saveDiaryToFile(struct Diary *root, FILE *fp);
struct Diary* loadDiaryFromFile(struct Diary *root);
void freeDiary(struct Diary *root);

#endif
