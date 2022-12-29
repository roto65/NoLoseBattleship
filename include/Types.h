#ifndef TYPES_H
#define TYPES_H

// File con class dummy che verranno dichiarate e implementate nei rispettivi file .h e .cpp
// Soluzione necessaria a causa di una inclusione circolare tra le class sottostanti 
// Ship include Player, Player include DefenceField, DefenceField include Ship (utilizza solo puntatori a Ship)

class Ship;
class Player;
class DefenceField;

#endif // TYPES_H