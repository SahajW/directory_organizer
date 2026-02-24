#include <stdio.h>
#include "summary.h"

void summary_init(Summary *s)
{
    s->total_scanned = 0;
    s->total_organized = 0;
    s->total_duplicates = 0;
    s->total_failed = 0;
    s->images = 0;
    s->videos = 0;
    s->audio = 0;
    s->docs = 0;
    s->code = 0;
    s->others = 0;
}

void summary_print(Summary *s)
{
    printf("\n========================================\n");
    printf("              SUMMARY\n");
    printf("========================================\n");
    printf("  total scanned  : %d\n", s->total_scanned);
    printf("  organized      : %d\n", s->total_organized);
    printf("  duplicates     : %d\n", s->total_duplicates);
    printf("  failed         : %d\n", s->total_failed);
    printf("\n  categories:\n");
    printf("    Images  : %d\n", s->images);
    printf("    Videos  : %d\n", s->videos);
    printf("    Audio   : %d\n", s->audio);
    printf("    Docs    : %d\n", s->docs);
    printf("    Code    : %d\n", s->code);
    printf("    Others  : %d\n", s->others);
    printf("========================================\n");
}