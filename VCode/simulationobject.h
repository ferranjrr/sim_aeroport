#pragma once

#include <iostream>
#include <list>
#include "entity.h"
#include "structs.h"

class CSimulator;

enum enumStateObject { sIDLE,sSERVICE,sOUTOFSERVICE,sREPAIR};

class CSimulationObject{    
    public:
        CSimulationObject(){};
        //Constructora base
        CSimulationObject(CSimulator* simulator){
          m_Simulator=simulator;
        };
        //Destructor de l'objecte
        virtual ~CSimulationObject(){};
        //Métode que el simulador us invocarà per a recollir els estadístics (print per consola)
        virtual void showStatistics()=0;
        //És una funció virtial pura així que us tocarà implementar-la indiferentment de si la invoqueu o no.
        virtual bool AcceptEntity()=0;
        //Retorna l'estat actual de l'objecte
        enumStateObject getState(){return m_state;};
        //Processar un esdeveniment de simulació, funció pura que us toca implementar
        virtual void processEvent (CSimulationEvent* event)=0;
        //Métode que el simulador invocarà a l'inici de la simulació, abans de que hi hagi cap esdeveniment a la llista d'esdeveniments
        virtual void simulationStart()=0;
        //Métode que el simulador us pot invocar a la finalització de l'estudi
        virtual void simulationEnd()=0;
    protected:
        //Estableix l'estat de l'objecte
        void setState(enumStateObject estat){m_state=estat;};
        //Estat de simulació en el que es troba l'objecte
        enumStateObject m_state;
        //Punter al simulador
        CSimulator* m_Simulator;
};


