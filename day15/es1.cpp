#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <cctype>
#include <cstring>
#include "Map.h"

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

void analyzeData(std::vector<std::string> content)
{
    int width = content[0].size();
    int height = content.size();
    std::cout << width << "X" << height << "\n";
    Map map(width, height);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << i << "," << j << "\n";
            map[i][j] = content[i][j] - '0';
        }
    }
    //map.initialize(content);
    map.print();
    int length = map.getPathLength();
    std::cout << "==================================\n";
    std::cout << length << "\n";
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