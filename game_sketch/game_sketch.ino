

// include the libraries
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Tone.h>
#include "GameMode.h"
#include "BombDefusal.h"
#include "KingOfTheHill.h"
#define pound 14

//initialize the library by associating any needed LCD interface pin
//with the arduino pin number it is connected to
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//TODO: Remove hardcoded timer
int Scount = 0;       // count seconds
int Mcount = 1;       // count minutes
int Hcount = 0;       // count hours
int DefuseTimer = 0;  // set timer to 0

long secMillis = 0;    // store last time for second add
long interval = 1000;  // interval for seconds

//password setup
int pwdLength = 6;
char password[6];       // number of characters in our password
int currentLength = 0;  //defines which number we are currently writing
int i = 0;
char entered[6];

//led setup
int greenLedPin = 4;
int yellowLedPin2 = 3;
int redLedPin3 = 2;


//keypad setup
const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns
char hexaKeys[ROWS][COLS] = {
  { 'D', '#', '0', '*' },
  { 'C', '9', '8', '7' },
  { 'B', '6', '5', '4' },
  { 'A', '3', '2', '1' }
};
byte colPins[COLS] = { 2, 3, A5, A4 };    //definition of colomn pins
byte rowPins[ROWS] = { A3, A2, A1, A0 };  //definition of row pins
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

GameMode* selectedGameMode;

void setup() {
  Serial.begin(9600);
  Serial.println("NEW setup");

  //set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  //Print a message to the LCD.


  showStartScreen();

  selectedGameMode = selectGameMode();
  lcd.clear();
  lcd.print("Selected Mode:");
  lcd.setCursor(0, 1);
  lcd.print(selectedGameMode->Name);
  delay(3000);
  selectedGameMode->Start();

  //(*selectedGameMode).Start();

  
}

void loop() {
  //set the cursor to column 0, line 1
  //(note: line 1 is the second row, since counting begins with 0):
  lcd.clear();
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //selectedGameMode->Start();
  lcd.print(selectedGameMode->Name);
  // lcd.print(millis() / 1000);
}





void showStartScreen() {
  lcd.print("Hello, Player!");
  lcd.setCursor(0, 1);
  lcd.print("Press # to start");

  while (true) {
    char key = keypad.getKey();
    if (key == '#') {
      lcd.clear();
      break;
    }
  }
}


// TODO move setup stuff into normal loop and see if this works better; setup crashes when Start is being
GameMode* selectGameMode() {
  printModeSelection("Select Game Mode");
  GameMode* gameMode;

  bool done = false;
  while (!done) {
    char key = keypad.getKey();
    if (key == '#') {
      if (gameMode->Name != "") {
        done = true;
      }
    }
    if (key == 'A') {
      gameMode = new BombDefusal();
      printModeSelection(gameMode->Name);
    }
    if (key == 'B') {
      gameMode = new KingOfTheHill();
      printModeSelection(gameMode->Name);
    }
    if ((key == 'C') || (key == 'D')) {
      gameMode->Name = "";
      lcd.clear();
      lcd.print("Not implemented");
      delay(3000);
      printModeSelection("Select Game Mode");
    }
  }
  return gameMode;
}

void printModeSelection(String mode) {
  lcd.clear();
  lcd.print(mode);
  lcd.setCursor(0, 1);
  lcd.print("# to confirm");
}
