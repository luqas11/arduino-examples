#include <Joystick.h>
#include <SegaController.h>

typedef struct
{
  word controllerButton;
  int joystickButton;
} buttonMap;

// Define the mapping between the Sega controller buttons and the PC joystick buttons
buttonMap buttonsMap[] = {
    {SC_BTN_UP, 1},
    {SC_BTN_DOWN, 2},
    {SC_BTN_LEFT, 3},
    {SC_BTN_RIGHT, 4},
    {SC_BTN_START, 5},
    {SC_BTN_A, 6},
    {SC_BTN_B, 7},
    {SC_BTN_C, 8},
    {SC_BTN_X, 9},
    {SC_BTN_Y, 10},
    {SC_BTN_Z, 11},
    {SC_BTN_MODE, 12}};

const byte BUTTONS = 12;

// Define the wiring between the Sega controller and the Arduino
SegaController controller(8, 2, 3, 4, 5, 6, 7);

word currentState = 0;
word lastState = 0;

Joystick_ Joystick;

void setup()
{
  Joystick.begin();
  Serial.begin(9600);
}

void loop()
{
  // Get the current state of the controller
  currentState = controller.getState();
  // Print the state to the serial monitor
  printState();
  // Update the PC joystick buttons states
  updateButtons();
  // Save the current state as the last one, for the following loops
  lastState = currentState;
}

// If the controller has changed it's state, print the current state of all the buttons
void printState()
{
  if (currentState != lastState)
  {
    Serial.print((currentState & SC_CTL_ON) ? "+" : "-");
    Serial.print((currentState & SC_BTN_UP) ? "U" : "0");
    Serial.print((currentState & SC_BTN_DOWN) ? "D" : "0");
    Serial.print((currentState & SC_BTN_LEFT) ? "L" : "0");
    Serial.print((currentState & SC_BTN_RIGHT) ? "R" : "0");
    Serial.print((currentState & SC_BTN_START) ? "S" : "0");
    Serial.print((currentState & SC_BTN_A) ? "A" : "0");
    Serial.print((currentState & SC_BTN_B) ? "B" : "0");
    Serial.print((currentState & SC_BTN_C) ? "C" : "0");
    Serial.print((currentState & SC_BTN_X) ? "X" : "0");
    Serial.print((currentState & SC_BTN_Y) ? "Y" : "0");
    Serial.print((currentState & SC_BTN_Z) ? "Z" : "0");
    Serial.print((currentState & SC_BTN_MODE) ? "M" : "0");

    Serial.print("\n");
  }
}

// Press or release the corresponding buttons when the controller state has changed
void updateButtons()
{
  // Loop over the buttons map
  for (byte i = 0; i < BUTTONS; i++)
  {
    // Check if the button is pressed in the last or current state
    word last = (lastState & buttonsMap[i].controllerButton);
    word current = (currentState & buttonsMap[i].controllerButton);

    // If the button has changed it's state between the last and the current one, press or release it accordingly
    if (last != current)
    {
      if (current)
      {
        Joystick.pressButton(buttonsMap[i].joystickButton);
      }
      else
      {
        Joystick.releaseButton(buttonsMap[i].joystickButton);
      }
    }
  }
}
