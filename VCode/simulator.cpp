#include "simulator.h"
#include "simulationevent.h"
#include "eventlist.h"
#include "montyobject.h"

CSimulator::CSimulator(){
    CMontyObject* mnty=new CMontyObject(this,"mnty");
    m_objectes.push_front(mnty);
    //Per simplicitat
    run();
}
CSimulator::~CSimulator(){
    //Eliminem objectes que formen part del model
    while (m_objectes.size()>0)
    {
        delete m_objectes.front();
        m_objectes.pop_front();
    }
    //Eliminem la llista d'esdeveniments
    m_eventList->reset();
    delete m_eventList;
}
void CSimulator::run(){
    simulationStart();
    int a=0;
    while (!simulationFinished() || a<4)
    {
        a=a+1;
        CSimulationEvent* event=(CSimulationEvent*)this->m_eventList->remove();
        m_currentTime=event->getTime();
        event->executed();
        delete event;
    }
}

void CSimulator::simulationStart()
{
    m_eventList=new CEventList();
    CMontyObject* mnty=(CMontyObject*) m_objectes.front();
    mnty->simulationStart();
}

bool CSimulator::simulationFinished(){
    //Executo 1200 unitats de temps com a mínim (no en feu cas d'això, que el temps es fixarà més endavant)
    return m_currentTime>1200 || m_eventList->isEmpty();
}

void CSimulator::losesFlight(CPassenger* pax){
    //Comprovar si és cert o no
}

void CSimulator::eventUnexpected(CSimulationEvent* event){
   //event->isUnexpected();
}

void CSimulator::scheduleEvent(CSimulationEvent* event){
    m_eventList->insert(event);
}

void CSimulator::PassengerOut(CPassenger *pax){
    delete pax;
}

std::list<struct__route> CSimulator::nextObject(CPassenger* entitat, CSimulationObject* objecte){
    std::list<struct__route> retorn;
    CMontyObject* mnty=(CMontyObject*) m_objectes.front();
    
    retorn.push_front(struct__route(mnty,23));
    
    return retorn;
}

float CSimulator::timeTo(CSimulationObject* desti,CPassenger* pax){
    //temporal a l'espera de tenir la matriu O/D
    return 50;
}
