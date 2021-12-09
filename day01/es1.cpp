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


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please, insert a file.txt as argument");
        exit(1);
    }
    char* fileName = argv[1]; 
    printf("Reading Data From:\n%s\n", fileName);
    std::ifstream *inFile = new std::ifstream();
    inFile->open(fileName);
    if (!inFile) {
        printf("Unable to open Data File!\n");
        exit(1);
    }
    std::vector<std::string> fileContent = getFileContent(inFile);
    inFile->close();
    printf("End Reading Data\n");
    int *previous = nullptr;
    int increments = 0;
    for (auto i = fileContent.begin(); i != fileContent.end(); i++) {
        std::string s = *i;
        int var = std::stoi(s);
        if (previous == nullptr) {
            printf("%d (N/A - no previous sum)\n", var);
            previous = (int *)malloc(sizeof (int));
        } else {
            if (var > *previous) {
                printf("%d (increased)\n", var);
                increments++;
            } else if (var < *previous) {
                printf("%d (decreased)\n", var);
            } else {
                printf("%d (no change)\n", var);
            }
        }
        *previous = var;
    }
    printf("Total Increments: %d\n", increments);
    return 0;
}