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

void analyzeData(std::vector<std::string> content)
{
    int totalErrorValue = 0;
    for (int i = 0; i < content.size(); i++)
    {
        std::string line = content[i];
        std::vector<char> caves;
        for (int j = 0; j < line.size(); j++)
        {
            char c = line[j];
            if (c == '(' || c == '[' || c == '{' || c == '<')
            { //Open a Cave
                caves.push_back(c);
            }
            else if (c == caves[caves.size() - 1] + 2)
            { // Closing [] or {} or <>
                caves.pop_back();
            }
            else if (c == ')' && c == caves[caves.size() - 1] + 1)
            { //Closing ()
                caves.pop_back();
            }
            else
            {
                char expected = caves[caves.size() - 1] + 1;
                if (expected != ')')
                {
                    expected += 1;
                }
                switch (c)
                {
                case ')':
                    totalErrorValue += 3;
                    break;
                case ']':
                    totalErrorValue += 57;
                    break;
                case '}':
                    totalErrorValue += 1197;
                    break;
                case '>':
                    totalErrorValue += 25137;
                    break;
                }
                std::cout << "Syntax Error at line:" << (i + 1) << ":" << (j + 1) << "\n\tExpected \'" << expected << "\', Found \'" << c << "\'\n";
                //break;
            }
        }
    }
    std::cout << "Total Error [" << totalErrorValue << "]\n";
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