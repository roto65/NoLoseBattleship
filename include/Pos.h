#ifndef POS_H
#define POS_H

#include <string>

/*
    struct che gestisce le coordinate all'interno della griglia di gioco.
    Le lettere vengono trasformate in numeri all'interno dei costruttori 
*/
struct Pos {

    int x, y;

    Pos ();
    Pos (int X, int Y);
    Pos (std::string s);

    /*
        metodo che prende una coordinata è la converte in una stringa
    */
    std::string toString();

};

Pos operator+ (Pos p1, Pos p2);
Pos operator- (Pos p1, Pos p2);
bool operator== (Pos p1, Pos p2);

/*
    metodo che restituisce la distanza tra due posizioni
*/
double distance(Pos p1, Pos p2);

#endif //POS_H