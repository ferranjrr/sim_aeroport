#include "Passaport8Object.h"
#include "simulator.h"
#include "simulationobject.h"
#include "simulationevent.h"
#include "passenger.h"
#include <string>

using namespace std;

CPassaport8Object::CPassaport8Object(CSimulator* simulator, int category, string id, string nom, int maxCua):CSimulationObject(simulator, category, id, nom)
{
    EntryQueue = queue<CPassenger>();
    ExitQueue = queue<CPassenger>();
    MAX_CUA = maxCua;
    _nom = nom;
}

//�s una funci� virtial pura aix� que us tocar� implementar-la indiferentment de si la invoqueu o no.
bool CPassaport8Object::AcceptEntity(CEntity* entity, CSimulationObject* emissor) {
    //if (emissor.get)
    return EntryQueue.size() < MAX_CUA;
};

//M�tode que el simulador us invocar� per a recollir els estad�stics (print per consola)
void CPassaport8Object::showStatistics() {
    cout << "S�c el control de passaport " << _nom << "i la meva MAX_CUA �s de " << MAX_CUA << endl;
};

bool CPassaport8Object::SendMeNow(CSimulationObject* tincEspai) {
    if (ExitQueue.size() <= MAX_CUA) return true;
    else return false;
}

//Processar un esdeveniment de simulaci�, funci� pura que us toca implementar
void CPassaport8Object::processEvent(CSimulationEvent* event) {
    
}

//M�tode que el simulador invocar� a l'inici de la simulaci�, abans de que hi hagi cap esdeveniment a la llista d'esdeveniments
void CPassaport8Object::simulationStart() {
    setState(IDLE);
    EntryQueue = queue<CPassenger>();
    ExitQueue = queue<CPassenger>();
}
//M�tode que el simulador us pot invocar a la finalitzaci� de l'estudi
void CPassaport8Object::simulationEnd() {

}