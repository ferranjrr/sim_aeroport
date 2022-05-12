#include <iostream>
#include <list>
#include "simulationevent.h"
#include "entity.h"
#include "simulationobject.h"
#include "structs.h"
#include "string.h"

CSimulationEvent::CSimulationEvent(float time,CSimulationObject* provider,CSimulationObject* consumer,CEntity* entity,enumEventType eventType)
{//Inicialitzacions
  m_consumer=consumer;
  m_provider=provider;
  m_entity=entity;
  m_eventTime=time;
  m_eventType=eventType;
};

void CSimulationEvent::executed(){
  m_consumer->processEvent(this);
}


