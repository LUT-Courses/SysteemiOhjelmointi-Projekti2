// my-cat.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0; /* no files */
    }

    char buffer[4096];

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("my-cat: cannot open file\n");
            return 1;
        }

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            fputs(buffer, stdout);
        }

        fclose(fp);
    }

    return 0;
}
