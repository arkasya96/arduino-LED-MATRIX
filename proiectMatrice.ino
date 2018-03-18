#include <LiquidCrystal.h>
#include "LedControl.h"
#include <stdlib.h>
#include <ArduinoSTL.h>
#include <Arduino.h>
#include <cmath>
#include <iostream>
using namespace std;
//const int v0 = 9;
//const int rs = 1;
//const int E = 2;
//const int d4 = 4;
//const int d5 = 5;
//const int d6 = 6;
//const int d7 = 7;
//const int SW_pin = 13; // digital pin connected to switch output
//const int X_pin = 0; // analog pin connected to X output
//const int Y_pin = 1;
#define v0 9
#define rs 1
#define E 2
#define d4 4
#define d5 5
#define d6 6
#define d7 7
#define SW_pin 13 // digital pin connected to switch output
#define X_pin 0 // analog pin connected to X output
#define Y_pin 1


int scor = 0;
int lives = 4;
int UD = 0;
int LR = 0;

LedControl lc = LedControl(12, 11, 10, 1); //
// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219
LiquidCrystal lcd(rs, E, d4, d5, d6, d7);

int start = 0;

int pressed = 0;
//------------------------------- ship
class Ship {
  public:
    int x, y;
    Ship() {
      x = 4;
      y = 7;
    }
    ~Ship() {
      //destructor
    }
    void drawShip()
    {
      lc.clearDisplay(0);
      lc.setLed(0, x, y, true);
      lc.setLed(0, x - 1, y, true);
      lc.setLed(0, x, y - 1, true);
      lc.setLed(0, x + 1, y, true);

    }
    void updateCoord()
    {
      x = map(LR, 0, 900, 1, 6); //This maps the values//
      //y = map(UD, 0,1000, 1, 7)+3;
      //y = 7;
    }
};

//------------------------------------enemy
class Enemy
{
  public:
    int x, y;
    Enemy() {
      x = rand() % 5 + 1;
      y = 0;
    }
    ~Enemy() {
      //destructor
    }
    void drawEnemy() {
      lc.setLed(0, x, y, true);
    }
    void updateEnemy() {
      y = y + 1;
    }
};

//-------------------bullet

class Bullet
{
  public:
    int x, y;
    Bullet(int x, int y) {
      this->x = x;
      this->y = y;
      //dasd
    }
    ~Bullet() {
      //destructor
    }
    void drawBullet() {
      lc.setLed(0, x, y, true);
    }
    void updateBullet() {
      y = y - 1;
    }
};

Ship *ship = new Ship();
std::vector<Enemy>enemy;
std::vector<Bullet>bullets;
int maxFirstLevel = 15;
int maxSecondLevel = 23;
int maxThirdLevel = 22;

int matrix[5][8] = {
  {0, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 1, 0, 0, 1, 1, 0},
  {0, 0, 1, 1, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 0, 1, 0}
};

int matrix2[5][8] = {
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 0}
};

int matrix3[5][8] = {
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 0}
};
int sumaMatrice(int matrice[5][8])
{
  int suma = 0;
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 8; j++)
      suma += matrice[i][j];

  return suma;

}

int scor2 = 0;
//int pres = 0;
int intervalFirstLevel = 9000;
int intervalSecondLevel = 17000;
//int intervalThirdLevel = 11000;

bool firstLevelOver = false;
bool secondLevelOver = false;
bool thirdLevelOver = false;
//unsigned long previousMillis = 0;
int timeElapsed = 0;


void restart() {
  timeElapsed = 0;
  scor = 0;
  scor2 = 0;
  start = 0;
  firstLevelOver = false;
  secondLevelOver = false;
  thirdLevelOver = false;

}
void gameOver() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("time: ");
  lcd.print(timeElapsed);
  lcd.setCursor(0, 1);
  lcd.print("scor: ");
  lcd.print(scor2 + scor);
  if (digitalRead(SW_pin) == LOW)
  {

    play();
  }
  start = 0;

}

void secondLevel() {
  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 8; col++)
    {
      if (matrix2[row][col] == 1)
        lc.setLed(0, col, row, true);
    }

  if (millis() <= intervalSecondLevel)
  {

    int mapBullet = map(analogRead(A1), 0, 1023, 0, 7);
    if (mapBullet == 0)
    {
      Bullet bul = Bullet(ship->x, ship->y - 2);
      bullets.push_back(bul);

      for (int i = 0; i < bullets.size(); i++)
      {
        bullets[i].drawBullet();
        bullets[i].updateBullet();
        int col = bullets[i].x;
        int row = bullets[i].y;
        if (matrix2[row][col] == 1)
        {
          bullets.erase(bullets.begin() + i);
          matrix2[row][col] = 0;
          scor2 += 1;
        }
        if (bullets[i].y < 0)
        {
          bullets.erase(bullets.begin() + i);
        }
      }
    }

    if (sumaMatrice(matrix2) == 0)
    {

      secondLevelOver = true;
      gameOver();

    }
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("time: ");
      lcd.print(millis());
      lcd.setCursor(0, 1);
      lcd.print("scor: ");
      lcd.print(scor); // scor = bubbles remaining
      lcd.setCursor(9, 1);
      lcd.print(secondLevelOver);
    }
  }
  else if ((scor + scor2) < (maxFirstLevel + maxSecondLevel))
  {
    gameOver();
  }
}

void firstLevel() {
  timeElapsed = millis();
  for (int row = 0; row < 8; row++)
    for (int col = 0; col < 8; col++)
    {
      if (matrix[row][col] == 1)
        lc.setLed(0, col, row, true);
    }
  if (millis() <= intervalFirstLevel)
  {
    int mapBullet = map(analogRead(A1), 0, 1023, 0, 7);
    if (mapBullet == 0)
    {
      Bullet bul = Bullet(ship->x, ship->y - 2);
      bullets.push_back(bul);

      for (int i = 0; i < bullets.size(); i++)
      {
        bullets[i].drawBullet();
        bullets[i].updateBullet();
        int col = bullets[i].x;
        int row = bullets[i].y;
        if (matrix[row][col] == 1)
        {
          bullets.erase(bullets.begin() + i);
          matrix[row][col] = 0;
          scor += 1;
        }

        if (bullets[i].y < 0)
        {
          bullets.erase(bullets.begin() + i);
        }
      }
    }

    if (maxFirstLevel - scor == 0)
    {
      firstLevelOver = true;
    }

    lcd.setCursor(0, 0);
    lcd.print("time: ");
    lcd.print(millis());
    lcd.setCursor(0, 1);
    lcd.print("scor: ");
    lcd.print(scor); // scor = bubbles remaining
    lcd.setCursor(9, 1);
  }
  else if (scor < maxFirstLevel)
  {
    gameOver();
  }
  if (firstLevelOver == true)
  {
    secondLevel();
  }
}

void play() {
  ship->drawShip();
  ship->updateCoord();

  LR = analogRead(A0);
  lcd.clear();
  firstLevel();
}


//------------------setup
void setup() {
  // put your setup code here, to run once:
  analogWrite(v0, 100);
  lcd.begin(16, 2);

  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 8); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  pinMode(SW_pin, INPUT);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("press the button to start");

}

void loop() {

  if (digitalRead(SW_pin) == LOW)
  {
    start = 1;
  }

  if (start == 1)
  {
    play();


  }

}

