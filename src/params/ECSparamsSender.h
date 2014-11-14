#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "oscParamSender.h"
//#include "jsonParams.h"

class ECSparamsSender
{
  public:

    ECSparamsSender(){};
    ~ECSparamsSender() { dispose(); }; 

    void init( ofxOscSender* sender )
    {
      this->sender = sender;
    };

    void dispose()
    {
      sender = NULL;
    };

    void add( string param_id, const Json::Value& jval, ofParameterGroup& params ) 
    {

      if ( params.contains( param_id ) )
      {
        ofLogError("ECSparamsSender") << "::add() params group already contains a param with id [" << param_id << "]";
        return;
      }

      if ( sender == NULL ) 
      {
        ofLogError("ECSparamsSender") << "not inited";
        return;
      }

      // array of [val, min, max]
      if ( jval.isArray() ) 
      {
        if ( jval.size() != 3 )
        {
          ofLogError("ECSparamsSender") << "set data from config for component [" << param_id << "] is an array with length (" << jval.size() << "), and it needs exactly (3) values: [value, min, max]";
          return;
        }

        if ( jval[0].isNumeric() ) 
        {
          shared_ptr< oscParamSender<float> > osc_param( new oscParamSender<float>() );
          float val = jval[0].asFloat();
          float min = jval[1].asFloat();
          float max = jval[2].asFloat();
          osc_param->set( sender, param_id, val, min, max );
          params.add( osc_param->param() );
          osc_params[param_id] = osc_param;
        }
      }

      // value, not array
      else
      {

        if ( jval.isBool() ) 
        {
          shared_ptr< oscParamSender<bool> > osc_param( new oscParamSender<bool>() );
          bool val = jval.asBool();
          osc_param->set(sender, param_id, val);
          params.add( osc_param->param() );
          osc_params[param_id] = osc_param;
        } 

        else if ( jval.isString() ) 
        {
          shared_ptr< oscParamSender<string> > osc_param( new oscParamSender<string>() );
          string val = jval.asString();
          osc_param->set(sender, param_id, val);
          params.add( osc_param->param() );
          osc_params[param_id] = osc_param;
        }
      }
      
    };

  private:

    ofxOscSender* sender;
    //jsonParams jsonp;

    map< string, shared_ptr<oscParamSenderAbstract> > osc_params;

    //template<typename T>
    //shared_ptr< oscParamSender<T> > make_osc_param( string param_id, const Json::Value& jarr ) 
    //{
      //shared_ptr< oscParamSender<T> > osc_param( new oscParamSender<T>() );
      //T val; 
      //val = jsonp.get_value<T>( jarr[0] );
      //T min = jsonp.get_value<T>( jarr[1] );
      //T max = jsonp.get_value<T>( jarr[2] );
      //osc_param->set( sender, param_id, val, min, max );
    //return osc_param;
  //};

};


