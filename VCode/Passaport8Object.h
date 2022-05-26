#pragma once
#include "simulationobject.h"
#include "simulator.h"
#include <queue>

class Passaport8Object : public CSimulationObject {
public:
    Passaport8Object(CSimulator* simulator, std::string nom);
    ~Passaport8Object() {}
    //M�tode que el simulador us invocar� per a recollir els estad�stics (print per consola)
    void showStatistics();
    //�s una funci� virtial pura aix� que us tocar� implementar-la indiferentment de si la invoqueu o no.
    bool AcceptEntity(CEntity* entity, CSimulationObject* emissor);
    //Processar un esdeveniment de simulaci�, funci� pura que us toca implementar
    void processEvent(CSimulationEvent* event);
    //M�tode que el simulador invocar� a l'inici de la simulaci�, abans de que hi hagi cap esdeveniment a la llista d'esdeveniments
    void simulationStart();
    //M�tode que el simulador us pot invocar a la finalitzaci� de l'estudi
    void simulationEnd();

protected:
    queue<int> EntryQueue;
    queue<int> ExitQueue;
};