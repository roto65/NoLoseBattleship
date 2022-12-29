#ifndef POS_H
#define POS_H

#include <string>

struct Pos {

    int x, y;

    Pos ();
    Pos (int X, int Y);
    Pos (std::string s);

};

Pos operator+ (Pos p1, Pos p2);
Pos operator- (Pos p1, Pos p2);

bool operator== (Pos p1, Pos p2);

double distance(Pos p1, Pos p2);

#endif //POS_H