#include "story.h"

struct Story* addStory(struct Story *head) {
    struct Story *newStory = (struct Story*)malloc(sizeof(struct Story));
    printf("Enter story title: ");
    fgets(newStory->name, sizeof(newStory->name), stdin);
    newStory->name[strcspn(newStory->name, "\n")] = '\0';
    newStory->chapters = NULL;
    newStory->next = NULL;

    int more = 1;
    struct Chapter *last = NULL;
    while (more) {
        struct Chapter *newCh = (struct Chapter*)malloc(sizeof(struct Chapter));
        printf("Enter chapter title: ");
        fgets(newCh->title, sizeof(newCh->title), stdin);
        newCh->title[strcspn(newCh->title, "\n")] = '\0';
        printf("Enter content: ");
        fgets(newCh->content, sizeof(newCh->content), stdin);
        newCh->content[strcspn(newCh->content, "\n")] = '\0';
        newCh->next = NULL;

        if (newStory->chapters == NULL)
            newStory->chapters = newCh;
        else
            last->next = newCh;
        last = newCh;

        printf("Add another chapter? (1-Yes / 0-No): ");
        scanf("%d", &more);
        getchar();
    }

    if (head == NULL) return newStory;

    struct Story *temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = newStory;

    return head;
}

void viewStories(struct Story *head) {
    int i = 1;
    while (head) {
        printf("\nStory %d: %s\n", i++, head->name);
        struct Chapter *ch = head->chapters;
        int j = 1;
        while (ch) {
            printf("  Chapter %d: %s\n", j++, ch->title);
            ch = ch->next;
        }
        head = head->next;
    }
}

void readStory(struct Story *head) {
    char name[50];
    printf("Enter story name to read: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    while (head && strcmp(head->name, name) != 0)
        head = head->next;

    if (!head) {
        printf("Story not found.\n");
        return;
    }

    struct Chapter *ch = head->chapters;
    int chapterNum = 1;
    while (ch) {
        printf("\nChapter %d: %s\n%s\n", chapterNum, ch->title, ch->content);
        printf("\n(Press Enter for next chapter or 'q' to quit): ");
        char c = getchar();
        if (c == 'q') break;
        ch = ch->next;
        chapterNum++;
    }
}

struct Story* deleteStory(struct Story *head, char storyName[]) {
    struct Story *temp = head, *prev = NULL;
    while (temp && strcmp(temp->name, storyName) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return head;

    if (prev == NULL) head = temp->next;
    else prev->next = temp->next;

    struct Chapter *ch = temp->chapters;
    while (ch) {
        struct Chapter *next = ch->next;
        free(ch);
        ch = next;
    }
    free(temp);
    return head;
}

void saveStoriesToFile(struct Story *head, FILE *fp) {
    while (head) {
        fprintf(fp, "Story:%s\n", head->name);
        struct Chapter *ch = head->chapters;
        while (ch) {
            fprintf(fp, "Chapter:%s|%s\n", ch->title, ch->content);
            ch = ch->next;
        }
        fprintf(fp, "END\n");
        head = head->next;
    }
}

struct Story* loadStoriesFromFile(struct Story *head) {
    FILE *fp = fopen("mystories.txt", "r");
    if (!fp) return NULL;

    char line[600];
    struct Story *currStory = NULL;
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Story:", 6) == 0) {
            struct Story *newS = (struct Story*)malloc(sizeof(struct Story));
            strcpy(newS->name, line + 6);
            newS->name[strcspn(newS->name, "\n")] = '\0';
            newS->chapters = NULL;
            newS->next = NULL;
            if (head == NULL)
                head = newS;
            else {
                struct Story *t = head;
                while (t->next) t = t->next;
                t->next = newS;
            }
            currStory = newS;
        } else if (strncmp(line, "Chapter:", 8) == 0 && currStory) {
            struct Chapter *newC = (struct Chapter*)malloc(sizeof(struct Chapter));
            sscanf(line + 8, "%49[^|]|%499[^\n]", newC->title, newC->content);
            newC->next = NULL;
            if (currStory->chapters == NULL)
                currStory->chapters = newC;
            else {
                struct Chapter *t = currStory->chapters;
                while (t->next) t = t->next;
                t->next = newC;
            }
        }
    }
    fclose(fp);
    return head;
}

void freeStories(struct Story *head) {
    while (head) {
        struct Chapter *ch = head->chapters;
        while (ch) {
            struct Chapter *next = ch->next;
            free(ch);
            ch = next;
        }
        struct Story *nextS = head->next;
        free(head);
        head = nextS;
    }
}
