#pragma once
#include "simulationobject.h"


class CEntity;

enum enumEventType { ePUSH,eSERVICE};
        
class CSimulationEvent{
    public:
        CSimulationEvent(){};
        CSimulationEvent(float time,CSimulationObject* provider,CSimulationObject* consumer,CEntity* entity,enumEventType eventType);
        ~CSimulationEvent(){};
        float getTime(){return m_eventTime;};
        CSimulationObject* getProvider(){return m_provider;};
        CSimulationObject* getConsumer(){return m_consumer;};
        CEntity* getEntity(){return m_entity;};
        enumEventType getEventType();
        void executed();
        void isUnexpected();
    protected:
        CSimulationObject* m_provider;
        CSimulationObject* m_consumer;
        CEntity* m_entity;
        enumEventType m_eventType;
        float m_eventTime;
};


