
#include "KingOfTheHill.h"
#include <LiquidCrystal_I2C.h>

KingOfTheHill::KingOfTheHill() {
  Name = "KingOfTheHill";
}


extern LiquidCrystal_I2C lcd;

 void KingOfTheHill::Start() {
  lcd.clear();
  lcd.print("Game started");
  lcd.setCursor(0, 1);
  lcd.print("King of the Hill");
}
