#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

void cpy_arr(int width, int height, char *src[width], char dst[height][width])
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            dst[i][j] = src[i][j];
}

int min(int a, int b, int c)
{
    if (a <= b && a <= c)
        return a;
    else if (b <= a && b <= c)
        return b;
    else c;
}

int get_cell_value(int width, int height, char *map[width], int x, int y)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
        return 0;
    else
        return map[y][x];
}

void find_biggest_square(int width, int height, char *map[width])
{
    printf("test\n");
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            map[i][j] = 1 + min(get_cell_value(width, height, map, j - 1, i - 1), get_cell_value(width, height, map, j - 1, i), get_cell_value(width, height, map, j, i - 1));
        }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            putchar(map[i][j] + '0');
        putchar('\n');
    }
}

void process_map(FILE *file)
{
    int height;
    char empty_char;
    char obstacle_char;
    char full_char;

    fscanf(file, "%d %c %c %c\n", &height, &empty_char, &obstacle_char, &full_char);
    printf("height %d, empty: %c, obstacle: %c, full: %c\n", height, empty_char, obstacle_char, full_char);
    char *map[height];
    int width = -1;

    for (int i = 0;;i++)
    {
        char *line = NULL;
        size_t n = 0;
        errno = 0;
        ssize_t size = getline(&line, &size, file);
        if(size == -1)
        {
            if (errno)
                return ; //free array if you want, likely not necessary
            else
                break;
        }
        if (i == 0)
            width = size - 1;
        else if (width != size - 1 || line[size - 1] != '\n')
        {
            fprintf(stderr, "map error\n");
            //free array if you want, likely not necessary
            return;
        }
        for (int j = 0; j < width; j++)
            if (line[j] != empty_char && line[j] != obstacle_char)
            {
                fprintf(stderr, "map error\n");
                //free array if you want, likely not necessary
                return;
            }
        printf("line is: %s", line);
        map[i] = line;
    }
    char temp_map[height - 1][width - 1];
    cpy_arr(width - 1, height - 1, map, temp_map);
    find_biggest_square(width, height, map);
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        FILE *file = fopen(argv[i], "r");
        if (!file)
            return 1;
        process_map(file);
        fclose(file);
        if (i != 1)
            fputs("\n", stdin);
    }
    return 0;
}