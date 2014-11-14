#pragma once

#include <Artemis/Artemis.h>
#include "ofMain.h"
#include "ofxJSON.h"
#include "ECSparams.h"
#include "ParamID.h"

class ECScomponent : public artemis::Component
{

  public:

    ECScomponent(string _id) : id(_id) {};

    virtual ~ECScomponent() 
    {
      ecs_params = NULL; 
    };

    string id;

    virtual void init( string e_id, Json::Value d, ECSparams* p )
    {
      _entity_id = e_id;
      _data = d;
      ecs_params = p;
    }; 

  protected:

    string _entity_id; //container
    Json::Value _data;
    ECSparams* ecs_params;

    template<typename T>
    void param( ofParameter<T>& _param, string data_key ) 
    {
      if ( ecs_params == NULL )
      {
        ofLogError("ECScomponent") << "param() set data for component [" << data_key << "] ECSparam is NULL";
        return;
      }

      string param_id = ParamID::make( _entity_id, this->id, data_key );

      const Json::Value& value = _data[data_key]; 

      ecs_params->add( param_id, value, _param );
    }; 

};

