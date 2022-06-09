#pragma once
#include "simulationobject.h"
#include "simulator.h"
#include <queue>
#include <string>

class CPassaport8Object : public CSimulationObject {
public:
    CPassaport8Object(CSimulator* simulator, int category, string id, string nom, int maxCua);
    ~CPassaport8Object() {}
    //Métode que el simulador us invocarà per a recollir els estadístics (print per consola)
    void showStatistics();
    //És una funció virtial pura així que us tocarà implementar-la indiferentment de si la invoqueu o no.
    bool AcceptEntity(CEntity* entity, CSimulationObject* emissor);
    //Processar un esdeveniment de simulació, funció pura que us toca implementar

    bool SendMeNow(CSimulationObject* tincEspai);

    void processEvent(CSimulationEvent* event);
    //Métode que el simulador invocarà a l'inici de la simulació, abans de que hi hagi cap esdeveniment a la llista d'esdeveniments
    void simulationStart();
    //Métode que el simulador us pot invocar a la finalització de l'estudi
    void simulationEnd();

protected:
    std::string _nom;

private:
    queue<CPassenger> EntryQueue;
    queue<CPassenger> ExitQueue;

    int MAX_CUA;

};

