# RFIDPowerDown

Example to test the soft power down mode of the **MFRC522** module with an external button. When the button is released, the module can read **RFID** card **IDs** and print them to the serial monitor, and when the button is pressed, the module enters in the soft power down mode, highly reducing it's power consumption.  

The **SPI** and **MFRC522** libraries enables the communication and management of the module, respectively. Requires an **MFRC522** module and a physical button connected to the given input and output pins.
