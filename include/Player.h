// Autore: Alessandro Rotondo (2032447)

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

#include "Types.h"              //Forward declarated classes
#include "AttackField.h"
#include "DefenceField.h"

/*
    classe che gestisce un giocatore umano
*/
class Player {

    public:
        Player();
        Player(std::string name);

        /*
            metodo che restituisce il campo di attacco di un giocatore
        */
        AttackField& getAttackField();

        /*
            metodo che restituisce il vettori di navi di un giocatore
        */
        DefenceField& getDefenceField();  

        /*
            metodo che stampa a schermo il campo di difesa e di attacco di un giocatore.
            I campi vengono visualizzati affiancati
        */
        void printFields();

        /*
            metodo che risìchiede al giocatore di inserie l'azione che desidera compiere
        */
        void action(Player& p2, std::vector<std::string>& matchActions); 

    protected:
        AttackField  _af;
        DefenceField _df;

        std::string _name;
};

/*
    Helper function per verificare se esiste la nave che dovrebbe compiere l'azione.
    In caso affermativo compie l'azione della nave selezionata
*/
bool activateShipAction(std::string XYOrigin, std::string XYTarget, Player& p1, Player& p2);

#endif // PLAYER_H