// my-zip.c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static void flush_run(int count, unsigned char ch) {
    // Write 4-byte integer in binary, then the character byte
    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&ch, sizeof(unsigned char), 1, stdout);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        return 1;
    }

    int have_run = 0;
    unsigned char current = 0;
    int count = 0;

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (fp == NULL) {
            return 1;
        }

        int c;
        while ((c = fgetc(fp)) != EOF) {
            unsigned char ch = (unsigned char)c;

            if (!have_run) {
                have_run = 1;
                current = ch;
                count = 1;
            } else if (ch == current && count < INT_MAX) {
                count++;
            } else {
                flush_run(count, current);
                current = ch;
                count = 1;
            }
        }

        fclose(fp);
    }

    if (have_run) {
        flush_run(count, current);
    }

    return 0;
}
