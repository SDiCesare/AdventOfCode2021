#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
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

std::vector<int> getFileSums(std::ifstream *inFile) {
    std::vector<std::string> vars = getFileContent(inFile);
    std::vector<int> out;
    int sequenceLength = 3;
    for (int i = 0; i < vars.size() - sequenceLength + 1; i++) {
        int sum = 0;
        for (int j = 0; j < sequenceLength; j++) {
            sum = sum + std::stoi(vars[j + i]);
        }
        out.push_back(sum);
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
    std::vector<int> fileContent = getFileSums(inFile);
    inFile->close();
    printf("End Reading Data\n");
    int *previous = nullptr;
    int increments = 0;
    char sectorName = 'A';
    for (auto i = fileContent.begin(); i != fileContent.end(); i++) {
        int var = *i;
        if (previous == nullptr) {
            printf("%c: %d (N/A - no previous sum)\n", var);
            previous = (int *)malloc(sizeof (int));
        } else {
            if (var > *previous) {
                printf("%c: %d (increased)\n", sectorName, var);
                increments++;
            } else if (var < *previous) {
                printf("%c: %d (decreased)\n", sectorName, var);
            } else {
                printf("%c: %d (no change)\n", sectorName, var);
            }
        }
        *previous = var;
        sectorName++;
    }
    printf("Total Increments: %d\n", increments);
    return 0;
}