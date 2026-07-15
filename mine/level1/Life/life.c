#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int edge_helper(int width, int height, char map[height][width], int x, int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return 0;
    return map[y][x] == 'O';
}

int count_neighbors(int width, int height, char map[height][width], int x, int y)
{
    int result = 0;
    // add up all living neighboring cells
    return edge_helper(width, height, map, x - 1, y - 1) + edge_helper(width, height, map, x, y - 1) + edge_helper(width, height, map, x + 1, y - 1)
        + edge_helper(width, height, map, x - 1, y) + edge_helper(width, height, map, x + 1, y)
        + edge_helper(width, height, map, x - 1, y + 1) + edge_helper(width, height, map, x, y + 1) + edge_helper(width, height, map, x + 1, y + 1);
}

void cpy_arr(int width, int height, char src[height][width], char dst[height][width])
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            dst[i][j] = src[i][j];
}

void exec_iteration(int width, int height, char map[height][width])
{
    char temp_map[height][width];

    cpy_arr(width, height, map, temp_map);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            int count = count_neighbors(width, height, map, j, i);
            if (count == 3)
                temp_map[i][j] = 'O';
            else if (count != 2)
                temp_map[i][j] = ' ';
        }
    cpy_arr(width, height, temp_map, map);
}

int main(int argc, char **argv)
{
    if (argc != 4)
        return 1;
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int iterations = atoi(argv[3]);
    char map[height][width];

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            map[i][j] = ' ';
    
    int x = 0;
    int y = 0;
    int pen_down = 0;
    char command;
    while (read(0, &command, 1) == 1)
    {
        if (command == 'x')
            pen_down = !pen_down;
        else if (command == 'w' && y > 0)
            y--;
        else if (command == 'a' && x > 0)
            x--;
        else if (command == 's' && y < height - 1)
            y++;
        else if (command == 'd' && x < width - 1)
            x++;
        else
            continue;

        if (pen_down)
            map[y][x] = 'O';
    }

    for (;iterations > 0; iterations--)
        exec_iteration(width, height, map);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            putchar(map[i][j]);
        putchar('\n');
    }

    return 0;
}
