#ifndef SCANNER_H
#define SCANNER_H

#include "file_entry.h"

int scan_directory(const char *path, FileEntry *files, int maxFiles);

#endif