#pragma once
#include <iostream>
#include <list>

#include "passenger.h"
#include "simulationobject.h"
#include "simulationevent.h"
#include "structs.h"

class CEventList;
class CSimulator{
    public:
      //Crearà el model i ho gestionarà tot
      CSimulator();
      //Destroeix el model
      ~CSimulator();
      //Retorna el temps de simulació actual
      float time(){return m_currentTime;};
      //El passatger no arribarà a temps a la porta d'embarcament
      void losesFlight(CPassenger* pax);
      //Un objecte es queixa de rebre un event que no esperava
      void eventUnexpected(CSimulationEvent* event);
      //Retorna el temps per arribar a un objecte des de la posició actual
      float timeTo(CSimulationObject* desti,CPassenger* pax);
      //Programa un esdeveniment de simulació
      void scheduleEvent(CSimulationEvent* event);
      //Un passatger abandoa l'aeroport -volant o amb SP-
      void PassengerOut(CPassenger* pax);
      //Retorna una llista de tuples de possibles destins i temps per arribar
      std::list<struct__route> nextObject(CPassenger* entitat, CSimulationObject* objecte);
    protected:
      //Mostrarà els estadístics dels elements de simulació, farà una crida a tots els elements de simulació
      void showEstadistics();
      //Executar la simulació
      void run();
      //Comprovació de final de simulació
      bool simulationFinished();
      //Inicialització de la simulació
      void simulationStart();
      //Fi de la simulació
      void simulationEnd();
      //Llista ordenada d'esdeveniments de simulació
      CEventList* m_eventList;
      //Llista dels objectes de simulació que composen el model
      std::list<CSimulationObject*> m_objectes; 
      //Temps de simulació
      float m_currentTime;
};

