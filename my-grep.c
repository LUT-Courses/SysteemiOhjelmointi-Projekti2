// my-grep.c
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void grep_stream(FILE *fp, const char *term) {
    char *line = NULL;
    size_t cap = 0;

    int match_all = (term[0] == '\0');

    while (getline(&line, &cap, fp) != -1) {
        if (match_all || strstr(line, term) != NULL) {
            fputs(line, stdout);
        }
    }

    free(line);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-grep: searchterm [file ...]\n");
        return 1;
    }

    const char *term = argv[1];

    if (argc == 2) {
        // read from stdin
        grep_stream(stdin, term);
        return 0;
    }

    for (int i = 2; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("my-grep: cannot open file\n");
            return 1;
        }

        grep_stream(fp, term);
        fclose(fp);
    }

    return 0;
}
