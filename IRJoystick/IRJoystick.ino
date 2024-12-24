#include <Joystick.h>
#include <IRremote.h>

// Mappings between the IR commands and the Joystick buttons
const int buttons[] = { 0, 1, 2 };
const int commands[] = { 4, 5, 6 };

const int IR_RECEIVER_PIN = 8;
const int DEBOUNCE_TIME = 125;

int currentCommand = -1;
long lastSignalTime;

Joystick_ Joystick;

void setup() {
  Serial.begin(9600);
  Joystick.begin();
  //  Start the receiver, and enable the built it led to give feedback when receiving signals
  IrReceiver.begin(IR_RECEIVER_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  // Try to read any signal and decode it
  if (IrReceiver.decode()) {
    // Check if the received signal uses a known protocol
    if (IrReceiver.decodedIRData.protocol != UNKNOWN) {
      // Get the received command
      int newCommand = IrReceiver.decodedIRData.command;

      // If the debounce time from the last processed command has passed, process a new one
      if (lastSignalTime < (millis() - DEBOUNCE_TIME)) {
        // Find the corresponding buttons mapped to the last and current commando, and release and press them respectively
        for (int i = 0; i < int(sizeof(commands) / 2); i++) {
          if (commands[i] == currentCommand) {
            Joystick.releaseButton(buttons[i]);
            Serial.println("Release " + String(buttons[i]) + " button");
          }
          if (commands[i] == newCommand) {
            Joystick.pressButton(buttons[i]);
            Serial.println("Press " + String(buttons[i]) + " button");
          }
        }

        currentCommand = newCommand;
        lastSignalTime = millis();
      } else {
        // If the debounce time from the last processed command hasn't passed but the new command is the same, update the debounce timer
        if (newCommand == currentCommand) {
          lastSignalTime = millis();
        }
      }
    }
    IrReceiver.resume();
  }

  // Besides the decoding process, if the debounce time has passed release the button
  if (lastSignalTime < (millis() - DEBOUNCE_TIME)) {
    for (int i = 0; i < int(sizeof(commands) / 2); i++) {
      if (commands[i] == currentCommand) {
        Joystick.releaseButton(buttons[i]);
        Serial.println("Release " + String(buttons[i]) + " button");
        Serial.println();
        currentCommand = -1;
      }
    }
  }
}
