
#include "BombDefusal.h"
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

BombDefusal::BombDefusal()
{
  Name = "Bomb Defusal";
}

extern LiquidCrystal_I2C lcd;
extern Keypad keypad;

void BombDefusal::Start()
{
  setTimeToPlant();
}

void setTimeToPlant()
{
  // int time = 15;
  String timeString = "15";

  lcd.clear();
  lcd.print("Set Plant-Time");
  lcd.setCursor(0, 1);

  String tmp = "Minutes: " + timeString;
  lcd.print(tmp);
  int cursorPositionX = tmp.length();
  lcd.setCursor(cursorPositionX, 1);
  lcd.blink();

  bool done = false;
  while (!done)
  {
    char key = keypad.getKey();
    if (key != NULL)
    {
Serial.println(key);
    }
    
    if (key == '#' && timeString != "")
    {
      done = true;
      break;
    }
    else if (key == '*')
    {
      timeString = "";
      lcd.clear();
      lcd.print("Set Plant-Time");
      lcd.setCursor(0, 1);

      String tmp = "Minutes: " + timeString;
      lcd.print(tmp);
      int cursorPositionX = tmp.length();
      lcd.setCursor(cursorPositionX, 1);
    }
    else if (key == 'A' || key == 'B' || key == 'C' || key == 'D')
    {
      continue;
    }
    else if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0')
    {
      timeString += key;
      lcd.clear();
      lcd.print("Set Plant-Time");
      lcd.setCursor(0, 1);

      String tmp = "Minutes: " + timeString;
      lcd.print(tmp);
      int cursorPositionX = tmp.length();
      lcd.setCursor(cursorPositionX, 1);
    }
  }
}

// int setTimeToDefuse()
// {
// }
