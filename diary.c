#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diary.h"

struct Diary* addDiaryEntry(struct Diary *root) {
    char date[20], entry[200];
    getchar();  

    printf("Enter date (DD/MM/YYYY): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0'; 
    
    struct Diary *existing = searchDiary(root, date);

    printf("Write your thoughts: ");
    fgets(entry, sizeof(entry), stdin);
    entry[strcspn(entry, "\n")] = '\0'; 

    if (existing) {
        strcat(existing->entry, "\n");
        strcat(existing->entry, entry);
        printf("Entry updated for %s.\n", date);
    } else {
        struct Diary *newNode = malloc(sizeof(struct Diary));
        strcpy(newNode->date, date);
        strcpy(newNode->entry, entry);
        newNode->left = newNode->right = NULL;

        if (!root) {
            root = newNode;
        } else {
            struct Diary *cur = root, *prev = NULL;
            while (cur) {
                prev = cur;
                if (strcmp(date, cur->date) < 0)
                    cur = cur->left;
                else
                    cur = cur->right;
            }

            if (strcmp(date, prev->date) < 0)
                prev->left = newNode;
            else
                prev->right = newNode;
        }
        printf("New entry added for %s.\n", date);
    }

    return root; 
}

void viewDiary(struct Diary *root) {
    if (!root) return;
    viewDiary(root->left);
    printf("\nDate: %s\nEntry: %s\n", root->date, root->entry);
    viewDiary(root->right);
}

struct Diary* searchDiary(struct Diary *root, char date[]) {
    if (!root) return NULL;
    if (strcmp(date, root->date) == 0) return root;
    if (strcmp(date, root->date) < 0)
        return searchDiary(root->left, date);
    else
        return searchDiary(root->right, date);
}

struct Diary* minValueNode(struct Diary* node) {
    struct Diary* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct Diary* deleteDiaryEntry(struct Diary* root, char date[]) {
    if (!root) return NULL;

    if (strcmp(date, root->date) < 0)
        root->left = deleteDiaryEntry(root->left, date);
    else if (strcmp(date, root->date) > 0)
        root->right = deleteDiaryEntry(root->right, date);
    else {
        
        if (!root->left) {
            struct Diary* temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            struct Diary* temp = root->left;
            free(root);
            return temp;
        }

        struct Diary* temp = minValueNode(root->right);
        strcpy(root->date, temp->date);
        strcpy(root->entry, temp->entry);
        root->right = deleteDiaryEntry(root->right, temp->date);
    }

    return root;
}

void saveDiaryToFile(struct Diary *root, FILE *fp) {
    if (!root) return;
    fprintf(fp, "%s|%s\n", root->date, root->entry);
    saveDiaryToFile(root->left, fp);
    saveDiaryToFile(root->right, fp);
}

struct Diary* loadDiaryFromFile(struct Diary *root) {
    FILE *fp = fopen("diary.txt", "r");
    if (!fp) return NULL;

    char line[250];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        char *sep = strchr(line, '|');
        if (sep) {
            struct Diary *node = malloc(sizeof(struct Diary));
            strncpy(node->date, line, sep - line);
            node->date[sep - line] = '\0';
            strcpy(node->entry, sep + 1);
            node->left = node->right = NULL;

            if (!root)
                root = node;
            else {
                struct Diary *cur = root, *prev = NULL;
                while (cur) {
                    prev = cur;
                    if (strcmp(node->date, cur->date) < 0)
                        cur = cur->left;
                    else
                        cur = cur->right;
                }
                if (strcmp(node->date, prev->date) < 0)
                    prev->left = node;
                else
                    prev->right = node;
            }
        }
    }
    fclose(fp);
    return root;
}

void freeDiary(struct Diary *root) {
    if (!root) return;
    freeDiary(root->left);
    freeDiary(root->right);
    free(root);
}
