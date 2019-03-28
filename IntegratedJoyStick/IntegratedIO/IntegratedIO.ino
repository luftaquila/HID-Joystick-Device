const int xAxis = A0;         // joystick X axis
const int yAxis = A1;         // joystick Y axis

//boolean lastButton = HIGH;
//boolean currentButton = HIGH;

boolean Mode = true;

// parameters for reading the joystick:
int range = 12;               // output range of X or Y movement
int threshold = range / 4;    // resting threshold
int center = range / 2;       // resting position value

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop()
{
  int xReading = readAxis(A0);
  int yReading = readAxis(A1);
  /*
  currentButton = debounce(lastButton);
  if(lastButton == HIGH && currentButton == LOW)
    Mode = !Mode;
  lastButton = currentButton;
*/
  String SeparatorMiddle = ","; // Separating x, y axis data
  String SeparatorMiddle2 = "@"; // Separating x, y axis data
  String SeparatorEnd = "|"; // Separating one x, y axis data package
  String SendData = xReading + SeparatorMiddle + yReading + SeparatorMiddle2 + digitalRead(2) + SeparatorEnd; // Set data package
  char transmitter[20];
  

  SendData.toCharArray(transmitter, 20);
  Serial.write(transmitter);
  
  if(Mode == true)
    digitalWrite(13, HIGH);
  else if(Mode == false)
    digitalWrite(13, LOW);

  delay(5);
}

int readAxis(int thisAxis)
{
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the
  // rest position threshold,  use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  }

  // return the distance for this axis:
  return distance;
}

/*boolean debounce(boolean last)
{
  boolean current = digitalRead(2);
  if(last!=current)
  {
    delay(5);
    current = digitalRead(2);
  }
  return current;
}*/
