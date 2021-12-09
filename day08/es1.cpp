#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

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

int getEmptyIndex(char c[])
{
    bool found[8] = {false, false, false, false, false, false, false, false};
    for (int i = 0; i < 7; i++)
    {
        if (c[i] != 'z')
        {
            int var = c[i] - 'a';
            found[var] = true;
        }
    }
    for (int i = 0; i < 7; i++)
    {
        if (!found[i])
        {
            return i;
        }
    }
    return -1;
}

void analyzeData(std::vector<std::string> content)
{
    int unique = 0;
    for (int k = 0; k < content.size(); k++)
    {
        std::vector<std::string> out = split(split(content[k], " | ")[1], " ");
        for (int i = 0; i < out.size(); i++)
        {
            std::string s = out[i];
            switch (s.size())
            {
            case 2:
            case 3:
            case 4:
            case 7:
                unique++;
                std::cout << s << "\t\t->\t" << unique << "\n";
                break;
            }
        }
    }
    std::cout << unique << "\n";
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