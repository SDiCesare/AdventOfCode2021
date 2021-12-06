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

void runSymulation(long long int fishes[10], int duration)
{
    for (int day = 1; day <= duration; day++)
    {
        //Pass a day for the fishes
        for (int i = 0; i < 10; i++)
        {
            long long int count = fishes[i];
            if (i == 0)
            {
                fishes[7] += count;
                fishes[9] += count;
                fishes[0] = 0;
            }
            else
            {
                fishes[i - 1] += count;
                fishes[i] = 0;
            }
        }
        std::cout << "Day " << day << "\n";
        for (int i = 0; i < 10; i++)
        {
            std::cout << "(" << i << "," << fishes[i] << ")";
        }
        std::cout << "\n";
    }
    long long int total = 0;
    for (int i = 0; i < 10; i++)
    {
        total += fishes[i];
    }
    std::cout << "Total fish after " << duration << " days: " << total << "\n";
}

void analyzeData(std::vector<std::string> content)
{
    std::vector<std::string> fishesAge = split(content[0], ",");
    long long int fishes[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < fishesAge.size(); i++)
    {
        std::string var = fishesAge[i];
        fishes[std::stoi(var)]++;
    }
    runSymulation(fishes, 256);
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