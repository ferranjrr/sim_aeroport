#pragma once

#include "simulationobject.h"

//Estructures i altres cosses
struct struct__route{
    CSimulationObject* destination;
    float time;
    struct__route(CSimulationObject* desti, float temps){
        destination=desti;
        time=temps;
    }
};
