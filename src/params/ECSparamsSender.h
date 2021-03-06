#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "oscParamSender.h"

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

    void send()
    {
      for ( map< string, shared_ptr<oscParamSenderAbstract> >::iterator it = osc_params.begin(); it != osc_params.end(); ++it )
        it->second->send();
    };

    void add( string param_id, const Json::Value& jval, ofParameterGroup& params ) 
    {

      bool inited = params.contains( param_id );
      //if ( params.contains( param_id ) )
      //{
        //ofLogError("ECSparamsSender") << "::add() params group already contains a param with id [" << param_id << "]";
        //return;
      //}

      if ( sender == NULL ) 
      {
        ofLogError("ECSparamsSender") << "not inited";
        return;
      }

      // array of [val, min, max] for numbers
      if ( jval.isArray() ) 
      {
        if ( jval.size() != 3 )
        {
          ofLogError("ECSparamsSender") << "set data from config for component [" << param_id << "] is an array with length (" << jval.size() << "), and it needs exactly (3) values: [value, min, max]";
          return;
        }

        if ( jval[0].isNumeric() ) 
        {
          float val = jval[0].asFloat();
          float min = jval[1].asFloat();
          float max = jval[2].asFloat();

          if (inited) //send
          {
            osc_params[param_id]->param().cast<float>().set( param_id, val, min, max );
            osc_params[param_id]->send();
          }

          else //init
          {
            shared_ptr< oscParamSender<float> > osc_param( new oscParamSender<float>() );
            osc_param->set( param_id, val, min, max );
            params.add( osc_param->init( sender ) );
            osc_params[param_id] = osc_param;
          }
        }
      }

      // single value
      else
      {

        if ( jval.isBool() ) 
        {
          bool val = jval.asBool();

          if (inited) //send
          {
            osc_params[param_id]->param().cast<bool>().set( param_id, val );
            osc_params[param_id]->send();
          }

          else //init
          {
            shared_ptr< oscParamSender<bool> > osc_param( new oscParamSender<bool>() );
            osc_param->set( param_id, val );
            params.add( osc_param->init( sender ) );
            osc_params[param_id] = osc_param;
          }
        } 

        //else if ( jval.isString() ) 
        //{
          //shared_ptr< oscParamSender<string> > osc_param( new oscParamSender<string>() );
          //string val = jval.asString();
          //osc_param->set( param_id, val );
          //osc_param->init( sender );
          //params.add( osc_param->param() );
          //osc_params[param_id] = osc_param;
        //}

      }

    };

  private:

    ofxOscSender* sender;

    map< string, shared_ptr<oscParamSenderAbstract> > osc_params;

};


