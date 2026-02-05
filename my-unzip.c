// my-unzip.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void write_repeated(unsigned char ch, uint32_t count)
{
    unsigned char buf[4096];
    for (size_t i = 0; i < sizeof(buf); i++)
    {
        buf[i] = ch;
    }

    while (count > 0)
    {
        size_t n = count < (uint32_t)sizeof(buf) ? (size_t)count : sizeof(buf);
        if (fwrite(buf, 1, n, stdout) != n)
        {
            exit(1);
        }
        count -= (uint32_t)n;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "rb");
        if (fp == NULL)
        {
            return 1;
        }

        while (1)
        {
            uint32_t count = 0;
            unsigned char ch = 0;

            // Read 4-byte count
            size_t r1 = fread(&count, sizeof(count), 1, fp);
            if (r1 != 1)
            {
                // Clean EOF: stop
                if (feof(fp))
                {
                    break;
                }
                fclose(fp);
                return 1;
            }


            size_t r2 = fread(&ch, sizeof(ch), 1, fp);
            if (r2 != 1)
            {
                fclose(fp);
                return 1;
            }

            if (count == 0)
            {
                continue;
            }

            write_repeated(ch, count);
        }

        fclose(fp);
    }

    return 0;
}
