#include "Passaport8Object.h"
#include "simulator.h"
#include "simulationobject.h"
#include "simulationevent.h"
#include "passenger.h"
#include <string>

using namespace std;

CPassaport8Object::CPassaport8Object(CSimulator* simulator, int category, int id, string nom, int minutsDelay) :CSimulationObject(simulator, category, id, nom)
{
    WaitingQueue = queue<CPassenger*>();
    ExitQueue = queue<CPassenger*>();
    _nom = nom;
    DELAY = minutsDelay;
}

//�s una funci� virtial pura aix� que us tocar� implementar-la indiferentment de si la invoqueu o no.
bool CPassaport8Object::AcceptEntity(CEntity* entity, CSimulationObject* emissor) {
    if (dynamic_cast<CPassenger*>(entity) == nullptr) return false; //No �s un passatger

    if (dynamic_cast<CCinta2Object*>(emissor) == nullptr or
        dynamic_cast<CCinta4Object*>(emissor) == nullptr or
        dynamic_cast<CCinta12Object*>(emissor) == nullptr or
        dynamic_cast<CElevador7Object*>(emissor) == nullptr or
        dynamic_cast<CElevador10Object*>(emissor) == nullptr or
        dynamic_cast<CElevador11Object*>(emissor) == nullptr or
        dynamic_cast<CElevador17Object*>(emissor) == nullptr or
        dynamic_cast<CElevador18Object*>(emissor) == nullptr or
        dynamic_cast<CElevador19Object*>(emissor) == nullptr) return false; //No �s l'objecte esperat.

    if (dynamic_cast<CPassenger*>(entity)->isSchengen() or 
        dynamic_cast<CPassenger*>(entity)->HaslostFlight()) return false;
    if (getState() == IDLE) return true;
    else {
        WaitingQueue.push(dynamic_cast<CPassenger*>(entity));
        return false;
    }
};

//M�tode que el simulador us invocar� per a recollir els estad�stics (print per consola)
void CPassaport8Object::showStatistics() {
    cout << "S�c en el control de passaport " << _nom << "i estic " << DELAY << " a la cua " << endl;
};

bool CPassaport8Object::SendMeNow(CSimulationObject* tincEspai) {
   
}

//Processar un esdeveniment de simulaci�, funci� pura que us toca implementar
void CPassaport8Object::processEvent(CSimulationEvent* event) {
    setCurrentEntity(event->getEntity());

    CSimulationEvent* eventPush = new CSimulationEvent(DELAY, this, this, event->getEntity(), eSERVICE);
    m_Simulator->scheduleEvent(eventPush);

    if (event->getEntity())

}

//M�tode que el simulador invocar� a l'inici de la simulaci�, abans de que hi hagi cap esdeveniment a la llista d'esdeveniments
void CPassaport8Object::simulationStart() {
    setState(IDLE);
    WaitingQueue = queue<CPassenger*>();
    ExitQueue = queue<CPassenger*>();
}
//M�tode que el simulador us pot invocar a la finalitzaci� de l'estudi
void CPassaport8Object::simulationEnd() {
    setState(IDLE);
}
