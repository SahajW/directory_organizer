#ifndef SUMMARY_H
#define SUMMARY_H

typedef struct {
    int total_scanned;
    int total_organized;
    int total_duplicates;
    int total_failed;
    int images;
    int videos;
    int audio;
    int docs;
    int code;
    int others;
} Summary;

void summary_init(Summary *s);
void summary_print(Summary *s);

#endif