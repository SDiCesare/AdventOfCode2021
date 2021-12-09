#include <stdlib.h>
#include <string>
#include <iostream>

class Number
{

public:
    Number(int _value)
    {
        value = _value;
        marked = false;
    }

    void mark()
    {
        marked = true;
    }

    void unmark()
    {
        marked = false;
    }

    int getValue()
    {
        return value;
    }

    bool isMarked()
    {
        return marked;
    }

private:
    int value;
    bool marked;
};

class Board
{

public:
    Board(int _width, int _height) : width(_width), height(_height)
    {
        board = (Number **)malloc(width * sizeof(Number *));
        for (int i = 0; i < width; i++)
        {
            board[i] = (Number *)malloc(height * sizeof(Number));
        }
        xIndex = 0;
        yIndex = 0;
        finished = false;
    }

    int getWidth()
    {
        return width;
    }

    int getHeight()
    {
        return height;
    }

    bool hasFinished()
    {
        return finished;
    }

public:
    Number get(int x, int y)
    {
        return board[x][y];
    }

    void set(Number var, int x, int y)
    {
        board[x][y] = var;
        std::cout << board[x][y].getValue() << "\n";
    }

    void put(Number var)
    {
        board[xIndex][yIndex] = var;
        yIndex++;
        if (yIndex == height)
        {
            xIndex++;
            yIndex = 0;
            if (xIndex == width)
            {
                xIndex = 0;
            }
        }
    }

    void mark(int value)
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                if (board[i][j].getValue() == value)
                {
                    board[i][j].mark();
                }
            }
        }
    }

    bool hasWin()
    {
        bool marked = false;
        int winPos = -1;
        for (int i = 0; i < width; i++)
        {
            winPos = i;
            marked = true;
            for (int j = 0; j < height; j++)
            {
                if (!board[i][j].isMarked())
                {
                    marked = false;
                    break;
                }
            }
            if (marked)
            {
                std::cout << "Win On Rows " << winPos << "\n";
                return true;
            }
        }
        for (int j = 0; j < height; j++)
        {
            winPos = j;
            marked = true;
            for (int i = 0; i < width; i++)
            {
                if (!board[i][j].isMarked())
                {
                    marked = false;
                    break;
                }
            }
            if (marked)
            {
                std::cout << "Win On Cols " << winPos << "\n";
                return true;
            }
        }
        return false;
    }

    void toString()
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                std::cout << get(i, j).getValue() << (get(i, j).isMarked() ? "T" : "F") << " ";
            }
            std::cout << "\n";
        }
    }

    void markAsComplete()
    {
        finished = true;
    }

private:
    Number **board;
    int xIndex;
    int yIndex;
    const int width;
    const int height;
    bool finished;
};