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

std::string getKey(std::map<std::string, std::vector<std::string> *> map, std::vector<std::string> *element)
{
    for (auto i : map)
    {
        if (i.second == element)
        {
            return i.first;
        }
    }
    return "";
}

int count = 0;

void algorithm(std::vector<std::string> *start, std::vector<std::string> previous, std::map<std::string, std::vector<std::string> *> *map)
{
    std::string current = getKey(*map, start);
    for (int i = 0; i < start->size(); i++)
    {
        if (current == "start")
        {
            previous.clear();
        }
        else
        {
            if (!std::isupper(current[0]))
            {
                previous.push_back(current);
            }
        }
        std::string var = start->operator[](i);
        if (var == "start")
        { //Can't Start multiple times in a sequence
            continue;
        }
        if (var == "end")
        { //End Reached for Path
            //std::cout << "E)" << current << " -> " << var << "\n";
            //std::cout << "End Reached\n";
            count++;
            continue;
        }
        if (std::find(previous.begin(), previous.end(), var) == previous.end())
        {
            //std::cout << "N)" << current << " -> " << var << "\n";
            algorithm(map->at(var), previous, map);
        }
    }
}

void analyzeData(std::vector<std::string> content)
{
    std::map<std::string, std::vector<std::string> *> map;
    //Generate Map
    for (int i = 0; i < content.size(); i++)
    {
        std::vector<std::string> connection = split(content[i], "-");
        std::string a = connection[0];
        std::string b = connection[1];
        { //Check First
            if (map.find(a) == map.end())
            {
                map.insert(std::pair<std::string, std::vector<std::string> *>(a, new std::vector<std::string>()));
            }
            std::vector<std::string> *value = map.at(a);
            if (std::find(value->begin(), value->end(), a) == value->end())
            {
                value->push_back(b);
            }
        }

        { //Check Second
            if (map.find(b) == map.end())
            {
                map.insert(std::pair<std::string, std::vector<std::string> *>(b, new std::vector<std::string>()));
            }
            std::vector<std::string> *value = map.at(b);
            if (std::find(value->begin(), value->end(), b) == value->end())
            {
                value->push_back(a);
            }
        }
    }
    for (auto i = map.begin(); i != map.end(); i++)
    {
        std::cout << i->first << "[" << i->second->size() << "]:\n ";
        for (int j = 0; j < i->second->size(); j++)
        {
            std::cout << i->second->operator[](j) << ",";
        }
        std::cout << "\n===================\n";
    }
    //Algorithm
    algorithm(map.at("start"), std::vector<std::string>(), &map);
    std::cout << "[" << count << "]\n";
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