#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

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

void analyzeData(std::vector<std::string> content)
{
    int width = content.size();
    int height = content[0].size();
    int map[width][height];
    for (int i = 0; i < content.size(); i++)
    {
        std::string line = content[i];
        for (int j = 0; j < height; j++)
        {
            map[i][j] = (int)(line[j] - '0');
        }
    }
    int minCount = 0;
    int sum = 0;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int value = map[i][j];
            bool isMin = true;
            for (int xOff = -1; xOff <= 1; xOff++)
            {
                for (int yOff = -1; yOff <= 1; yOff++)
                {
                    //Check out of bounds
                    if (i + xOff < 0 || i + xOff >= width || j + yOff < 0 || j + yOff >= height)
                    {
                        continue;
                    }
                    int var = map[i + xOff][j + yOff];
                    if (var < value)
                    {
                        isMin = false;
                    }
                }
            }
            if (isMin)
            {
                minCount += 1;
                sum += 1 + value;
            }
        }
    }
    std::cout << "Min Count:\t" << minCount << "\nSum:\t\t" << sum << "\n"; 
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