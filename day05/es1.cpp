#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "map.h"

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

void incrementMap(Map *map, int x1, int y1, int x2, int y2)
{
    int xFactor = abs(x2 - x1);
    int yFactor = abs(y2 - y1);
    int start = 0, length = 0;
    if (xFactor == 0)
    { //Rect: x = C -> moves only Y
        std::cout << "x = " << x1 << "\n";
        start = (y1 < y2) ? y1 : y2;
        length = yFactor + start + 1;
        for (int i = start; i < length; i++)
        {
            map->operator[](x1)[i]++;
        }
    }
    else if (yFactor == 0)
    { //Rect: y = C -> moves only X
        std::cout << "y = " << y1 << "\n";
        start = (x1 < x2) ? x1 : x2;
        length = xFactor + start + 1;
        for (int i = start; i < length; i++)
        {
            map->operator[](i)[y1]++;
        }
    }
    else
    { //Standard Rect: y = mx + q
        start = (x1 < x2) ? x1 : x2;
        length = xFactor + start + 1;
        float m = (y2 - y1) / (float)(x2 - x1);
        float q = ((x1 * y2) - (x1 * y1)) / (float)(x2 - x1);
        q = y1 - q;
        std::cout << "y = " << m << "x + " << q << "\n";
        for (int x = start; x < length; x++)
        {
            int y = m * x;
            y = y + q;
            map->operator[](x)[y]++;
        }
    }
}

void analyzeData(std::vector<std::string> content)
{
    Map map(1000, 1000);
    for (int i = 0; i < content.size(); i++)
    {
        std::string var = content[i];
        std::vector<std::string> couple = split(var, " -> ");
        int x1 = std::stoi(couple[0].substr(0, couple[0].find(",")));
        int y1 = std::stoi(couple[0].substr(couple[0].find(",") + 1));
        int x2 = std::stoi(couple[1].substr(0, couple[1].find(",")));
        int y2 = std::stoi(couple[1].substr(couple[1].find(",") + 1));
        //Solution 1 -> only for x1 == x2 || y1 == y2
        //Solution 2 -> for every coords
        incrementMap(&map, x1, y1, x2, y2);
    }
    int count = 0;
    int minFactor = 2;
    for (int i = 0; i < map.getWidth(); i++)
    {
        for (int j = 0; j < map.getHeight(); j++)
        {
            if (map[i][j] >= minFactor)
            {
                count++;
            }
        }
    }
    std::cout << "Count[" << count << "]\n";
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