#include <stdlib.h>

class Map
{
public:
    Map(int _width, int _height) : width(_width), height(_height)
    {
        map = (int **)malloc(width * sizeof(int *));
        for (int i = 0; i < height; i++)
        {
            map[i] = (int *)malloc(height * sizeof(int));
        }
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                map[i][j] = 0;
            }
        }
    }

public:
    void print()
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                std::cout << map[i][j];
                if (j < height - 1)
                {
                    std::cout << ",";
                }
            }
            std::cout << "\n";
        }
    }

    int *operator[](int index)
    {
        return map[index];
    }

    int getWidth()
    {
        return width;
    }

    int getHeight()
    {
        return height;
    }

private:
    int **map;
    const int height;
    const int width;
};