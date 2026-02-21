#ifndef FILE_ENTRY_H
#define FILE_ENTRY_H

typedef struct{
    char path[1024];
    char extension[32];
    long size;

}FileEntry;

#endif