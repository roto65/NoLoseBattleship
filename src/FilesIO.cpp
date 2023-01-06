#include <vector>
#include <string>
#include <fstream>
#include <queue>

#include "FilesIO.h"

std::queue<std::string> importLog (std::string path) {
    std::queue<std::string> matchActions;
    std::string line;
    std::ifstream logFile(path);

    while (std::getline(logFile, line)) {
        matchActions.push(line);
    }

    logFile.close();

    return matchActions;
}

void exportLog (std::vector<std::string> matchActions, std::string path) {
    std::ofstream logFile(path);

    for (std::string action : matchActions) {
        logFile << action << std::endl;
    }
    
    logFile.close();
}