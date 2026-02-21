#include <stdio.h>
#include "dirent.h"
#include <string.h>
#include <sys/stat.h>
#include "scanner.h"
void scan_directory(const char *path)
{
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL)
    {
        printf("Cannot open directory: %s\n", path);
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        // Ignore current and parent directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullPath[1024];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

        struct stat fileStat;
        stat(fullPath, &fileStat);

        if (S_ISDIR(fileStat.st_mode))
        {
            // It's a directory → scan again
            scan_directory(fullPath);
        }
        else
        {
            // It's a file
            printf("Found file: %s\n", fullPath);
        }
    }

    closedir(dir);
}