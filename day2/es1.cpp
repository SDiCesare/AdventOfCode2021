#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector> 

std::vector<std::string> getFileContent(std::ifstream *inFile) {
    std::vector<std::string> out;
    std::string line;
    while (std::getline(*inFile, line)) {
        out.push_back(line);
    }
    return out;
}

void changePos(std::string command, int *x, int *y) {
    int n = command.find("forward");
    if (n != std::string::npos) {
        n = n + 7;
        std::string sub = command.substr(n);
        int change = std::stoi(sub);
        std::cout << "Changing X of:[" << change << "]\n";
        *x = *x + change;
        return;
    }
    n = command.find("up");
    if (n != std::string::npos) {
        n = n + 2;
        std::string sub = command.substr(n);
        int change = std::stoi(sub);
        std::cout << "Going Up of:[" << change << "]\n";
        *y = *y - change;
        return;
    }
    n = command.find("down");
    if (n != std::string::npos) {
        n = n + 4;
        std::string sub = command.substr(n);
        int change = std::stoi(sub);
        std::cout << "Going Down of:[" << change << "]\n";
        *y = *y + change;
        return;
    }
}

int main(int argc, char* argv[]) {
    std::ifstream *inFile = new std::ifstream();
    std::string fileName;
    if (argc < 2) {
        printf("No file passed! Using default File.\n");
        fileName = "data.txt";
    } else {
        fileName = argv[1];
    }
    std::cout << "Reading Data from FIle: " << fileName << "\n";
    inFile->open(fileName);
    std::vector<std::string> content = getFileContent(inFile);
    inFile->close();
    int *x = (int *)malloc(sizeof (int));
    int *y = (int *)malloc(sizeof (int));
    *x = 0;
    *y = 0;
    for (auto i = content.begin(); i < content.end(); i++) {
        std::string var = *i;
        changePos(var, x, y);
    }
    std::cout << "(" << *x << "," << *y << ")\n";
    int product = *x * *y;
    std::cout << "Out:[" << product << "]\n";
    return 0;
}