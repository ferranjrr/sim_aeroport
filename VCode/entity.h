#pragma once

class CSimulationObject;
class CSimulationEvent;
class CEntity
{
public:
    int staticId;
    float m_creationTime;
    float m_departureTime;
    CEntity(){}
    //registra de quan l'entitat entra en el sistema
    CEntity(float currentTime){
        //Aquí aniria bé tenir un singleton o una variable statica ...
        idUnic=1;
        m_creationTime=currentTime;
    }
    virtual ~CEntity(){}
    //registra de quan l'entitat surt del sistema
    void departureTime(float currentTime){
        m_departureTime=currentTime;
    }
    //recuperar el temps de vida
    float getlifeTime(){
        return m_departureTime-m_creationTime;
    }
    //recuperar identificador únic
    int getId(){
        return idUnic;
    }
private:
    //Recupera la posició on es troba l'entitat
    CSimulationObject* getPlace(){
      return m_objectPlace;
    }
    //Actualitza la posició on es troba l'entitat
    void setPlace(CSimulationObject* receptor){
      m_objectPlace=receptor;
    }
    //Actualitza la traça d'esdeveniments on aquesta entitat s'ha vist implicat
    void traceEvent(CSimulationEvent* event);   
    //Identificador únic de l'entitat 
    int idUnic;
    //Element de simulació on es troba l'entitat
    CSimulationObject* m_objectPlace;
};

