#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

#include "board.h"

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

bool isNumber(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
    {
        ++it;
    }
    return !s.empty() && it == s.end();
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
    std::vector<std::string> extractions = split(content[0], ",");
    //Parse Boards
    std::vector<Board> boards;
    int contentIndex = 2;
    while (true)
    {
        Board *board = new Board(5, 5);
        for (int i = 0; i < board->getHeight(); i++)
        {
            std::string vars = content[contentIndex + i];
            std::vector<std::string> numbers = split(vars, " ");
            for (int j = 0; j < numbers.size(); j++)
            {
                if (!isNumber(numbers[j]))
                {
                    continue;
                }
                int number = std::stoi(numbers[j]);
                board->put(Number(number));
            }
        }
        board->toString();
        std::cout << "\n";
        boards.push_back(*board);
        contentIndex += 6;
        if (contentIndex >= (content.size() - 2))
        {
            break;
        }
    }
    //Play the game
    for (int i = 0; i < extractions.size(); i++)
    {
        int number = std::stoi(extractions[i]);
        for (int j = 0; j < boards.size(); j++)
        {
            boards[j].mark(number);
            if (boards[j].hasWin())
            {
                //Calculate the Winner Bord Value
                std::cout << "Board Number " << j << " Won \n";
                Board b = boards[j];
                int sum = 0;
                for (int x = 0; x < b.getWidth(); x++)
                {
                    for (int y = 0; y < b.getHeight(); y++)
                    {
                        if (!b.get(x, y).isMarked())
                        {
                            sum += b.get(x, y).getValue();
                        }
                    }
                }
                std::cout << "Board Value [" << sum * number << "]\n";
                return;
            }
        }
    }
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