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

        char cod[8] = {'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z'};
        char c[10][8] = {
            {'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z'},
            {'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z'},
            {'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z'},
            {'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z'},
            {'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z'},
            {'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z'},
            {'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z'},
            {'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z'},
            {'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z'},
            {'z', 'z', 'z', 'z', 'z', 'z', 'z', 'z'}};
        std::vector<std::string> out = split(split(content[k], " | ")[0], " ");
        std::vector<std::string> o1 = split(split(content[k], " | ")[1], " ");
        for (int i = 0; i < o1.size(); i++)
        {
            out.push_back(o1[i]);
        }
        //Chek Unique Number [1, 4, 7, 8]
        for (int i = 0; i < out.size(); i++)
        {
            std::string s = out[i];
            switch (s.size())
            {
            case 7:
                for (int x = 0; x < 8; x++)
                {
                    c[8][x] = s[x];
                }
                break;
            case 2:
                c[1][2] = s[0];
                c[1][5] = s[1];
                break;
            case 3:
                c[7][0] = s[0];
                c[7][2] = s[1];
                c[7][5] = s[2];
                break;
            case 4:
                c[4][1] = s[0];
                c[4][2] = s[1];
                c[4][3] = s[2];
                c[4][5] = s[3];
                break;
            }
        }
        //Check 6 Segment Number [0, 6, 9]
        for (int i = 0; i < out.size(); i++)
        {
            std::string s = out[i];
            if (s.size() == 6)
            {
                //Check 6 [diff 1 with 7]
                int equals = 0;
                for (int j = 0; j < 6; j++)
                {
                    if (s[j] == c[7][0] || s[j] == c[7][2] || s[j] == c[7][5])
                    {
                        equals++;
                    }
                }
                if (equals == 2)
                {
                    c[6][0] = s[0];
                    c[6][1] = s[1];
                    c[6][3] = s[2];
                    c[6][4] = s[3];
                    c[6][5] = s[4];
                    c[6][6] = s[5];
                    continue;
                }
                //Check 0 [diff 1 with 4]
                equals = 0;
                for (int j = 0; j < 6; j++)
                {
                    if (s[j] == c[4][1] || s[j] == c[4][2] || s[j] == c[4][3] || s[j] == c[4][5])
                    {
                        equals++;
                    }
                }
                if (equals == 3)
                {
                    c[0][0] = s[0];
                    c[0][1] = s[1];
                    c[0][2] = s[2];
                    c[0][4] = s[3];
                    c[0][5] = s[4];
                    c[0][6] = s[5];
                    continue;
                }
                //9 -> No 0 or 6
                c[9][0] = s[0];
                c[9][1] = s[1];
                c[9][2] = s[2];
                c[9][3] = s[3];
                c[9][5] = s[4];
                c[9][6] = s[5];
            }
        }
        //Check 5 Segment Number [2, 3, 5]
        for (int i = 0; i < out.size(); i++)
        {
            std::string s = out[i];
            if (s.size() == 5)
            {
                int equals = 0;
                //Check 3 [diff 0 with 1]
                for (int j = 0; j < 5; j++)
                {
                    if (s[j] == c[1][2] || s[j] == c[1][5])
                    {
                        equals++;
                    }
                }
                if (equals == 2)
                {
                    c[3][0] = s[0];
                    c[3][2] = s[1];
                    c[3][3] = s[2];
                    c[3][5] = s[3];
                    c[3][6] = s[4];
                    continue;
                }
                //Check 5 [diff 1 with 4]
                equals = 0;
                for (int j = 0; j < 5; j++)
                {
                    if (s[j] == c[4][1] || s[j] == c[4][2] || s[j] == c[4][3] || s[j] == c[4][5])
                    {
                        equals++;
                    }
                }
                if (equals == 3)
                {
                    c[5][0] = s[0];
                    c[5][1] = s[1];
                    c[5][3] = s[2];
                    c[5][5] = s[3];
                    c[5][6] = s[4];
                    continue;
                }
                //2 -> Not 3 or 5
                c[2][0] = s[0];
                c[2][2] = s[1];
                c[2][3] = s[2];
                c[2][4] = s[3];
                c[2][6] = s[4];
            }
        }
        //Cod
        //Check value for i [2, 3, 4]
        int index = getEmptyIndex(c[0]);
        cod[3] = 'a' + index;
        index = getEmptyIndex(c[6]);
        cod[2] = 'a' + index;
        index = getEmptyIndex(c[9]);
        cod[4] = 'a' + index;
        //Check value for i = 0
        for (int i = 0; i < 8; i++)
        {
            if (c[7][i] == 'z')
            {
                continue;
            }
            if (!(c[7][i] == c[4][1] || c[7][i] == c[4][2] || c[7][i] == c[4][3] || c[7][i] == c[4][5]))
            {
                cod[0] = c[7][i];
                break;
            }
        }
        //Check value for i = 6
        for (int i = 0; i < 8; i++)
        {
            if (c[2][i] == 'z')
            {
                continue;
            }
            if (!(c[2][i] == cod[0] || c[2][i] == cod[2] || c[2][i] == cod[3] || c[2][i] == cod[4]))
            {
                cod[6] = c[2][i];
                break;
            }
        }
        //Check value for i = 5
        for (int i = 0; i < 8; i++)
        {
            if (c[3][i] == 'z')
            {
                continue;
            }
            if (!(c[3][i] == cod[0] || c[3][i] == cod[2] || c[3][i] == cod[3] || c[3][i] == cod[6]))
            {
                cod[5] = c[3][i];
                break;
            }
        }
        index = getEmptyIndex(cod);
        cod[1] = 'a' + index;
        {
            std::cout << " " << cod[0] << cod[0] << cod[0] << " \n";
            std::cout << cod[1] << "   " << cod[2] << " \n";
            std::cout << cod[1] << "   " << cod[2] << " \n";
            std::cout << cod[1] << "   " << cod[2] << " \n";
            std::cout << " " << cod[3] << cod[3] << cod[3] << " \n";
            std::cout << cod[4] << "   " << cod[5] << " \n";
            std::cout << cod[4] << "   " << cod[5] << " \n";
            std::cout << cod[4] << "   " << cod[5] << " \n";
            std::cout << " " << cod[6] << cod[6] << cod[6] << " \n";
        }
        int sum = 0;
        for (int i = 0; i < o1.size(); i++)
        {
            std::string s = o1[i];
            int pow = std::pow(10, o1.size() - (i + 1));
            switch (s.size())
            {
            case 2:
                sum += 1 * pow;
                break;
            case 3:
                sum += 7 * pow;
                break;
            case 4:
                sum += 4 * pow;
                break;
            case 5:
                if (s.find(cod[4]) != std::string::npos)
                {
                    sum += 2 * pow;
                }
                else if (s.find(cod[1]) != std::string::npos)
                {
                    sum += 5 * pow;
                }
                else
                {
                    sum += 3 * pow;
                }
                break;
            case 6:
                if (s.find(cod[4]) == std::string::npos)
                {
                    sum += 9 * pow;
                }
                else if (s.find(cod[2]) == std::string::npos)
                {
                    sum += 6 * pow;
                }
                else
                {
                    sum += 0 * pow;
                }
                break;
            case 7:
                sum += 8 * pow;
                break;
            }
        }
        std::cout << k << " -> " << sum << "\n";
        std::cout << "=====================================\n";
        unique += sum;
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