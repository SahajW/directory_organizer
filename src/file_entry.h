#ifndef FILE_ENTRY_H
#define FILE_ENTRY_H

#define MAX_PATH_LEN 1024
#define MAX_FILE 1024

typedef struct{
    char path[1024];
    char extension[32];
    long size;

}FileEntry;

#endif