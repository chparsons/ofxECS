
//===========
//DEPRECTATED
//===========

#include "jsonParams.h"

template<> 
string jsonParams::get_value( Json::Value d ) 
{ return d.asString(); };

template<> 
bool jsonParams::get_value( Json::Value d ) 
{ return d.asBool(); };

template<> 
float jsonParams::get_value( Json::Value d ) 
{ 
  ofLogNotice("jsonParams") << "get_value " << d.asString() << " as float = " << d.asFloat();
  return d.asFloat(); 
};

template<> 
int jsonParams::get_value( Json::Value d ) 
{ return d.asInt(); };

