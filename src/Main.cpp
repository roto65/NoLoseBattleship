// Autore: Francesco Ariani (2041835)

#include <string>
#include <iostream>
#include <vector>

#include "Main.h"
#include "FilesIO.h"
#include "Player.h"
#include "Computer.h"

/*
    enum per poter fare lo switch sulle varie modalita' di gioco:
    pc = player vs computer
    cc = computer vs computer
    pp = player vs player
*/
enum Arguments {
    invalidArgument, pc, cc, pp
};

Arguments resolveArgument(std::string input) {
    if (input == "pc") return pc;
    if (input == "cc") return cc;
    if (input == "pp") return pp;

    return invalidArgument;
}

/*
    tiene conto delle azioni per il replay
*/
std::vector<std::string> matchActions;

int main(int argc, char* argv[]) {
    
    if (argc < 2) {                 //controllo che venga inserita la modaita' di gioco
        std::cout << "Non e' stata inserito l'argomento che specifica la modalita' di gioco!\n";
        return 0;
    }

    std::string argument = argv[1];
    
    Player p1 ("Giocatore 1"), p2 ("Giocatore 2");
    Computer c1 ("Computer 1"), c2 ("Computer 2");

    switch (resolveArgument(argument)) {
        case pc:                    //player vs computer
            p1.insertAllShips(matchActions);
            c1.insertAllShips(matchActions);
            gameLoop(p1,c1,matchActions);
            break;
        case cc:                    //computer vs computer
            c1.insertAllShips(matchActions);
            c2.insertAllShips(matchActions);
            gameLoop(c1,c2,matchActions);
            break;
        case pp:                    //player vs player
            p1.insertAllShips(matchActions);
            p2.insertAllShips(matchActions);
            gameLoop(p1,p2,matchActions);
            break;
        default:                    //viene inserita una modalita' di gioco non in elenco 
            std::cout << "Inserire:\n"
                << "- \"pc\" se si vuole eseguire una partita player vs computer\n" 
                << "- \"cc\" se si vuole eseguire una partita computer vs computer" << std::endl;
            return 0;
            break;
    }

    FilesIO::exportLog(matchActions);        //scrittura del log della partita
    return 0;
}

bool endGame (Player p1, Player p2, int round) {
    const int MAX_TURN = 104;
    if (p1.getDefenceField().getShipCount() == 0 && p2.getDefenceField().getShipCount() == 0) {
        std::cout << "Nuke sganciata: tutte le navi sono state distrutte!" << std::endl;
        matchActions.push_back("PP 00");
        return false;
    }
    if (p1.getDefenceField().getShipCount() == 0) {
        std::cout << "Vittoria per il giocatore 2!" << std::endl;
        matchActions.push_back("PP 02");
        return false;
    }
    if (p2.getDefenceField().getShipCount() == 0) {
        std::cout << "Vittoria per il giocatore 1!" << std::endl;
        matchActions.push_back("PP 01");
        return false;
    }
    if (round > MAX_TURN) {
        std::cout << "Limite massimo di turni raggiunto: partita terminata in pareggio" << std::endl;
        matchActions.push_back("PP 104");
        return false;
    }
    return true;
}