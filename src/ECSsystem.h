#pragma once

#include <Artemis/Artemis.h>
#include "ECSgetter.h"

class ECSsystem : public artemis::EntityProcessingSystem, public ECSgetter
{

  public:

    ECSsystem(string _id) : id(_id) {};

    string id;

    artemis::World* get_world()
    {
      return world;
    };

};

