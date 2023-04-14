#ifndef GameMode_h
#define GameMode_h
#include "Arduino.h"
class GameMode {
public:
  GameMode();
  virtual void Start();

  String Name;

private:
};
#endif