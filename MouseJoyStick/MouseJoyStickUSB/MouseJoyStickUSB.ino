#include <Mouse.h>
#include <HID.h>
void setup()
{
  Serial1.begin(115200);
  Serial.begin(115200);
  Mouse.begin();
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
  
  Mouse.move(xValue, yValue, 0);
}
