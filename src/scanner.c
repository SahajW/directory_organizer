#include <stdio.h>
#include "dirent.h"
#include <string.h>
#include <sys/stat.h>
#include "scanner.h"
#include "file_entry.h"

void get_extension(const char *filename, char *ext, int extSize)
{
    const char *dot = strrchr(filename, '.');
    if (dot && dot != filename)
        strncpy(ext, dot, extSize - 1);
    else
        strncpy(ext, "none", extSize - 1);
    ext[extSize - 1] = '\0';
}

int scan_directory(const char *path, FileEntry *files, int maxFiles)
{
    struct dirent *entry;
    DIR *dir = opendir(path);
    int count = 0;

    if (dir == NULL)
    {
        printf("Cannot open directory: %s\n", path);
        return count;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        // ignore current and parent directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullPath[1024];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

        struct stat fileStat;
        stat(fullPath, &fileStat);

        if (S_ISDIR(fileStat.st_mode)) // if its a directory recursive function call used
        {
            scan_directory(fullPath, files, maxFiles); // the function
        }
        else
        {
            if (count >= maxFiles)
            {
                printf("Max file limit reached!\n");
                closedir(dir);
                return count;
            }

            strncpy(files[count].path, fullPath, MAX_PATH_LEN - 1);
            get_extension(entry->d_name, files[count].extension, 32);
            files[count].size = fileStat.st_size;

            printf("Found file: %s (ext: %s, size: %ld bytes)\n",
                   fullPath, files[count].extension, files[count].size);

            count++;
        }
    }

    closedir(dir);
    return count;
}