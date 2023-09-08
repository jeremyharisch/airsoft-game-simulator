#ifndef BombDefusal_h
#define BombDefusal_h
#include "Arduino.h"
#include "GameMode.h"

class BombDefusal : public GameMode
{
public:
  BombDefusal();
  virtual void Start();

private:
};

void setTimeToPlant();
#endif