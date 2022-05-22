#include "Passaport8Object.h"
#include "simulator.h"
#include "simulationobject.h"
#include "simulationevent.h"
#include "passenger.h"
#include <string>

using namespace std;

Passaport8Object::Passaport8Object(CSimulator* simulator, string nom) :CSimulationObject(simulator)
{
    //EntryQueue = queue<int>();
    //ExitQueue = queue<int>();
}

//�s una funci� virtial pura aix� que us tocar� implementar-la indiferentment de si la invoqueu o no.
bool Passaport8Object::AcceptEntity(CEntity* entity, CSimulationObject* emissor) {

};

//M�tode que el simulador us invocar� per a recollir els estad�stics (print per consola)
void Passaport8Object::showStatistics() {

};

//Processar un esdeveniment de simulaci�, funci� pura que us toca implementar
void Passaport8Object::processEvent(CSimulationEvent* event) {
    
}

//M�tode que el simulador invocar� a l'inici de la simulaci�, abans de que hi hagi cap esdeveniment a la llista d'esdeveniments
void Passaport8Object::simulationStart() {
    setState(sIDLE);
    //EntryQueue = queue<int>();
    //ExitQueue = queue<int>();
}
//M�tode que el simulador us pot invocar a la finalitzaci� de l'estudi
void Passaport8Object::simulationEnd() {

}