#pragma once
#include <Artemis/Artemis.h>

class VelocityComponent : public artemis::Component 
{
  public:
    float velocityX;
    float velocityY;

    VelocityComponent(float velocityX, float velocityY)
    {
      this->velocityX = velocityX;
      this->velocityY = velocityY;
    };
};

class PositionComponent : public artemis::Component
{

  public:
    float posX;
    float posY;
    PositionComponent(float posX, float posY)
    {
      this->posX = posX;
      this->posY = posY;
    };
};

