#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxKeyValueOSC.h"

class ECSparams
{
  public:

    ECSparams(){};
    ~ECSparams() { dispose(); };

    void init( int receiver_port )
    {
      receiver.setup( receiver_port );

      ofAddListener( ofEvents().update, this, &ECSparams::update, OF_EVENT_ORDER_BEFORE_APP );
    };

    void dispose()
    {
      ofRemoveListener( ofEvents().update, this, &ECSparams::update, OF_EVENT_ORDER_BEFORE_APP );
    };

    void update(ofEventArgs&)
    {
      int len = params.size();
      for ( int i = 0; i < len; i++ )
      {
        bool updated = receiver.get( "/"+params.getName(i), params.get(i), true );
      }
    };

    template<typename T>
    void add( string param_id, const Json::Value& jval, ofParameter<T>& param )
    {

      //if ( params.contains( param_id ) )
      //{
        //ofLogError("ECSparams") << "add() params group already contains a param with id [" << param_id << "]";
        //return;
      //}

      params.add( set( param, param_id, jval ) );
    };  

  private:

    ofParameterGroup params;
    ofxKeyValueOSC receiver; 

    template<typename T>
    ofParameter<T>& set( ofParameter<T>& param, string param_id, const Json::Value& jval )
    {

      if ( jval.isArray() )
      {

        if (jval.size() != 3 )
        {
          ofLogError("ECSparams") << "set data from config for component --" << param_id << "-- has an array value with (" << jval.size() << ") values, and it needs exactly (3): [value, min, max]";
          return;
        }

        if ( jval[0].isNumeric() ) 
        {
          float val = jval[0].asFloat();
          float min = jval[1].asFloat();
          float max = jval[2].asFloat();
          return param.set(param_id, val, min, max);
        } 

      }

      else
      {

        if ( jval.isNumeric() ) 
        {
          float val = jval.asFloat();
          return param.set( param_id, val );
        }

        else if ( jval.isBool() ) 
        {
          bool val = jval.asBool();
          return param.set( param_id, val );
        }

        //else if ( jval.isString() ) 
        //{
          //string val = jval.asString();
          //return param.set( param_id, val );
        //}

      } 

    };

};

