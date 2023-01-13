Battaglia Navale

Descrizione del progetto

Programma in C++ che implementa una versione avanzata del gioco Battaglia Navale. 

--------------------------------------------------------------------------

Contenuto della cartella log

Il file di log di ogni partita viene salvato all'interno della cartella log.

La cartella contiene:
 - log_cc.txt

   File di log risultato di una partita computer vs. computer

 - log_pc.txt

   File di log risultato di una partita giocatore vs. computer

 - log_replay.txt

    File generato eseguendo il replay della partita contenuta in log_pc.txt

 - log.txt 

   File di log dell'ulitma parita svolta dal programma, viene aggiornato in seguito a ciascuna esecuzione

[Attenzione!]

Il file di log contiene soltanto dati fondamentali per l'esecuzione del replay. Non sono contenuti i
 comandi speciali con funzionalita' puramente estetica.

--------------------------------------------------------------------------

Eseguibili e argomenti a linea di comando

Eseguibili:
 - battaglia_navale
 - replay

Argomenti di battaglia_navale:
 - pc
   
      Viene avviata una partita giocatore vs. computer

 - cc

      Viene avviata una partita computer vs. computer

 - pp

      [Experimental] Viene avviata una partita giocatore vs. giocatore

      Modalita' consigliata soltanto per fini di testing

Argomenti di replay:
 - v

      l'eseguibile replay stampa a video i campi del giocatore attivo per ogni turno della partita di
       cui viene effettuato il replay

    - input path

        percorso del file di log di cui effettuare il replay

 - f

      l'eseguibile replay stampa su file i campi del giocatore attivo per ogni turno della partita di
       cui viene effettuato il replay

    - input path

        percorso del file di log di cui effettuare il replay

    - output path

        percorso del file in cui viene salvato il replay

[Attenzione!] 

Tutti i percorsi sono da considerarsi relativi rispetto all'eseguibile replay. Specificare sempre
 l'estensione dei file di cui si inserisce il percorso

--------------------------------------------------------------------------

Comandi speciali

Durante una partita un giocatore puo' decidere di utilizzare i comandi speciali sotto elencati senza perdere il turno:

 - AA AA
 
   rimuove tutte le rilevazioni sonar dal campo di attacco
 
 - BB BB
 
   rimuove tutti i colpi andati a segno dal campo di attacco
 
 - CC CC
 
   rimuove tutti i colpi andati a vuoto dal campo di attacco
 
 - HH HH
 
   fornisce la lista di tutte le azioni speciali compibili
 
 - XX XX
 
   stampa le griglie di attacco e difesa del giocatore corrente

E' stato implementato anche il comando speciale NN NN che finisce immediatamente la partita in pareggio
 lanciando una bomba nucleare (nuke) sul campo di difesa di ciascun giocatore

--------------------------------------------------------------------------

Comandi utili

Compilazione

Questo progetto utilizza CMake per compilare il codice contenuto. Per configurare il progetto CMake e
 generare i file necessari per il build (specifici per l'ambiente in uso) entrare nella cartella del
 progetto tramite terminale ed eseguire: 

cmake .

Successivamente per eseguire il build del progetto eseguire il comando: 

cmake --build .

oppure il comando:

make

Esecuzione

Per avviare gli eseguibili generati sono consigliati i seguenti comandi:

 - ./battaglia_navale pc
 - ./replay v log/log.txt
 - ./replay f log/log_pc.txt log/log_replay.txt

Inserimento delle navi

Per inserire le navi piu' rapidamente nel proprio campo di difesa e' possibile incollare nel terminale
 la seguente combinazione:

A1 A5 B1 B5 C1 C5 D1 D3 E1 E3 F1 F3 H1 H2

E' possibile utilizzare un comando simile soltanto durante l'inserimento della prima corazzata poiche'
 esso contiene i valori richiesti per l'inserimento di tutte le 8 navi presenti in un campo di difesa

--------------------------------------------------------------------------

Autori

Questo progetto e' stato realizzato da:

| Nome                | Matricola |
| ------------------- | --------- |
| Francesco Ariani    | 2041835   |
| Simone Pietrogrande | 2032448   |
| Alessandro Rotondo  | 2032447   |

Questo progetto e' interamente disponibile su GitHub nella pagina https://github.com/roto65/NoLoseBattleship