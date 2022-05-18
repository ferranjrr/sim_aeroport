#include "Autocheck8Object.h"
#include "simulator.h"
#include "simulationobject.h"
#include "simulationevent.h"
#include "passenger.h"
#include <string>

using namespace std;

Autocheck8Object::Autocheck8Object(CSimulator* simulator, string nom) :CSimulationObject(simulator) {
	_nom = nom;
	_nQuioscs = vector<quiosc>(12);
}


bool Autocheck8Object::AcceptEntity() {
	return true;
};

void Autocheck8Object::showStatistics() {
	cout << _nom << " No tinc estadístics";
}

void Autocheck8Object::processEvent(CSimulationEvent* event) {
	// TODO: hacer cositas aqui
}

void Autocheck8Object::simulationStart() {
	// TODO: hacer cositas aqui
}

void Autocheck8Object::simulationEnd() {}


/* MIS COSITAS */

double Autocheck8Object::triTimeToRepair()
{
	return 0.0;
}

void Autocheck8Object::breakQuioscIdle()
{
}

void Autocheck8Object::breakQuioscService()
{
}

double Autocheck8Object::triTimeToChekin(bool baggage)
{
	return 0.0;
}

bool Autocheck8Object::isAcheckinOpen()
{
	return false;
}
