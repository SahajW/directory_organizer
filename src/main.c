#include "scanner.h"
#include "file_entry.h"
#include <stdio.h>
int main()
{
    FileEntry files[MAX_FILE];
    int totalfiles = scan_directory("test_folder", files, MAX_FILE);
    printf("Total numer of files scanned is %d", totalfiles);

    return 0;
}