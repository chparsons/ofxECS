#pragma once

#include "ofMain.h"
#include <Artemis/Artemis.h>
#include "ECSsystem.h"
#include "ECSgetter.h"

class ECS : public ECSgetter
{
  public:

    ECS(){};

    void init()
    {
      sm = _world.getSystemManager();
      em = _world.getEntityManager();
      tm = _world.getTagManager();
      fps(30.0); 
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
        dt_micros = now - prev_proc;
        float fA = 0.95; 
        _dt_micros = (fA*_dt_micros)+((1.0-fA)*dt_micros);
        prev_proc = now;

        //ofLog() << "__proc"
          //<< ", lag " << lag
          //<< ", dt " << dt_micros;

        _world.loopStart();
        _world.setDelta( dt_micros * _MICROS_TO_MILLIS ); 

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

    artemis::World* get_world()
    {
      return &_world;
    }; 

    void fps( float v ) 
    {
      _fps = v;
      micros_per_update = 1000000.0/_fps;
    };

    float fps() 
    {
      return _fps;
    };

    float framerate()
    {
      return 1000000.0/_dt_micros;
    };

  private: 

    artemis::World _world;
    artemis::SystemManager *sm;
    artemis::EntityManager *em;
    artemis::TagManager *tm;

    vector<ECSsystem*> _systems; 
    //vector<ECSsystem*> _render_systems; 

    //time in micros
    unsigned long long prev, lag, prev_proc, dt_micros;
    float _fps, micros_per_update, _dt_micros; 
    const double _MICROS_TO_MILLIS = .001;
};

