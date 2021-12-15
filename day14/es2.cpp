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

int indexOf(std::vector<std::pair<std::string, long long int>> combination, std::string var)
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
    std::vector<std::pair<std::string, long long int>> countComb1;
    std::vector<std::pair<std::string, long long int>> countComb2;
    for (int i = 2; i < content.size(); i++)
    {
        std::string comb = split(content[i], " -> ")[0];
        combination.push_back(std::pair<std::string, std::string>(comb, split(content[i], " -> ")[1]));
        countComb1.push_back(std::pair<std::string, long long int>(comb, 0));
        countComb2.push_back(std::pair<std::string, long long int>(comb, 0));
    }
    for (int i = 0; i < initial.size() - 1; i++)
    {
        std::string couple = initial.substr(i, 2);
        int index = indexOf(countComb1, couple);
        if (index == -1)
        {
            std::cout << "Incomplete Table!\n";
            return;
        }
        countComb1[index].second++;
        //countComb2[index].second++;
    }
    for (int i = 0; i < countComb1.size(); i++)
    {
        std::cout << countComb1[i].first << ") " << countComb1[i].second << "\t==\t" << countComb2[i].second << "\n";
    }
    std::cout << "=====================\n";
    int steps = 40;
    for (int step = 0; step < steps; step++)
    {
        for (int i = 0; i < countComb1.size(); i++)
        {
            if (countComb1[i].second > 0)
            {
                std::string first = countComb1[i].first;
                std::string var = findValueAt(combination, first);
                //std::cout << first << " -> " << var << "\n";
                int index1 = indexOf(countComb1, first[0] + var);
                int index2 = indexOf(countComb1, var + first[1]);
                countComb2[index1].second += countComb1[i].second;
                countComb2[index2].second += countComb1[i].second;
                countComb1[i].second = 0;
            }
        }
        /*for (int i = 0; i < countComb1.size(); i++)
        {
            std::cout << countComb1[i].first << ") " << countComb1[i].second << "\t==\t" << countComb2[i].second << "\n";
        }
        std::cout << "=====================\n";*/
        countComb1 = countComb2;
        for (int i = 0; i < countComb1.size(); i++)
        {
            countComb2[i].second = 0;
        }
    }
    for (int i = 0; i < countComb1.size(); i++)
    {
        std::cout << countComb1[i].first << ") " << countComb1[i].second << "\t==\t" << countComb2[i].second << "\n";
    }
    std::cout << "=====================\n";
    std::vector<std::pair<std::string, long long int>> counts;
    for (int i = 0; i < countComb1.size(); i++)
    {
        long long int var = countComb1[i].second;
        std::string couple = countComb1[i].first;
        for (int j = 0; j <= 0; j++)
        {
            std::string c = couple.substr(j, 1);
            int index = indexOf(counts, c);
            if (index == -1)
            {
                counts.push_back(std::pair<std::string, long long int>(c, var));
            }
            else
            {
                counts[index].second += var;
            }
        }
    }
    counts[indexOf(counts, initial.substr(initial.size() - 1, 1))].second++;
    for (int i = 0; i < counts.size(); i++)
    {
        std::cout << counts[i].first << ") " << counts[i].second << "\n";
    }
    long long int max = 0;
    long long int min = INT64_MAX;
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