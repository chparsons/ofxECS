#pragma once

#include <Artemis/Artemis.h>

class ECSgetter
{

  public:

    ECSgetter(){};

    virtual artemis::World* get_world() = 0;

    template<typename TSystem>
    TSystem* system()
    {
      return ((TSystem*)get_world()->getSystemManager()->getSystem<TSystem>());
    };

    template<typename TComponent>
    TComponent* component(string tag)
    {
      return ((TComponent*)get_world()->getTagManager()->getEntity( tag ).getComponent<TComponent>());
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
      return get_world()->getEntityManager();
    };

    artemis::SystemManager* systems()
    {
      return get_world()->getSystemManager();
    };

    artemis::TagManager* tags()
    {
      return get_world()->getTagManager();
    };

};

