#include "Keyboard.h"

// Input pin numbers
int inputs[] = {8, 9};
// Keys to be pressed when each pin is LOW
int keys[] = {107, 108};
// State of the keys
int state[] = {HIGH, HIGH};

void setup()
{
  // Loop over the pin array
  for (int i = 0; i < int(sizeof(inputs) / 2); i++)
  {
    // Initialize the pin with the internal pull up enabled
    pinMode(inputs[i], INPUT_PULLUP);
  }
  Keyboard.begin();
  Serial.begin(9600);
}

void loop()
{
  // Loop over the pin array
  for (int i = 0; i < int(sizeof(inputs) / 2); i++)
  {
    // Read the pin value
    uint8_t value = digitalRead(inputs[i]);
    // Evaluate if the state has change since the previos loop, and if not, do nothing
    if (value != state[i])
    {
      // If the pin is LOW, press the key indicated for that pin
      if (value == LOW)
      {
        Serial.println("Pressing key " + String(keys[i]));
        Keyboard.press(keys[i]);
      }
      // If the pin is HIGH, release the key indicated for that pin
      else
      {
        Serial.println("Releasing key " + String(keys[i]));
        Keyboard.release(keys[i]);
      }
      // Update the key state value for the next loop
      state[i] = value;
    }
  }
}
