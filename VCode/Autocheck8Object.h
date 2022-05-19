#pragma once
#include "simulationobject.h"
#include "simulator.h"
#include <vector>
#include <queue>


class CAutocheck8Object :public CSimulationObject {

public:

    CAutocheck8Object(CSimulator* simulator, std::string nom);

    ~CAutocheck8Object() {}

    //Métode que el simulador us invocarà per a recollir els estadístics (print per consola)
    void showStatistics();

    //És una funció virtial pura així que us tocarà implementar-la indiferentment de si la invoqueu o no.
    bool AcceptEntity();

    //Processar un esdeveniment de simulació, funció pura que us toca implementar
    void processEvent(CSimulationEvent* event);

    //Métode que el simulador invocarà a l'inici de la simulació, abans de que hi hagi cap esdeveniment a la llista d'esdeveniments
    void simulationStart();

    //Métode que el simulador us pot invocar a la finalització de l'estudi
    void simulationEnd();

protected:

    // ATRIBUTS

    std::string _nom;


private:

    /* ATRIBUTS */

    // Struct amb l'identificador i l'estat d'un quiosc 
    struct quiosc {
        enumStateObject state;
        int timeToRepair;
    };
    // Array amb els quioscs de l'autocheckin (fa falta??)
    vector<quiosc> _nQuioscs;
    // Cua que tinc a l'autocheckin
    queue<CPassenger> cuaACheck;


    /* METODES */

    // Seguint una distribucio triangular retorna el temps que es trigara en reparar un quiosc Tri(15,180,120)
    double triTimeToRepair();

    // Donat un quiosc q, nomes començar el dia hi ha un 5% de possibilitats de que es trenqui.
    void breakQuioscIdle();

    // Donat un quiosc q en servei, quan esta en estat 'sSERVICE' hi ha un 1% de possibilitats de que es trenqui.
    void breakQuioscService();

    // Seguint una distribució triangular retorna el temps que trigara una persona en fer el Checkin
    double triTimeToChekin(bool baggage);

    // Donat el temps actual i el temps de sortida del vol retorna si el checkin esta disponible o no
    bool isAcheckinOpen();

};

