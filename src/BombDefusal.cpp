
#include "BombDefusal.h"
#include <LiquidCrystal_I2C.h>

BombDefusal::BombDefusal() {
  Name = "Bomb Defusal";
}


extern LiquidCrystal_I2C lcd;

void BombDefusal::Start() {
  lcd.clear();
  lcd.print("Game started");
  lcd.setCursor(0, 1);
  lcd.print("Bomb Defusal");
}

int setTimeToPlant() {

}

int setTimeToDefuse() {
  
}
