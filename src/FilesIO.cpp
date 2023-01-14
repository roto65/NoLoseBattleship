// Autore: Alessandro Rotondo (2032447)

#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <sstream>

#include "FilesIO.h"

std::queue<std::string> FilesIO::importLog (std::string path) {
    std::queue<std::string> outData;
    std::string line, token1, token2;
    std::ifstream logFile(path);

    while (std::getline(logFile, line)) {
        std::istringstream iss (line);
        if (line.find(' ') == std::string::npos) {
            iss >> token1;
            outData.push(token1);
        } else {
            iss >> token1 >> token2;
            outData.push(token1);
            outData.push(token2);
        }
    }

    logFile.close();

    return outData;
}

void FilesIO::exportLog (std::vector<std::string> inData, std::string path) {
    std::ofstream logFile(path);

    for (std::string action : inData) {
        logFile << action << std::endl;
    }
    
    logFile.close();
}