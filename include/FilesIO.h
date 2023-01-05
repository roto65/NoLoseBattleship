#ifndef FILES_IO_H
#define FILES_IO_H

#include <vector>
#include <string>

std::vector<std::string> importLog (std::string path);
void exportLog(std::vector<std::string> matchActions);


#endif //FILES_IO_H