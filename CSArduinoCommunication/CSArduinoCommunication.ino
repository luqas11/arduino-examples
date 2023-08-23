// Number of connected LEDs
const int LEDS_NUMBER = 5;
// Number of the first LED
const int LED_OFFSET = 2;
// Max value to be sent from the CS script
const int MAX_VALUE = 300;

String receivedValue = "";

void setup()
{
  // Set all given pins as outputs
  for (int i = LED_OFFSET; i < LED_OFFSET + LEDS_NUMBER; i++)
  {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
}

void loop()
{
  // Read any serial input
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    // If the received character is a number, concatenate it to the read value
    if (c <= '9' && c >= '0')
    {
      receivedValue.concat(c);
    }
    // If not, finish the reading and update LEDs accordingly
    else
    {
      updateLeds(receivedValue);
      receivedValue = "";
    }
  }
}

// Update the LEDs status depending on the received value and the given max value
void updateLeds(String value)
{
  // Iterate over the given pin numbers
  for (int i = LED_OFFSET; i < LED_OFFSET + LEDS_NUMBER; i++)
  {
    // Decide if each LED should be on based on dividing the max value in equally distributed intervals
    if (value.toInt() >= (i - LED_OFFSET + 1) * (MAX_VALUE / (LEDS_NUMBER + 1)))
    {
      digitalWrite(i, HIGH);
    }
    else
    {
      digitalWrite(i, LOW);
    }
  }
}
