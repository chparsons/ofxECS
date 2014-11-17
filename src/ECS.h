#pragma once

#include "ofMain.h"
#include <Artemis/Artemis.h>
#include "ECSsystem.h"

class ECS
{
  public:

    ECS(){};

    void init()
    {
      sm = _world.getSystemManager();
      em = _world.getEntityManager();
      tm = _world.getTagManager();
    };

    void update()
    {
      //ofLogNotice("ECS") << "--update";
      //TODO game/sim loop accum
      _world.loopStart();
      //deciseconds ???
      //github.com/vinova/Artemis-Cpp
      //_world.setDelta( 0.0016f ); 
      _world.setDelta( 1.0f/ofGetFrameRate()*0.1f ); 
      int len = _systems.size();
      for (int i = 0; i < len; i++)
        _systems[i]->process();
    };

    void render()
    {
      int len = _systems.size();
      for (int i = 0; i < len; i++)
        //_render_systems[i]->process();
        _systems[i]->render();
    };

    void init_systems()
    {
      sm->initializeAll();
    };

    void add_system( ECSsystem* sys )
    {
      _systems.push_back( (ECSsystem*)sm->setSystem( sys ) );
    }; 

    //void add_render_system( ECSsystem* sys )
    //{
      //_render_systems.push_back( (ECSsystem*)sm->setSystem( sys ) );
    //};

    artemis::EntityManager* entities()
    {
      return em;
    };

    artemis::SystemManager* systems()
    {
      return sm;
    };

    artemis::TagManager* tags()
    {
      return tm;
    };

    template<typename TSystem>
    TSystem* system()
    {
      return ((TSystem*)sm->getSystem<TSystem>());
    };

    //get component by entity tag
    template<typename TComponent>
    TComponent* component(string tag)
    {
      return ((TComponent*)tm->getEntity( tag ).getComponent<TComponent>());
    };

    artemis::World* world()
    {
      return &_world;
    };

  private: 

    artemis::World _world;
    artemis::SystemManager *sm;
    artemis::EntityManager *em;
    artemis::TagManager *tm;

    vector<ECSsystem*> _systems; 
    //vector<ECSsystem*> _render_systems; 

    static float _fps;
};

