#ifndef STORY_H
#define STORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Chapter {
    char title[50];
    char content[500];
    struct Chapter *next;
};

struct Story {
    char name[50];
    struct Chapter *chapters;
    struct Story *next;
};

struct Story* addStory(struct Story *head);
void viewStories(struct Story *head);
void readStory(struct Story *head);
struct Story* deleteStory(struct Story *head, char storyName[]);
void saveStoriesToFile(struct Story *head, FILE *fp);
struct Story* loadStoriesFromFile(struct Story *head);
void freeStories(struct Story *head);

#endif
