#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxKeyValueOSC.h"
//#include "jsonParams.h"

class ECSparams
{
  public:

    ECSparams(){};
    ~ECSparams() { dispose(); };

    //TODO 
    //void init( Json::Value& settings )
    void init()
    {
      int app_port = 6667;

      receiver.setup( app_port );

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
        bool updated = receiver.get( "/"+params.getName(i), params.get(i) );
        //if (updated) ofLogNotice("ECSparams") << "----- updated param " << params.getName(i) << " = " << params.get(i);
      }
    };

    template<typename T>
    void add( string param_id, const Json::Value& jval, ofParameter<T>& param )
    {

      if ( params.contains( param_id ) )
      {
        ofLogError("ECSparams") << "::add() params group already contains a param with id [" << param_id << "]";
        return;
      }

      params.add( set( param, param_id, jval ) );
    };  

  private:

    ofParameterGroup params;
    ofxKeyValueOSC receiver; 
    //jsonParams jsonp;

    template<typename T>
    ofParameter<T>& set( ofParameter<T>& param, string param_id, const Json::Value& jval )
    {
      T val;

      if ( jval.isArray() )
      {

        if (jval.size() != 3 )
        {
          ofLogError("ECSparams") << "set data from config for component --" << param_id << "-- has an array value with (" << jval.size() << ") values, and it needs exactly (3): [value, min, max]";
          return;
        }


        //FIXME soportar string y otros
        val = jval[0].asFloat();
        T min = jval[1].asFloat();
        T max = jval[2].asFloat();


        //if ( jval[0].isDouble() ) 
        //{
          //val = jval[0].asFloat();
          //T min = jval[1].asFloat();
          //T max = jval[2].asFloat();
        //} 

        //else if ( jval[0].isIntegral() ) 
        //{
          //val = jval[0].asInt();
          //T min = jval[1].asInt();
          //T max = jval[2].asInt();
        //}

        //else if ( jval[0].isBool() ) 
        //{
          //val = jval[0].asBool();
          //T min = jval[1].asBool();
          //T max = jval[2].asBool();
        //}

        //else if ( jval[0].isString() ) 
        //{
          //val = jval[0].asString();
          //T min = jval[1].asString();
          //T max = jval[2].asString();
        //}

        //val = jsonp.get_value<T>( jval[0] );
        //T min = jsonp.get_value<T>( jval[1] );
        //T max = jsonp.get_value<T>( jval[2] );

        return param.set( param_id, val, min, max );
      }

      else
      {
        //FIXME soportar string y otros
        val = jval.asFloat();

        //if ( jval.isDouble() ) 
          //val = jval.asFloat();

        //else if ( jval.isIntegral() ) 
          //val = jval.asInt();

        //else if ( jval.isBool() ) 
          //val = jval.asBool();

        //else if ( jval.isString() ) 
          //val = jval.asString();

        //val = jsonp.get_value<T>(jval);

        return param.set( param_id, val );
      } 

    };

};

