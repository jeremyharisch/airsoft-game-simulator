#ifndef KingOfTheHill_h
#define KingOfTheHill_h
#include "Arduino.h"
#include "GameMode.h"

class KingOfTheHill : public GameMode {
public:
  KingOfTheHill();
  virtual void Start();

private:
};
#endif