#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

long long int getBasinSize(int **map, int x, int y, int width, int height, std::string *alreadyDone)
{
    long long int size = 1;
    int v1 = map[x][y];
    for (int xOff = -1; xOff <= 1; xOff++)
    {
        for (int yOff = -1; yOff <= 1; yOff++)
        {
            //Ignore Diagonals
            if (xOff != 0 && yOff != 0)
            {
                continue;
            }
            //Esclude the Starting Spot
            if (xOff == 0 && yOff == 0)
            {
                continue;
            }
            //Check out of bounds
            if (x + xOff < 0 || x + xOff >= width || y + yOff < 0 || y + yOff >= height)
            {
                continue;
            }
            //Check Already Done
            std::string stringVar = std::to_string(x + xOff) + "," + std::to_string(y + yOff) + " ";
            if (alreadyDone->find(stringVar) != std::string::npos)
            {
                continue;
            }
            int v2 = map[x + xOff][y + yOff];
            if (v2 != 9 && v2 > v1)
            {
                *alreadyDone += stringVar;
                size += getBasinSize(map, x + xOff, y + yOff, width, height, alreadyDone);
            }
        }
    }
    return size;
}

void analyzeData(std::vector<std::string> content)
{
    int width = content.size();
    int height = content[0].size();
    int **map = (int **)malloc(sizeof(int *) * width);
    for (int i = 0; i < content.size(); i++)
    {
        std::string line = content[i];
        map[i] = (int *)malloc(sizeof(int) * height);
        for (int j = 0; j < height; j++)
        {
            map[i][j] = (int)(line[j] - '0');
        }
    }
    //Check min indexes
    std::vector<std::string> indexes;
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
                std::string s = std::to_string(i) + "," + std::to_string(j);
                indexes.push_back(s);
            }
        }
    }
    //Calculate Basin
    int max[3] = {1, 1, 1};
    for (int i = 0; i < indexes.size(); i++)
    {
        std::string s = "";
        std::vector<std::string> coords = split(indexes[i], ",");
        int x = std::stoi(coords[0]);
        int y = std::stoi(coords[1]);
        long long int basinValue = getBasinSize(map, x, y, width, height, &s);
        std::cout << indexes[i] << "\t->\t" << basinValue << "\n";
        if (basinValue > max[0])
        {
            if (basinValue > max[1])
            {
                if (basinValue > max[2])
                {
                    max[0] = max[1];
                    max[1] = max[2];
                    max[2] = basinValue;
                }
                else
                {
                    max[0] = max[1];
                    max[1] = basinValue;
                }
            }
            else
            {
                max[0] = basinValue;
            }
        }
    }
    std::cout << max[0] << "-" << max[1] << "-" << max[2] << "\n";
    std::cout << max[0] * max[1] * max[2] << "\n";
    std::cout << indexes.size() << "\n";
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