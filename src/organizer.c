#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "organizer.h"

static const char *get_category(const char *ext)
{
    if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".png") == 0 ||
        strcmp(ext, ".gif") == 0 || strcmp(ext, ".jpeg") == 0)
        return "Images";

    if (strcmp(ext, ".mp4") == 0 || strcmp(ext, ".mkv") == 0 ||
        strcmp(ext, ".avi") == 0 || strcmp(ext, ".mov") == 0)
        return "Videos";

    if (strcmp(ext, ".mp3") == 0 || strcmp(ext, ".wav") == 0 ||
        strcmp(ext, ".flac") == 0)
        return "Audio";

    if (strcmp(ext, ".pdf") == 0 || strcmp(ext, ".docx") == 0 ||
        strcmp(ext, ".txt") == 0 || strcmp(ext, ".xlsx") == 0)
        return "Docs";

    if (strcmp(ext, ".c") == 0 || strcmp(ext, ".h") == 0 ||
        strcmp(ext, ".py") == 0 || strcmp(ext, ".js") == 0)
        return "Code";

    return "Others";
}

static void make_folder(const char *path)
{
    struct stat st;
    if (stat(path, &st) == -1)
        mkdir(path);
}

void organize_files(FileEntry *files, int total, int *isDuplicate)
{
    int i;
    for (i = 0; i < total; i++)
    {
        if (isDuplicate[i])
        {
            make_folder("organized/Duplicates");
            char dest[1024];
            char *filename = strrchr(files[i].path, '/');
            if (!filename) filename = files[i].path;
            else filename++;

            snprintf(dest, sizeof(dest), "organized/Duplicates/%s", filename);
            if (rename(files[i].path, dest) == 0)
                printf("moved duplicate -> organized/Duplicates/%s\n", filename);
            else
                printf("failed to move: %s\n", files[i].path);
            continue;
        }

        const char *category = get_category(files[i].extension);

        char folder[256];
        snprintf(folder, sizeof(folder), "organized/%s", category);
        make_folder("organized");
        make_folder(folder);

        char *filename = strrchr(files[i].path, '/');
        if (!filename) filename = files[i].path;
        else filename++;

        char dest[1024];
        snprintf(dest, sizeof(dest), "%s/%s", folder, filename);

        if (rename(files[i].path, dest) == 0)
            printf("moved %s -> %s\n", filename, folder);
        else
            printf("failed to move: %s\n", files[i].path);
    }
}