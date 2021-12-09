#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

#include "lanternfish.h"

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

void runSymulation(std::vector<Lanternfish> fishes, int duration)
{
    std::cout << "Initial State: ";
    for (auto fish = fishes.begin(); fish < fishes.end(); fish++)
    {
        std::cout << fish->getAge();
        if (fish != fishes.end())
        {
            std::cout << ",";
        }
    }
    std::cout << "\n";
    for (int day = 1; day <= duration; day++)
    {
        //Pass a day for the fishes
        std::cout << "Day " << day << "\n";
        int l = fishes.size();
        for (int i = 0; i < l; i++)
        {
            if (fishes[i].getAge() == 0)
            {
                fishes.push_back(*fishes[i].makeChild());
            }
            fishes[i].tick();
        }
        std::cout << "\n";
    }
    std::cout << "Total fish after " << duration << " days: " << fishes.size() << "\n";
}

void analyzeData(std::vector<std::string> content)
{
    std::vector<std::string> fishesAge = split(content[0], ",");
    std::vector<Lanternfish> fishes;
    for (int i = 0; i < fishesAge.size(); i++)
    {
        std::string var = fishesAge[i];
        fishes.push_back(Lanternfish(std::stoi(var)));
    }
    runSymulation(fishes, 80);
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