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

int getCommonBit(std::vector<std::string> var, int index)
{
    int zeroCount = 0;
    int unoCount = 0;
    for (auto i = var.begin(); i < var.end(); i++)
    {
        std::string v = *i;
        char c = v[index];
        if (c == '0')
        {
            zeroCount++;
        }
        else if (c == '1')
        {
            unoCount++;
        }
    }
    int out;
    if (zeroCount > unoCount)
    {
        out = 0;
    }
    else
    {
        out = 1;
    }
    return out;
}

std::vector<std::string> filterBy(std::vector<std::string> content, int bit, int index)
{
    std::vector<std::string> out;
    for (auto i = content.begin(); i < content.end(); i++)
    {
        std::string var = *i;
        if (var[index] - '0' == bit)
        {
            out.push_back(var);
        }
    }
    return out;
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
    //Assuming all Input has same bit-length
    const int l = content.begin()->size();
    std::vector<std::string> oxygen;
    std::vector<std::string> co2;
    int *oxygenFilter = new int[l];
    int *cO2Filter = new int[l];
    inFile->close();
    int mostCommon = getCommonBit(content, 0);
    oxygen = filterBy(content, mostCommon, 0);
    co2 = filterBy(content, (mostCommon == 0) ? 1 : 0, 0);
    for (int i = 1; i < l; i++)
    {
        mostCommon = getCommonBit(oxygen, i);
        if (oxygen.size() > 1)
        {
            oxygen = filterBy(oxygen, mostCommon, i);
        }
        mostCommon = getCommonBit(co2, i);
        if (co2.size() > 1)
        {
            co2 = filterBy(co2, (mostCommon == 0) ? 1 : 0, i);
        }
    }
    int oxygenValue = std::stoi(oxygen[0], nullptr, 2);
    int co2Value = std::stoi(co2[0], nullptr, 2);
    std::cout << oxygen[0] << "X" << co2[0] << "\n";
    std::cout << oxygenValue << "X" << co2Value << "\n";
    std::cout << oxygenValue * co2Value << "\n";
    return 0;
}