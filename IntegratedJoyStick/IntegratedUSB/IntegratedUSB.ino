#include <Keyboard.h>
#include <Mouse.h>
#include <HID.h>

boolean Mode = true;

int xValue;
int yValue;

int LastButtonReceive = 1;

unsigned long int time1 = 0;

void setup()
{
  Serial1.begin(115200);
  Serial.begin(115200);
  Keyboard.begin();
  Mouse.begin();
}

void loop()
{
  String receive = Serial1.readStringUntil('|'); // Read one x, y axis data package
Serial.println(receive);

  int SeparatorMiddle = receive.indexOf(','); // Locate axis data separator location
  int SeparatorMiddle2 = receive.indexOf('@'); // Locate axis data separator location

  int ButtonReceive = receive.substring(SeparatorMiddle2 + 1).toInt();
  receive.remove(SeparatorMiddle2);
  
  yValue = receive.substring(SeparatorMiddle + 1).toInt(); // Separate y axis data from received data
  receive.remove(SeparatorMiddle); // Remove y axis data from received data
  xValue = receive.toInt();

  if(LastButtonReceive == 0 && LastButtonReceive != ButtonReceive) // Push
    time1 = millis();
    
  if(LastButtonReceive == 1 && LastButtonReceive != ButtonReceive) // Release
  { 
    if(millis() - time1 > 1000)
      Mode = !Mode;
    else
      Keyboard.write(KEY_RETURN);
  }
 
  LastButtonReceive = ButtonReceive;

  if(Mode == true)
    Mouse.move(xValue, yValue, 0);
  
  else if(Mode == false)
  {
    /*if(xValue == 0)
    {
      Keyboard.release(KEY_LEFT_ARROW);
      Keyboard.release(KEY_RIGHT_ARROW);
    }
    if(yValue == 0)
    {
      Keyboard.release(KEY_UP_ARROW);
      Keyboard.release(KEY_DOWN_ARROW);
    }*/
    
  if(xValue > 0)    Keyboard.write(KEY_RIGHT_ARROW);
  if(xValue < 0)    Keyboard.write(KEY_LEFT_ARROW);

  if(yValue < 0)    Keyboard.write(KEY_UP_ARROW);
  if(yValue > 0)    Keyboard.write(KEY_DOWN_ARROW);
  }
}
