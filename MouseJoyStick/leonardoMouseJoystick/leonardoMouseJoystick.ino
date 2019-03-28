#include <Mouse.h>
#include <Keyboard.h>
#include <HID.h>

const byte MOUSE_CLICK = 5;
const byte SCROLL_UP = 2;
const byte SCROLL_DOWN = 4;
const byte HOME = 3;
const byte MOUSE_SPEED = 8;

int scale = 175;
boolean scalestate = true;

const byte JOY_X = 0;
const byte JOY_Y = 1;

void setup()
{
  pinMode(MOUSE_CLICK, INPUT_PULLUP);
  pinMode(SCROLL_UP, INPUT_PULLUP);
  pinMode(SCROLL_DOWN, INPUT_PULLUP);
  pinMode(HOME, INPUT_PULLUP);
  Mouse.begin();
  Keyboard.begin();
}
void loop()
{
  int set_X = (analogRead(JOY_X) - 510) / scale;
  int set_Y = ((analogRead(JOY_Y) - 510) / scale) * -1;
  Mouse.move(set_X, set_Y, 0);
  if(digitalRead(MOUSE_CLICK) == LOW)
  {
    Mouse.click();
    delay(150);
  }
  if(digitalRead(SCROLL_UP) == LOW)
  {
    Mouse.move(0, 0, 1);
    delay(100);
  }
  if(digitalRead(SCROLL_DOWN) == LOW)
  {
    Mouse.move(0, 0, -1);
    delay(100);
  }
  if(digitalRead(HOME) == LOW)
  {
    Keyboard.press(KEY_LEFT_ALT);
    delay(10);
    Keyboard.press(KEY_HOME);
    delay(30);
    Keyboard.releaseAll();
    delay(30);
  }
  if(digitalRead(MOUSE_SPEED) == LOW)
  {
    if(scalestate == true)
    {
      scalestate = false;
      scale = 100;
    }
    else if(scalestate == false)
    {
      scalestate = true;
      scale = 175;
    }
    delay(200);
  }
  delay(5);
}
