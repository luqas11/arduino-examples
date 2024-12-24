#include <IRremote.h>

const int IR_RECEIVER_PIN = 8;

void setup()
{
  Serial.begin(115200);

  // Start the receiver, and enable the built it led to give feedback when receiving signals
  IrReceiver.begin(IR_RECEIVER_PIN, ENABLE_LED_FEEDBACK);
}

void loop()
{
  // Try to read any signal and decode it
  if (IrReceiver.decode())
  {
    // If the protocol cannot be identified, print an error message
    if (IrReceiver.decodedIRData.protocol == UNKNOWN)
    {
      Serial.println("Received noise or an unknown protocol");
    }
    // If the protocol can be identified, print the received command
    else
    {
      Serial.println();
      Serial.println("Received command:");
      Serial.println(IrReceiver.decodedIRData.command);
    }

    // Enable the receiver to read the next signal
    IrReceiver.resume();
  }
}
