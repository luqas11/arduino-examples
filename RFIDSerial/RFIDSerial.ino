// For pin layout, refer to the "Typical pin layout" at any MFRC522 library example sketch.

#include <SPI.h>
#include <MFRC522.h>

const int RST_PIN = 9;
const int SS_PIN = 10;

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  // Initialize serial monitor, MFRC522 chip and SIP communication
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  // Reset the loop if no new card present
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the present cards, and try to communicate with it
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Print card info
  Serial.println("Card data:");
  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));
  Serial.println();

  // Set the card to HALT state, to prevent further readings until it's removed
  mfrc522.PICC_HaltA();
}
