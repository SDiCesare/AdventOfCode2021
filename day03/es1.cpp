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

int getCommonBit(std::vector<std::string> var, int index) {
    int zeroCount = 0;
    int unoCount = 0;
    for (auto i = var.begin(); i < var.end(); i++) {
        std::string v = *i;
        char c = v[index];
        if (c == '0') {
            zeroCount++;
        } else if (c == '1') {
            unoCount++;
        }
    }
    int out;
    if (zeroCount > unoCount) {
        out = 0;
    } else {
        out = 1;
    }
    return out;
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
    std::string gamma;
    std::string epsilon;
    inFile->close();
    //Assuming all Input has same bit-length 
    int l =  content.begin()->size();
    for (int i = 0; i < l; i++) {
        int mostCommon = getCommonBit(content, i);
        gamma = gamma + std::to_string(mostCommon);
        epsilon = epsilon + std::to_string(((mostCommon == 0)? 1 : 0));
        //std::cout << gamma << "\n" << epsilon << "\n====\n";
    }
    int gammaValue = std::stoi(gamma, nullptr, 2);
    int epsilonValue = std::stoi(epsilon, nullptr, 2);
    std::cout << "Gamma:\t\t" << gamma << "\nEpsilon:\t" << epsilon << "\n";
    std::cout << "Gamma:\t\t" << gammaValue << "\nEpsilon:\t" << epsilonValue << "\n";
    std::cout << gammaValue * epsilonValue << "\n";
    return 0;
}