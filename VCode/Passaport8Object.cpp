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
    WaitingQueue = queue<CPassenger*>();
    ExitQueue = queue<CPassenger*>();
    _nom = nom;
    DELAY = minutsDelay;
}

//És una funció virtial pura així que us tocarà implementar-la indiferentment de si la invoqueu o no.
bool CPassaport8Object::AcceptEntity(CSimulationObject* emissor) {

    CEntity* entity = emissor->getCurrentEntity();

    if (dynamic_cast<CPassenger*>(entity) == nullptr) return false; //No és un passatger

    if (dynamic_cast<CCinta2Object*>(emissor) == nullptr ||
        dynamic_cast<CCinta4Object*>(emissor) == nullptr ||
        dynamic_cast<CCinta12Object*>(emissor) == nullptr ||
        dynamic_cast<CElevador7Object*>(emissor) == nullptr ||
        dynamic_cast<CElevador10Object*>(emissor) == nullptr ||
        dynamic_cast<CElevador11Object*>(emissor) == nullptr ||
        dynamic_cast<CElevador17Object*>(emissor) == nullptr ||
        dynamic_cast<CElevador18Object*>(emissor) == nullptr ||
        dynamic_cast<CElevador19Object*>(emissor) == nullptr) return false; //No és l'objecte esperat.

    if (dynamic_cast<CPassenger*>(entity)->isSchengen() ||
        dynamic_cast<CPassenger*>(entity)->HaslostFlight() ||
        not dynamic_cast<CPassenger*>(entity)->takeFlight()) return false;
    if (getState() == IDLE) return true;
    else {
        WaitingQueue.push(dynamic_cast<CPassenger*>(entity));
        return false;
    }
};

//Métode que el simulador us invocarà per a recollir els estadístics (print per consola)
void CPassaport8Object::showStatistics() {
    cout << "Sóc en el control de passaport " << _nom << " i estic " << DELAY << " a la cua " << endl;
};

bool CPassaport8Object::SendMeNow(CSimulationObject* tincEspai) {
    if (ExitQueue.empty()) return false;
    else {
        float tempsEvent;
        if (tincEspai->getCategory() == 13)  tempsEvent = 13 /*Retocar*/ + m_Simulator->time();
        else if (tincEspai->getCategory() == 15) tempsEvent = 15 /*Retocar*/ + m_Simulator->time();
        else return false;

        CPassenger* p = ExitQueue.back();
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
            if (((CPassenger*)event->getEntity())->getDepartureTime() - m_Simulator->time() - 13 - 15 < 40 + 15) {
            //Queden menys de 40 minuts perque surti el vol (contant els 15 minuts per arribar a sortida)
            //Cap a Sortida
                if (!to_Sortida(event) && !to_Restauracio(event)) ExitQueue.push((CPassenger*)event->getEntity());
            }
            else {
                //Queden més de 40 minuts perque surti el vol (contant els 13 minuts que estriguen a anar a Restauració + 15 des de Restauració a Sortida)
                //Cap a Restauració

                if (!to_Restauracio(event) && !to_Sortida(event)) ExitQueue.push((CPassenger*)event->getEntity());
            }
        }
    }
}

bool CPassaport8Object::to_Sortida(CSimulationEvent* event) {

    std::list<struct__route> destins;
    destins = m_Simulator->nextObject(event->getEntity(), this);

    CSimulationEvent* eventService;

    for (struct__route d : destins) {
        if (dynamic_cast<CSortida2Object*>(d.destination) != nullptr ||
            dynamic_cast<CSortida15Object*>(d.destination) != nullptr ||
            dynamic_cast<CSortida17Object*>(d.destination) != nullptr)
        {
            if (d.destination->AcceptEntity(this)) {
                float tempsEvent = d.time + m_Simulator->time();
                eventService = new CSimulationEvent(tempsEvent, this, d.destination, event->getEntity(), ePUSH);
                m_Simulator->scheduleEvent(eventService);
                setState(IDLE);
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
        if (dynamic_cast<CRestauracio1Object*>(d.destination) != nullptr ||
            dynamic_cast<CRestauracio4Object*>(d.destination) != nullptr ||
            dynamic_cast<CRestauracio6Object*>(d.destination) != nullptr ||
            dynamic_cast<CRestauracio10Object*>(d.destination) != nullptr ||
            dynamic_cast<CRestauracio18Object*>(d.destination) != nullptr)
        {
            if (d.destination->AcceptEntity(this)) {
                float tempsEvent = d.time + m_Simulator->time();
                eventService = new CSimulationEvent(tempsEvent, this, d.destination, event->getEntity(), ePUSH);
                m_Simulator->scheduleEvent(eventService);
                setState(IDLE);
                return true;
            }
        }
    }
    return false;
}


//Métode que el simulador invocarà a l'inici de la simulació, abans de que hi hagi cap esdeveniment a la llista d'esdeveniments
void CPassaport8Object::simulationStart() {
    setState(IDLE);
    WaitingQueue = queue<CPassenger*>();
    ExitQueue = queue<CPassenger*>();
}
//Métode que el simulador us pot invocar a la finalització de l'estudi
void CPassaport8Object::simulationEnd() {
    setState(IDLE);
}
