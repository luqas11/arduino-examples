void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Read the analog input values, and map them to a percentage value between 0 and 100
  int rawValueX = analogRead(A0);
  int mappedValueX = map(rawValueX, 0, 1023, 0, 100);
  int rawValueY = analogRead(A1);
  int mappedValueY = map(rawValueY, 0, 1023, 0, 100);

  // Print the parsed values in the serial monitor
  Serial.println();
  Serial.println("Joystick values:");
  Serial.println("X :" + String(mappedValueX));
  Serial.println("Y: " + String(mappedValueY));

  delay(100);
}
