#include <vector>
#include <string>
#include <fstream>

#include "FilesIO.h"

std::vector<std::string> importLog (std::string path) {
    std::vector<std::string> matchActions;
    std::string line;
    std::ifstream logFile(path);

    while (std::getline(logFile, line)) {
        matchActions.push_back(line);
    }

    logFile.close();

    return matchActions;
}

void exportLog (std::vector<std::string> matchActions) {
    std::ofstream logFile("log.txt");

    for (std::string action : matchActions) {
        logFile << action << std::endl;
    }
    
    logFile.close();
}