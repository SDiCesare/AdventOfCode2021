#include <stdio.h>

class Paper
{
public:
    Paper(int _width, int _height, std::vector<std::pair<int, int>> points)
    {
        width = _height;
        height = _width;
        paper = (int **)malloc(sizeof(int *) * width);
        for (int i = 0; i < width; i++)
        {
            paper[i] = (int *)malloc(sizeof(int) * height);
        }
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                paper[i][j] = 0;
            }
        }
        for (auto point = points.begin(); point != points.end(); point++)
        {
            paper[point->second][point->first] = 1;
        }
    }

    void print()
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                std::cout << paper[i][j];
                if (j < height - 1)
                {
                    std::cout << ",";
                }
            }
            std::cout << "\n";
        }
    }

    void foldAtY(int y)
    {
        for (int i = 1; y + i < height && y - i >= 0; i++)
        {
            for (int x = 0; x < width; x++)
            {
                if (paper[x][y + i] == 1)
                {
                    paper[x][y + i] = 0;
                    paper[x][y - i] = 1;
                }
            }
        }
        height = y;
    }

    void foldAtX(int x)
    {
        for (int i = 1; x + i < width && x - i >= 0; i++)
        {
            for (int y = 0; y < height; y++)
            {
                if (paper[x + i][y] == 1)
                {
                    paper[x + i][y] = 0;
                    paper[x - i][y] = 1;
                }
            }
        }
        width = x;
    }

    int getPointCount()
    {
        int count = 0;
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                if (paper[i][j] == 1)
                {
                    count++;
                }
            }
        }
        return count;
    }

private:
    int **paper;
    int width;
    int height;
};