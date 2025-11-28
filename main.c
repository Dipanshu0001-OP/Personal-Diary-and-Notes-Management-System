#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diary.h"
#include "notes.h"

int main() {
    struct Diary *diaryRoot = NULL;
    struct Note *noteRoot = NULL;
    int choice, sub;
    char date[20];

    diaryRoot = loadDiaryFromFile(diaryRoot);
    noteRoot = loadNotesFromFile(noteRoot);

    do {
        printf("\n==== MAIN MENU ====\n");
        printf("1. Diary Mode\n2. Notes Mode\n3. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            do {
                printf("\n--- Diary Mode ---\n");
                printf("1. Add Entry / Append\n2. View All\n3. Search by Date\n4. Delete by Date\n5. Back\nChoice: ");
                scanf("%d", &sub);
                getchar();

                if (sub == 1)
                    diaryRoot = addDiaryEntry(diaryRoot);  
                else if (sub == 2)
                    viewDiary(diaryRoot);
                else if (sub == 3) {
                    printf("Enter date: ");
                    fgets(date, 20, stdin);
                    date[strcspn(date, "\n")] = '\0';
                    struct Diary *found = searchDiary(diaryRoot, date);
                    if (found)
                        printf("Entry on %s:\n%s\n", found->date, found->entry);
                    else
                        printf("Not found.\n");
                }
                else if (sub == 4) {
                    printf("Enter date to delete: ");
                    fgets(date, 20, stdin);
                    date[strcspn(date, "\n")] = '\0';
                    diaryRoot = deleteDiaryEntry(diaryRoot, date);
                    printf("Deleted entry if it existed.\n");
                }

            } while (sub != 5);

            FILE *fp = fopen("diary.txt", "w");
            if (fp) {
                saveDiaryToFile(diaryRoot, fp);
                fclose(fp);
            }
        }

        else if (choice == 2) {
            do {
                printf("\n--- Notes Mode ---\n");
                printf("1. Add Note\n2. View All\n3. Delete Last Note\n4. Back\nChoice: ");
                scanf("%d", &sub);
                getchar();

                if (sub == 1)
                    noteRoot = addNote(noteRoot);
                else if (sub == 2)
                    viewNotes(noteRoot);
                else if (sub == 3) {
                    noteRoot = deleteLastNote(noteRoot);
                    printf("Last note deleted if it existed.\n");
                }

            } while (sub != 4);

            FILE *fp = fopen("notes.txt", "w");
            if (fp) {
                saveNotesToFile(noteRoot, fp);
                fclose(fp);
            }
        }

    } while (choice != 3);

    freeDiary(diaryRoot);
    freeNotes(noteRoot);
    printf("Data saved. Exiting program.\n");
    return 0;
}
