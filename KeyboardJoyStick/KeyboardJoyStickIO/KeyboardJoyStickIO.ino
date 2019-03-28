const int xAxis = A0;         // joystick X axis
const int yAxis = A1;         // joystick Y axis

// parameters for reading the joystick:
int range = 12;               // output range of X or Y movement
int responseDelay = 5;        // response delay of the mouse, in ms
int threshold = range / 4;    // resting threshold
int center = range / 2;       // resting position value

void setup() {
  Serial.begin(115200);
}

void loop()
{
  int xReading = readAxis(A0);
  int yReading = readAxis(A1);

  String a = ",";
  String a1 = "|";
  String b = xReading+a+yReading+a1;
  char c[20];
  b.toCharArray(c, 20);
  Serial.write(c);

  delay(responseDelay);
}

/*
  reads an axis (0 or 1 for x or y) and scales the
 analog input range to a range from 0 to <range>
 */

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


