
//===========
//DEPRECTATED
//===========

#pragma once

#include "ofMain.h"
#include "ofxJSON.h"

class jsonParams
{
  public:
    jsonParams(){};

    template<typename T>
    T get_value( Json::Value d ) {};
};

