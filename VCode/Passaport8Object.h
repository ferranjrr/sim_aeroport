#pragma once
#include "simulationobject.h"
#include "simulator.h"
#include <queue>
#include <string>

class CPassaport8Object : public CSimulationObject {
public:
    CPassaport8Object(CSimulator* simulator, int category, string id, string nom, int maxCua);
    ~CPassaport8Object() {}
    //M�tode que el simulador us invocar� per a recollir els estad�stics (print per consola)
    void showStatistics();
    //�s una funci� virtial pura aix� que us tocar� implementar-la indiferentment de si la invoqueu o no.
    bool AcceptEntity(CEntity* entity, CSimulationObject* emissor);
    //Processar un esdeveniment de simulaci�, funci� pura que us toca implementar

    bool SendMeNow(CSimulationObject* tincEspai);

    void processEvent(CSimulationEvent* event);
    //M�tode que el simulador invocar� a l'inici de la simulaci�, abans de que hi hagi cap esdeveniment a la llista d'esdeveniments
    void simulationStart();
    //M�tode que el simulador us pot invocar a la finalitzaci� de l'estudi
    void simulationEnd();

protected:
    std::string _nom;

private:
    queue<CPassenger> EntryQueue;
    queue<CPassenger> ExitQueue;

    int MAX_CUA;

};

