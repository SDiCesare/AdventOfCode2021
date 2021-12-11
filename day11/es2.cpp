#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <windows.h>

std::vector<std::string> getFileContent(std::ifstream *inFile)
{
    std::vector<std::string> out;
    std::string line;
    while (std::getline(*inFile, line))
    {
        out.push_back(line);
    }
    return out;
}

std::vector<std::string> split(std::string s, std::string delimiter)
{
    std::vector<std::string> out;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        out.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    out.push_back(s);
    return out;
}

void spotTick(int width, int height, int **map, int x, int y, std::vector<std::string> *ignoreList)
{
    if (map[x][y] >= 9)
    {
        map[x][y] = 0;
        ignoreList->push_back(std::to_string(x) + "," + std::to_string(y));
        for (int xOff = -1; xOff <= 1; xOff++)
        {
            int i = x + xOff;
            if (i < 0 || i >= width)
            {
                continue;
            }
            for (int yOff = -1; yOff <= 1; yOff++)
            {
                int j = y + yOff;
                if (xOff == 0 && yOff == 0)
                {
                    continue;
                }
                if (j < 0 || j >= height)
                {
                    continue;
                }
                spotTick(width, height, map, i, j, ignoreList);
            }
        }
    }
    else if (std::find(ignoreList->begin(), ignoreList->end(), std::to_string(x) + "," + std::to_string(y)) == ignoreList->end() || map[x][y] != 0)
    {
        map[x][y]++;
    }
}

bool isSync(int **map, int width, int height)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (map[i][j] != 0)
            {
                return false;
            }
        }
    }
    return true;
}

void analyzeData(std::vector<std::string> content)
{
    int brightness[10];
    int width = content[0].size();
    int height = content.size();
    int **map = (int **)malloc(sizeof(int *) * height);
    for (int i = 0; i < height; i++)
    {
        map[i] = (int *)malloc(sizeof(int) * width);
        for (int j = 0; j < width; j++)
        {
            map[i][j] = content[i][j] - '0';
        }
    }
    int day = 1;
    while (true)
    {
        std::vector<std::string> ignoreList;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                spotTick(height, width, map, i, j, &ignoreList);
            }
        }
        if (isSync(map, height, width))
        {
            std::cout << "After Day " << day << ":\n";
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    std::cout << map[i][j];
                    if (j < width - 1)
                    {
                        std::cout << ",";
                    }
                }
                std::cout << "\n";
            }
            break;
        }
        day++;
    }
}

int main(int argc, char *argv[])
{
    std::ifstream *inFile = new std::ifstream();
    std::string fileName;
    if (argc < 2)
    {
        printf("No file passed! Using default File.\n");
        fileName = "data.txt";
    }
    else
    {
        fileName = argv[1];
    }
    std::cout << "Reading Data from FIle: " << fileName << "\n";
    inFile->open(fileName);
    std::vector<std::string> content = getFileContent(inFile);
    inFile->close();
    analyzeData(content);
    return 0;
}