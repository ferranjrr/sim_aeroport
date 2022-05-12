#include "montyobject.h"
#include "simulator.h"
#include "simulationobject.h"
#include "simulationevent.h"
#include "passenger.h"
#include <string>

using namespace std;

CMontyObject::CMontyObject(CSimulator* simulator,string nom):CSimulationObject(simulator)
{
    m_nom=nom;
}

//És una funció virtial pura així que us tocarà implementar-la indiferentment de si la invoqueu o no.
bool CMontyObject::AcceptEntity()  {
    return true;
};

//Métode que el simulador us invocarà per a recollir els estadístics (print per consola)
void CMontyObject::showStatistics()  {
    cout << m_nom <<  " No tinc estadístics";
};
    
//Processar un esdeveniment de simulació, funció pura que us toca implementar
void CMontyObject::processEvent (CSimulationEvent* event)  {
    float tempsevent=std::rand() % 30 + 1;
    m_Simulator->scheduleEvent(new CSimulationEvent(tempsevent+m_Simulator->time(),this,this,event->getEntity(),eSERVICE));
    std::cout << m_Simulator->time() << " executo un event de servei \n";
}

//Métode que el simulador invocarà a l'inici de la simulació, abans de que hi hagi cap esdeveniment a la llista d'esdeveniments
void CMontyObject::simulationStart()  {
    setState(sIDLE);
    CPassenger* pax=new CPassenger(0);
    m_Simulator->scheduleEvent(new CSimulationEvent(20.0f,this,this,pax,eSERVICE));
}
//Métode que el simulador us pot invocar a la finalització de l'estudi
void CMontyObject::simulationEnd()  {

}