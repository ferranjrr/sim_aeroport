#include "Autocheck8Object.h"
#include "simulator.h"
#include "simulationobject.h"
#include "simulationevent.h"
#include "passenger.h"
#include <string>

using namespace std;

CAutocheck8Object::CAutocheck8Object(CSimulator* simulator, string nom) :CSimulationObject(simulator) {
	_nom = nom;
	_nQuioscs = vector<quiosc>(12);
}


bool CAutocheck8Object::AcceptEntity() {
	return true;
};

void CAutocheck8Object::showStatistics() {
	cout << _nom << " No tinc estadístics";
}

void CAutocheck8Object::processEvent(CSimulationEvent* event) {
	// TODO: hacer cositas aqui
}

void CAutocheck8Object::simulationStart() {
	// TODO: hacer cositas aqui
}

void CAutocheck8Object::simulationEnd() {}


/* MIS COSITAS */

double CAutocheck8Object::triTimeToRepair()
{
	return 0.0;
}

void CAutocheck8Object::breakQuioscIdle()
{
}

void CAutocheck8Object::breakQuioscService()
{
}

double CAutocheck8Object::triTimeToChekin(bool baggage)
{
	return 0.0;
}

bool CAutocheck8Object::isAcheckinOpen()
{
	return false;
}
