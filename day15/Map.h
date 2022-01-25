#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>

class Map
{
public:
    Map(int _width, int _height)
    {
        width = _width;
        height = _height;
        map = (int **)malloc(height);
        for (int i = 0; i < height; i++)
        {
            map[i] = (int *)malloc(sizeof(int) * width);
            for (int j = 0; j < width; j++)
            {
                map[i][j] = 0;
            }
        }
    }

    void initialize(std::vector<std::string> content)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                std::cout << i << "," << j;
                std::cout << "->\t" << map[i][j] << "<=" << content[i][j] << "\n";
                map[i][j] = content[i][j] - '0';
            }
        }
        std::cout << "Map initialized!\n";
    }

    void print()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                std::cout << map[i][j] << ",";
            }
            std::cout << "\n";
        }
    }

    int getPathLength(int x = 0, int y = 0)
    {
        int v1 = INT16_MAX;
        int v2 = INT16_MAX;
        if (x == width - 1 && y == height - 1)
        {
            return map[x][y] - map[0][0];
        }
        if (x + 1 < width)
        {
            v1 = map[x][y] + getPathLength(x + 1, y);
        }
        if (y + 1 < height)
        {
            v2 = map[x][y] + getPathLength(x, y + 1);
        }
        return v1 < v2 ? v1 : v2;
    }

    int *operator[](const int index)
    {
        return map[index];
    }

private:
    int width;
    int height;
    int **map;
};