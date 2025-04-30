#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100

// File structure
typedef struct File {
    char name[MAX_NAME_LEN];
    int size;              // size in KB
    int startBlock;        // FAT-like index (just simulated here)
    struct File* next;
} File;

File* head = NULL;
int nextStartBlock = 0;

// Create a new file
void createFile(const char* name, int size) {
    File* current = head;

    // Check if file already exists
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("File '%s' already exists.\n", name);
            return;
        }
        current = current->next;
    }

    // Create and initialize new file
    File* newFile = (File*)malloc(sizeof(File));
    strcpy(newFile->name, name);
    newFile->size = size;
    newFile->startBlock = nextStartBlock;
    newFile->next = head;
    head = newFile;

    nextStartBlock += size;

    printf("File '%s' created successfully.\n", name);
}

// Delete a file
void deleteFile(const char* name) {
    File* current = head;
    File* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("File '%s' deleted successfully.\n", name);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("File '%s' not found.\n", name);
}

// Rename a file
void renameFile(const char* oldName, const char* newName) {
    File* current = head;

    while (current != NULL) {
        if (strcmp(current->name, oldName) == 0) {
            strcpy(current->name, newName);
            printf("File '%s' renamed to '%s'.\n", oldName, newName);
            return;
        }
        current = current->next;
    }

    printf("File '%s' not found.\n", oldName);
}

// Search for a file
void searchFile(const char* name) {
    File* current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("File found: %s, Size: %d KB, Start Block: %d\n",
                   current->name, current->size, current->startBlock);
            return;
        }
        current = current->next;
    }

    printf("File '%s' not found.\n", name);
}

// Display all files
void displayFiles() {
    File* current = head;

    if (current == NULL) {
        printf("No files in the system.\n");
        return;
    }

    printf("\n--- File List ---\n");
    while (current != NULL) {
        printf("Name: %s, Size: %d KB, Start Block: %d\n",
               current->name, current->size, current->startBlock);
        current = current->next;
    }
    printf("------------------\n");
}

// Main menu
int main() {
    int choice;
    char name[MAX_NAME_LEN], newName[MAX_NAME_LEN];
    int size;

    while (1) {
        printf("\n--- Simple File Management System ---\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Rename File\n");
        printf("4. Search File\n");
        printf("5. Display Files\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Clear newline from buffer

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                fgets(name, MAX_NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';  // Remove newline

                printf("Enter file size (KB): ");
                scanf("%d", &size);
                getchar();

                createFile(name, size);
                break;

            case 2:
                printf("Enter file name to delete: ");
                fgets(name, MAX_NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';

                deleteFile(name);
                break;

            case 3:
                printf("Enter current file name: ");
                fgets(name, MAX_NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';

                printf("Enter new file name: ");
                fgets(newName, MAX_NAME_LEN, stdin);
                newName[strcspn(newName, "\n")] = '\0';

                renameFile(name, newName);
                break;

            case 4:
                printf("Enter file name to search: ");
                fgets(name, MAX_NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';

                searchFile(name);
                break;

            case 5:
                displayFiles();
                break;

            case 6:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}