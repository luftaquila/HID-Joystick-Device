#include <Keyboard.h>
#include <HID.h>
void setup()
{
  Serial1.begin(115200);
  Serial.begin(115200);
  Keyboard.begin();
}

int xValue;
int yValue;

void loop()
{
  String receive = Serial1.readStringUntil('|');

  int sub = receive.indexOf(',');
  yValue = receive.substring(sub+1).toInt();
  receive.remove(sub);
  xValue = receive.toInt();

  if(xValue == 0)
  {
    Keyboard.release(KEY_LEFT_ARROW);
    Keyboard.release(KEY_RIGHT_ARROW);
  }
  if(xValue > 0)
  {
    Keyboard.press(KEY_RIGHT_ARROW);
  }
  if(xValue < 0)
  {
    Keyboard.press(KEY_LEFT_ARROW);
  }
  if(yValue == 0)
  {
    Keyboard.release(KEY_UP_ARROW);
    Keyboard.release(KEY_DOWN_ARROW);
  }
  if(yValue < 0)
  {
    Keyboard.press(KEY_UP_ARROW);
  }
  if(yValue > 0)
  {
    Keyboard.press(KEY_DOWN_ARROW);
  }
}
