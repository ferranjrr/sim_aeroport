#include "Passaport8Object.h"
#include "simulator.h"
#include "simulationobject.h"
#include "simulationevent.h"
#include "passenger.h"
#include <string>

using namespace std;

Passaport8Object::Passaport8Object(CSimulator* simulator, string nom) :CSimulationObject(simulator)
{

}

//És una funció virtial pura així que us tocarà implementar-la indiferentment de si la invoqueu o no.
bool Passaport8Object::AcceptEntity() {

};

//Métode que el simulador us invocarà per a recollir els estadístics (print per consola)
void Passaport8Object::showStatistics() {

};

//Processar un esdeveniment de simulació, funció pura que us toca implementar
void Passaport8Object::processEvent(CSimulationEvent* event) {

}

//Métode que el simulador invocarà a l'inici de la simulació, abans de que hi hagi cap esdeveniment a la llista d'esdeveniments
void Passaport8Object::simulationStart() {
    setState(sIDLE);
}
//Métode que el simulador us pot invocar a la finalització de l'estudi
void Passaport8Object::simulationEnd() {

}