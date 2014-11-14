#pragma once

#include <Artemis/Artemis.h>
#include "ofxECS.h"

class ComponentFactory
{
  public:

  ComponentFactory(){};
  virtual ~ComponentFactory(){};

  virtual ECScomponent* make(string id) = 0;

};
