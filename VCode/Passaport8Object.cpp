#include "Passaport8Object.h"
#include "simulator.h"
#include "simulationobject.h"
#include "simulationevent.h"
#include "passenger.h"
#include <string>
#include <iostream>

using namespace std;

CPassaport8Object::CPassaport8Object(CSimulator* simulator, int category, int id, string nom, int minutsDelay) :CSimulationObject(simulator, category, id, nom)
{
    WaitingQueue = queue<CSimulationObject*>();
    ExitQueue = queue<CPassenger*>();
    _nom = nom;
    DELAY = minutsDelay;
    RestauracioCounter = 0;
    SortidaCounter = 0;
}

//És una funció virtial pura així que us tocarà implementar-la indiferentment de si la invoqueu o no.
bool CPassaport8Object::AcceptEntity(CSimulationObject* emissor) {

    CEntity* entity = emissor->getCurrentEntity();

    if (dynamic_cast<CPassenger*>(entity) == nullptr) return false; //No és un passatger

    if (emissor->getCategory() != 7 || emissor->getCategory() != 8) return false; //No és l'objecte esperat.

    if (dynamic_cast<CPassenger*>(entity)->isSchengen() ||
        dynamic_cast<CPassenger*>(entity)->HaslostFlight() ||
        !dynamic_cast<CPassenger*>(entity)->takeFlight()) return false;
    if (getState() == IDLE) return true;
    else {
        WaitingQueue.push(emissor);
        return false;
    }
};

//Métode que el simulador us invocarà per a recollir els estadístics (print per consola)
void CPassaport8Object::showStatistics() {
    cout << endl;
    cout << "Soc l'objecte " << _nom << ":" << endl;
    cout << "   Els passatgers estan " << DELAY << " minuts en el control de passaport." << endl;
    cout << "   Han passat " << RestauracioCounter + SortidaCounter << " passatgers." << endl;
    cout << "   " << RestauracioCounter << " passatgers s'han enviat a restauracio." << endl;
    cout << "   " << SortidaCounter << " passatgers s'han enviat a la sortida." << endl << endl;
};

bool CPassaport8Object::SendMeNow(CSimulationObject* tincEspai) {
    if ((tincEspai->getCategory() != 15 && tincEspai->getCategory() != 13) || ExitQueue.empty()) return false;
    else {
        float tempsEvent;
        tempsEvent = m_Simulator->timeTo(tincEspai, (CPassenger*)tincEspai->getCurrentEntity()) + m_Simulator->time();

        CPassenger* p = ExitQueue.front();
        CSimulationEvent* eventService = new CSimulationEvent(tempsEvent, this, tincEspai, p, ePUSH);
        m_Simulator->scheduleEvent(eventService);

        ExitQueue.pop();
        return true;
    }
}

//Processar un esdeveniment de simulació, funció pura que us toca implementar
void CPassaport8Object::processEvent(CSimulationEvent* event) {
    if (event->getEventType() == ePUSH) {
        setCurrentEntity(event->getEntity());

        float tempsEvent = DELAY + event->getTime();
        CSimulationEvent* eventPush = new CSimulationEvent(tempsEvent, this, this, event->getEntity(), eSERVICE);
        m_Simulator->scheduleEvent(eventPush);
        setState(BUSY);
    }

    if (event->getEventType() == eSERVICE) {
        if (m_category > 0)
        {
            /* Per evitar crear nous punters a objectes que encara no sé la seva capcelera, el temps que triguen els passatgers 
            a moures d'un lloc a un altre s'ha calculat a mà, tot observant què feia la funció timeTo de simulator.cpp*/

            float tempsPassaport2Sortida = 135; //abs(15 - 10*15)
            float tempsPassaport2Restauracio = 137; //abs(13 - 10*15)
            float tempsRestauracio2Sortida = 180; //abs(15 - 13*15)
            float tempsPassaport2Restauracio2Sortida = tempsPassaport2Restauracio + tempsRestauracio2Sortida; //317
            float tempsSortidaVol = ((CPassenger*)event->getEntity())->getDepartureTime() - m_Simulator->time();

            //Els mostradors obren 40 minuts abans. Per tant, si es tan oberts, els passatgers ja poden anar tirant cap a la Sortida.

            if ((tempsSortidaVol < 40 + tempsPassaport2Sortida) || (tempsSortidaVol < 40 + tempsPassaport2Restauracio2Sortida)) {
            //Queden menys de 40 minuts perque surti el vol (contant també el temps de desplaçament entre Passaport i Sortida)
            //Cap a Sortida. Si cap me l'accepta, llavors cap a la cua de sortida, esperant a rebre un SendMeNow.
                if (!to_Sortida(event)) ExitQueue.push((CPassenger*)event->getEntity());
            }
            else {
                //Queden més de 40 minuts perque surti el vol (contant els temps de desplaçament entre Passaport, Restauració i Sortida)
                //Cap a Restauració. Si cap me l'accepta, llavors cap a Sortida. Si tampoc és acceptat, llavors cap a la cua de sortida, esperant a rebre un SendMeNow.
                if (!to_Restauracio(event) && !to_Sortida(event)) ExitQueue.push((CPassenger*)event->getEntity());
            }

            setState(IDLE);

            if (!WaitingQueue.empty()) {
                while (!WaitingQueue.front()->SendMeNow(this)) WaitingQueue.pop();
            }
        }
    }
}

bool CPassaport8Object::to_Sortida(CSimulationEvent* event) {

    std::list<struct__route> destins;
    destins = m_Simulator->nextObject(event->getEntity(), this);

    CSimulationEvent* eventService;

    for (struct__route d : destins) {
        if (d.destination->getCategory() == 15)
        {
            if (d.destination->AcceptEntity(this)) {
                float tempsEvent = d.time + m_Simulator->time();
                eventService = new CSimulationEvent(tempsEvent, this, d.destination, event->getEntity(), ePUSH);
                m_Simulator->scheduleEvent(eventService);
                
                ++SortidaCounter;
                return true;
            }
        }
    }
    return false;
}

bool CPassaport8Object::to_Restauracio(CSimulationEvent* event) {

    std::list<struct__route> destins;
    destins = m_Simulator->nextObject(event->getEntity(), this);

    CSimulationEvent* eventService;

    for (struct__route d : destins) {
        if (d.destination->getCategory() == 13)
        {
            if (d.destination->AcceptEntity(this)) {
                float tempsEvent = d.time + m_Simulator->time();
                eventService = new CSimulationEvent(tempsEvent, this, d.destination, event->getEntity(), ePUSH);
                m_Simulator->scheduleEvent(eventService);

                ++RestauracioCounter;
                return true;
            }
        }
    }
    return false;
}


//Métode que el simulador invocarà a l'inici de la simulació, abans de que hi hagi cap esdeveniment a la llista d'esdeveniments
void CPassaport8Object::simulationStart() {
    setState(IDLE);
    WaitingQueue = queue<CSimulationObject*>();
    ExitQueue = queue<CPassenger*>();
    RestauracioCounter = 0;
    SortidaCounter = 0;
}
//Métode que el simulador us pot invocar a la finalització de l'estudi
void CPassaport8Object::simulationEnd() {
    setState(IDLE);
}
