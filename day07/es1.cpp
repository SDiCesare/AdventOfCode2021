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

int min(int vector[], int length)
{
    int min = INT16_MAX;
    for (int i = 0; i < length; i++)
    {
        if (vector[i] < min)
        {
            min = vector[i];
        }
    }
    return min;
}

int max(int vector[], int length)
{
    int max = INT16_MIN;
    for (int i = 0; i < length; i++)
    {
        if (vector[i] > max)
        {
            max = vector[i];
        }
    }
    return max;
}

int getStepCost(int step)
{
    if (step == 1)
    {
        return step;
    }
    if (step < 1)
    {
        return 0;
    }
    return step + getStepCost(step - 1);
}

void analyzeData(std::vector<std::string> content)
{
    std::vector<std::string> orizontalPositions = split(content[0], ",");
    const int length = orizontalPositions.size();
    int positions[length];
    for (int i = 0; i < length; i++)
    {
        positions[i] = std::stoi(orizontalPositions[i]);
        //std::cout << positions[i] << "\n";
    }
    int minFuel = -1;
    int fuel = 0;
    int pos = 0;
    int start = min(positions, length);
    int end = max(positions, length);
    std::cout << start << " <-> " << end << "\n";
    for (int i = start; i < end; i++)
    {
        for (int j = 0; j < length; j++)
        {
            fuel += getStepCost(std::abs(positions[j] - i));
        }
        if (minFuel > fuel || minFuel == -1)
        {
            pos = i;
            minFuel = fuel;
        }
        std::cout << i << " -> " << fuel << "\n";
        fuel = 0;
    }
    std::cout << "Min Fuel: " << minFuel << " To position: "
              << pos << "\n";
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