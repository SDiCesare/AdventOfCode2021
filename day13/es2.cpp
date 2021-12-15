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
#include "Paper.h"

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
    int foldIndex = -1;
    int width = 0;
    int height = 0;
    std::vector<std::pair<int, int>> points;
    for (int i = 0; i < content.size(); i++)
    {
        if (content[i] == "")
        {
            foldIndex = i + 1;
            break;
        }
        std::vector<std::string> coords = split(content[i], ",");
        int x = std::stoi(coords[0]);
        int y = std::stoi(coords[1]);
        points.push_back(std::pair<int, int>(x, y));
        if (x >= width)
        {
            width = x + 1;
        }
        if (y >= height)
        {
            height = y + 1;
        }
    }
    if (foldIndex == -1)
    {
        std::cout << "Invalid File Format!\n";
        return;
    }
    std::cout << width << "-" << height << "\n";
    Paper *paper = new Paper(width, height, points);
    //paper->print();

    for (int i = foldIndex; i < content.size(); i++)
    {
        std::string folding = split(content[i], "=")[1];
        if (split(content[i], "=")[0].find("x") == std::string::npos)
        {
            std::cout << "Folding y of " << folding << "\n";
            paper->foldAtX(std::stoi(folding));
        }
        else
        {
            std::cout << "Folding x of " << folding << "\n";
            paper->foldAtY(std::stoi(folding));
        }
    }
    paper->print();
    std::cout << paper->getPointCount() << "\n";
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