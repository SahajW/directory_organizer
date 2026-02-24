#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_entry.h"
#include "scanner.h"
#include "hash_table.h"
#include "organizer.h"
#include "summary.h"

static void print_header()
{
    printf("\n========================================\n");
    printf("       DIRECTORY ORGANIZER v1.0\n");
    printf("========================================\n\n");
}

static void do_organize(char *path)
{
    FileEntry files[MAX_FILE];
    int i;

    printf("\nscanning %s ...\n\n", path);
    int total = scan_directory(path, files, MAX_FILE);

    if (total == 0)
    {
        printf("no files found in: %s\n", path);
        return;
    }

    printf("\n%d file(s) found. checking for duplicates...\n", total);

    HashTable ht;
    ht_init(&ht);

    int isDuplicate[MAX_FILE] = {0};
    int dupes = 0;
    for (i = 0; i < total; i++)
    {
        if (ht_insert(&ht, files[i].path))
        {
            isDuplicate[i] = 1;
            dupes++;
        }
    }

    printf("%d duplicate(s) found.\n", dupes);

    printf("\nready to organize '%s'. proceed? (y/n): ", path);
    char confirm;
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y')
    {
        printf("cancelled.\n");
        ht_free(&ht);
        return;
    }

    Summary s;
    summary_init(&s);
    s.total_scanned = total;

    organize_files(files, total, isDuplicate, &s);
    summary_print(&s);

    ht_free(&ht);
}

static void do_scan(char *path)
{
    FileEntry files[MAX_FILE];

    printf("\nscanning %s ...\n\n", path);
    int total = scan_directory(path, files, MAX_FILE);

    if (total == 0)
    {
        printf("no files found in: %s\n", path);
        return;
    }

    printf("\n----------------------------------------\n");
    printf("  total files found : %d\n", total);
    printf("----------------------------------------\n");
}

int main()
{
    char path[1024];
    int choice;
    int running = 1;

    print_header();

    while (running)
    {
        printf("  [1] organize a folder\n");
        printf("  [2] scan only\n");
        printf("  [3] exit\n\n");
        printf("choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("enter folder path: ");
                scanf("%s", path);
                do_organize(path);
                break;

            case 2:
                printf("enter folder path: ");
                scanf("%s", path);
                do_scan(path);
                break;

            case 3:
                printf("\ngoodbye!\n\n");
                running = 0;
                break;

            default:
                printf("\ninvalid choice. try again.\n\n");
                break;
        }

        if (running)
            printf("\n----------------------------------------\n\n");
    }

    return 0;
}