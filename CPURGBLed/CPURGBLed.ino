// The pins where the R, G and B components of the RGB LED are connected
const int LED_PINS[] = { 11, 10, 9 };
// The chat offset defined in the CPULoadReader for the outcoming characters
const char CHAR_OFFSET = ' ';
// The speed at which the color will change after receiving a value (inversely defined, e.g. a lower value will increase the speed)
const int SPEED_FACTOR = 40;

int currentValue = 1;
float mean = 1;

void setup() {
  // Initialize serial communication and LED outputs
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  // Read the serial port until a character is received
  while (Serial.available() > 0) {
    char receivedChar = Serial.read();
    // Apply a correction to the received character, based on the given offset
    currentValue = (receivedChar - CHAR_OFFSET) * 2;
  }

  // Get a mean value between the received and the stored one, using the speed factor to weight them
  mean = ((mean * (SPEED_FACTOR - 1) + currentValue) / SPEED_FACTOR);

  // Print the current values
  Serial.println();
  Serial.println("Mean: " + (String)mean);
  Serial.println("Current: " + (String)currentValue);

  // Set the RGB outputs to the corresponding values
  float valueR = map(mean, 0, 100, 0, 255);
  analogWrite(LED_PINS[0], valueR);
  float valueG = map(100 - mean, 0, 100, 0, 255);
  analogWrite(LED_PINS[1], valueG);
  float valueB = map(100 - mean, 0, 100, 0, 255);
  analogWrite(LED_PINS[2], valueB);

  // Wait some time to avoid excessive prints to the serial monitor
  delay(50);
}
