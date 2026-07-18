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
    int d = a;
    if (b < a)
        d = b;
    int result = c;
    if (d < c)
        result = d;
    return result;
}

int get_cell_value(int width, int height, char map[height][width], int x, int y)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
        return 0;
    else
        return map[y][x];
}

void find_biggest_square(int width, int height, char map[height][width], int obstacle_char)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] == obstacle_char)
                map[i][j] = 0;
            else
            {
                int a = get_cell_value(width, height, map, j - 1, i - 1);
                int b = get_cell_value(width, height, map, j - 1, i);
                int c = get_cell_value(width, height, map, j, i - 1);
                map[i][j] = 1 + min(a, b, c);
            }
        }
    }
    // for (int i = 0; i < height; i++)
    // {
    //     for (int j = 0; j < width; j++)
    //         putchar(map[i][j] + '0');
    //     putchar('\n');
    // }
}

void process_map(FILE *file)
{
    int height;
    char empty_char;
    char obstacle_char;
    char full_char;

    if (fscanf(file, "%d %c %c %c\n", &height, &empty_char, &obstacle_char, &full_char) != 4)
    {
        fprintf(stderr, "map error\n");
        return;
    }
    char *map[height];
    int width = -1;

    for (int i = 0;;i++)
    {
        char *line = NULL;
        size_t n = 0;
        errno = 0;
        ssize_t size = getline(&line, &n, file);
        if(size == -1)
        {
            if (errno)
                return ; //free array if you want, likely not necessary
            else
                break;
        }
        if (i == 0)
            width = size - 1;
        else if (width != size - 1 || size <= 0 || line[size - 1] != '\n' || i >= height)
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
        map[i] = line;
    }
    char temp_map[height][width];
    cpy_arr(width, height, map, temp_map);
    find_biggest_square(width, height, temp_map, obstacle_char);
    int x = 0;
    int y = 0;
    int biggest = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (temp_map[i][j] > biggest)
            {
                y = i;
                x = j;
                biggest = temp_map[i][j];
            }
        }
    }
    for (int i = y; y - i < biggest; i--)
    {
        for (int j = x; x - j < biggest; j--)
        {
            map[i][j] = full_char;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            putchar(map[i][j]);
        putchar('\n');
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
        process_map(stdin);
    for (int i = 1; i < argc; i++)
    {
        if (i != 1)
            fputs("\n", stdin);
        FILE *file = fopen(argv[i], "r");
        if (!file)
        {
            fprintf(stderr, "map error\n");
            continue ;
        }
        process_map(file);
        fclose(file);
    }
    return 0;
}
