# CSArduinoCommunication

Example of communication between a **C#** script and Arduino. The script reads a numeric value from a textfile, sends it to the serial port, and the Arduino receives it and turns on **LEDs** depending on it's value. The value must be a number between `0` and a specified max number, and the **LEDs** must be connected to contiguous pins. Both values must be set in the sketch, along with the **LEDs** number, and it will automatically define the limits between each **LED** will be on (each **LED** will be on when the value is over some different threshold, to make easy to identify if the value is being received properly).  

Requires some **LEDs** connected to contiguous pins and a textfile named `value.txt` to be in the same directory as the **C#** script, with a single line with a number written on it.
