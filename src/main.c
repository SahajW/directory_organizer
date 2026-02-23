#include "scanner.h"
#include "hash_table.h"
#include "file_entry.h"
#include <stdio.h>
int main()
{
    FileEntry files[MAX_FILE];
    int totalfiles = scan_directory("test_folder", files, MAX_FILE);
    printf("Total numer of files scanned is %d\n", totalfiles);

    HashTable ht;
    ht_init(&ht);

    int dupes = 0;
    int i;
    for (i = 0; i < totalfiles; i++)
    {
        if (ht_insert(&ht, files[i].path))
            dupes++;
    }

    printf("duplicates: %d\n", dupes);

    ht_free(&ht);

    return 0;
}