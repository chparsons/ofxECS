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

      _fps = 30.0;
      micros_per_update = 1000000.0 / _fps;
    };

    void update()
    {
      unsigned long long now = ofGetElapsedTimeMicros();
      unsigned long long dt = now - prev;
      prev = now;
      lag += dt;

      //ofLog() << "update " 
        //<< ", target millis " << micros_per_update * _MICROS_TO_MILLIS
        //<< ", dt " << dt;

      while ( lag >= micros_per_update )
      {
        unsigned long long dt_proc = now - prev_proc;
        prev_proc = now;

        //ofLog() << "__proc"
          //<< ", lag " << lag
          //<< ", dt " << dt_proc;

        _world.loopStart();
        _world.setDelta( dt_proc * _MICROS_TO_MILLIS ); 

        int len = _systems.size();
        for (int i = 0; i < len; i++)
          _systems[i]->process();

        lag -= micros_per_update;
      }
    };

    void render() //at variable framerate
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

    float fps() 
    {
      return _fps;
    };

  private: 

    artemis::World _world;
    artemis::SystemManager *sm;
    artemis::EntityManager *em;
    artemis::TagManager *tm;

    vector<ECSsystem*> _systems; 
    //vector<ECSsystem*> _render_systems; 

    //time in micros
    unsigned long long prev, lag, prev_proc;
    float _fps, micros_per_update;
    const double _MICROS_TO_MILLIS = .001;
};

