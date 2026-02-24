#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "file_entry.h"
#include "summary.h"

void organize_files(FileEntry *files, int total, int *isDuplicate, Summary *s);

#endif