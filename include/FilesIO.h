// Autore: Alessandro Rotondo (2032447)

#ifndef FILES_IO_H
#define FILES_IO_H

#include <vector>
#include <string>
#include <queue>

const std::string defaultLogPath = "log/log.txt";

/*
    metodo che restituisce una coda (FIFO) di stringhe (comandi di gioco) leggendo le righe da file
*/
std::queue<std::string> importLog (std::string path);

/*
    metodo che scrive il log di una partita a partre da un vettore di stringhe (comandi di gioco)
*/
void exportLog(std::vector<std::string> inData, std::string path = defaultLogPath);


#endif //FILES_IO_H