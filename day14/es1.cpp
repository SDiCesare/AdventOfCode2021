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

int indexOf(std::vector<std::pair<std::string, int>> combination, std::string var)
{
    for (int i = 0; i < combination.size(); i++)
    {
        if (combination[i].first == var)
        {
            return i;
        }
    }
    return -1;
}

std::string findValueAt(std::vector<std::pair<std::string, std::string>> combination, std::string var)
{
    for (auto i = combination.begin(); i != combination.end(); i++)
    {
        if (i->first == var)
        {
            return i->second;
        }
    }
    return NULL;
}

void analyzeData(std::vector<std::string> content)
{
    std::string initial = content[0];
    std::vector<std::pair<std::string, std::string>> combination;
    for (int i = 2; i < content.size(); i++)
    {
        std::string comb = split(content[i], " -> ")[0];
        combination.push_back(std::pair<std::string, std::string>(comb, split(content[i], " -> ")[1]));
    }
    int steps = 10;
    for (int step = 0; step < steps; step++)
    {
        std::string sAtStep = "";
        for (int i = 0; i < initial.size() - 1; i++)
        {
            std::string s = initial.substr(i, 2);
            std::string var = findValueAt(combination, s);
            if (i == 0)
            {
                sAtStep += s[0] + var + s[1];
            }
            else
            {
                sAtStep += var + s[1];
            }
            //std::cout << s << " -> " << var << "\n";
        }
        //std::cout << step << ")" << sAtStep << "\n";
        initial = sAtStep;
    }
    std::cout << steps << ")" << initial << "\n";
    std::vector<std::pair<std::string, int>> counts;
    for (int i = 0; i < initial.size(); i++)
    {
        std::string c = "" + (char)initial[i];
        int index = indexOf(counts, c);
        if (index == -1)
        {
            counts.push_back(std::pair<std::string, int>(c, 1));
        }
        else
        {
            counts[index].second++;
        }
    }
    int max = 0;
    int min = INT16_MAX;
    for (auto i = counts.begin(); i != counts.end(); i++)
    {
        if (i->second > max)
        {
            max = i->second;
        }
        if (i->second < min)
        {
            min = i->second;
        }
    }
    std::cout << max << "-" << min << "=" << (max - min) << "\n";
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