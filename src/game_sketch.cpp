#include <Arduino.h>

// include the libraries
#include <Keypad.h>
#include <LiquidCrystal.h>
#include "GameMode.h"
#include "BombDefusal.h"
#include "KingOfTheHill.h"
#include "PCF8574.h" // https://github.com/xreef/PCF8574_library
#include "pitches.h"
#include <LiquidCrystal_I2C.h>

#define pound 14

void isButtonPressed(int button);

void showStartScreen();

void playStartUpSound();

void playLEDStartUpAnmiation();

void toggleLEDsSequentially(uint8_t value);

void toggleLEDs(uint8_t value);

GameMode *selectGameMode();

void printModeSelection(String mode);

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x3F for a 16 chars and 2 line display

// TODO: Remove hardcoded timer
int Scount = 0;      // count seconds
int Mcount = 1;      // count minutes
int Hcount = 0;      // count hours
int DefuseTimer = 0; // set timer to 0

long secMillis = 0;   // store last time for second add
long interval = 1000; // interval for seconds

// password setup
int pwdLength = 6;
char password[6];      // number of characters in our password
int currentLength = 0; // defines which number we are currently writing
int i = 0;
char entered[6];

// I2C Board setup
PCF8574 ex1(0x24);

// keypad setup
const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns
char hexaKeys[ROWS][COLS] = {
    {'D', '#', '0', '*'},
    {'C', '9', '8', '7'},
    {'B', '6', '5', '4'},
    {'A', '3', '2', '1'}};
byte colPins[COLS] = {2, 3, A5, A4};   // definition of colomn pins
byte rowPins[ROWS] = {A3, A2, A1, A0}; // definition of row pins
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// button setup
int redButton = 8;
int blueButton = 11;

// buzzer setup
int buzzer = 6;

GameMode *selectedGameMode;

void setup()
{
  Serial.begin(9600);
  Serial.println("NEW setup");

  // set up the buttons
  pinMode(redButton, INPUT);
  pinMode(blueButton, INPUT);

  // set up the LCD
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);

  // set up LEDs; external I2C Board
  for (int i = 0; i < 8; i++)
  {
    ex1.pinMode(i, OUTPUT);
  }
  toggleLEDs(LOW);

  // start up
  showStartScreen();

  selectedGameMode = selectGameMode();
  lcd.clear();
  lcd.print("Selected Mode:");
  lcd.setCursor(0, 1);
  lcd.print(selectedGameMode->Name);
  delay(3000);
  selectedGameMode->Start();
  delay(3000);

  //(*selectedGameMode).Start();
}

void loop()
{
  // set the cursor to column 0, line 1
  //(note: line 1 is the second row, since counting begins with 0):
  //  lcd.clear();
  //  lcd.setCursor(0, 1);
  //  // print the number of seconds since reset:
  //  //selectedGameMode->Start();
  //  lcd.print(selectedGameMode->Name);
  //  delay(1000);
  //  lcd.print(millis() / 1000);

  // TODO: start the specific game mode

  isButtonPressed(redButton);
  isButtonPressed(blueButton);
  delay(500);
}

void isButtonPressed(int button)
{
  int buttonstatus = digitalRead(button);
  if (buttonstatus == HIGH) // Wenn der Taster gedrückt ist...
  {
    tone(6, 100); // …spiele diesen Ton...
    delay(500);   // …und zwar für eine Sekunde...
    tone(6, 300); // …spiele diesen Ton...
    delay(500);   // …und zwar für eine Sekunde...
    noTone(6);    // Ton abschalten
  }
}

void showStartScreen()
{
  playStartUpSound();
  lcd.print("Hello, Player!");
  lcd.setCursor(0, 1);
  lcd.print("Press # to start");
  playLEDStartUpAnmiation();
  while (true)
  {
    char key = keypad.getKey();
    if (key == '#')
    {
      lcd.clear();
      break;
    }
  }
}

void playStartUpSound()
{
  tone(buzzer, NOTE_G2);
  delay(500);
  noTone(buzzer);
}

void playLEDStartUpAnmiation()
{
  toggleLEDsSequentially(HIGH);
  toggleLEDs(LOW);
  toggleLEDsSequentially(HIGH);
}

void toggleLEDsSequentially(uint8_t value)
{
  for (int i = 4; i > 0; i--)
  {
    ex1.digitalWrite(i, value);
    delay(300);
  }
}

void toggleLEDs(uint8_t value)
{
  for (int i = 4; i > 0; i--)
  {
    ex1.digitalWrite(i, value);
  }
}

// TODO move setup stuff into normal loop and see if this works better; setup crashes when Start is being
GameMode *selectGameMode()
{
  printModeSelection("Select Game Mode");
  GameMode *gameMode;

  bool done = false;
  while (!done)
  {
    char key = keypad.getKey();
    if (key == '#')
    {
      if (gameMode->Name != "")
      {
        done = true;
      }
    }
    if (key == 'A')
    {
      gameMode = new BombDefusal();
      printModeSelection(gameMode->Name);
    }
    if (key == 'B')
    {
      gameMode = new KingOfTheHill();
      printModeSelection(gameMode->Name);
    }
    if ((key == 'C') || (key == 'D'))
    {
      gameMode->Name = "";
      lcd.clear();
      lcd.print("Not implemented");
      delay(3000);
      printModeSelection("Select Game Mode");
    }
  }
  return gameMode;
}

void printModeSelection(String mode)
{
  lcd.clear();
  lcd.print(mode);
  lcd.setCursor(0, 1);
  lcd.print("# to confirm");
}
