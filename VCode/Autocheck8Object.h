#pragma once
#include "simulationobject.h"
#include "simulator.h"
#include <vector>
#include <queue>


class CAutocheck8Object :public CSimulationObject {

public:

    CAutocheck8Object(CSimulator* simulator, std::string nom);

    ~CAutocheck8Object() {}

    //M�tode que el simulador us invocar� per a recollir els estad�stics (print per consola)
    void showStatistics();

    //�s una funci� virtial pura aix� que us tocar� implementar-la indiferentment de si la invoqueu o no.
    bool AcceptEntity();

    //Processar un esdeveniment de simulaci�, funci� pura que us toca implementar
    void processEvent(CSimulationEvent* event);

    //M�tode que el simulador invocar� a l'inici de la simulaci�, abans de que hi hagi cap esdeveniment a la llista d'esdeveniments
    void simulationStart();

    //M�tode que el simulador us pot invocar a la finalitzaci� de l'estudi
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

    // Donat un quiosc q, nomes comen�ar el dia hi ha un 5% de possibilitats de que es trenqui.
    void breakQuioscIdle();

    // Donat un quiosc q en servei, quan esta en estat 'sSERVICE' hi ha un 1% de possibilitats de que es trenqui.
    void breakQuioscService();

    // Seguint una distribuci� triangular retorna el temps que trigara una persona en fer el Checkin
    double triTimeToChekin(bool baggage);

    // Donat el temps actual i el temps de sortida del vol retorna si el checkin esta disponible o no
    bool isAcheckinOpen();

};

