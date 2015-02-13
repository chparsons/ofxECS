#pragma once

#include <Artemis/Artemis.h>

class ECSsystem : public artemis::EntityProcessingSystem
{

  public:

    ECSsystem(string _id) : id(_id) {};

    string id;
    //virtual void render(){};

  protected:

    //some shortcuts

    template<typename TSystem>
    TSystem* system()
    {
      return ((TSystem*)world->getSystemManager()->getSystem<TSystem>());
    };

    template<typename TSystem>
    TSystem* require_system()
    {
      TSystem* sys = system<TSystem>();
      if ( sys == NULL ) 
      {
        ofLogFatalError("ECSsystem") << "System [" << typeid(this).name() << "] requires a System [" << typeid(TSystem).name() << "]";
        ofExit(); //TODO
      }
      return sys;
    };

    template<typename TComponent>
    TComponent* component(string tag)
    {
      return ((TComponent*)world->getTagManager()->getEntity( tag ).getComponent<TComponent>());
    };

    template<typename TComponent>
    TComponent* require_component(string tag)
    {
      TComponent* comp = component<TComponent>(tag);
      if ( comp == NULL ) 
      {
        ofLogFatalError("ECSsystem") << "System [" << typeid(this).name() << "] requires a Component [" << typeid(TComponent).name() << "] on entity tagged [" << tag << "]";
        ofExit(); //TODO
      }
      return comp;
    }; 

    artemis::EntityManager* entities()
    {
      return world->getEntityManager();
    };

    artemis::SystemManager* systems()
    {
      return world->getSystemManager();
    };

    artemis::TagManager* tags()
    {
      return world->getTagManager();
    };

};

