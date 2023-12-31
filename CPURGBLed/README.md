# CPURGBLed

Sets the color of an **RGB LED** based on the **CPU** current load percentage. If the load is low, the color will be blue, and if the load is high, it will be red, transitioning smoothly between intermediate values. The **CPU** load value is sent from a **C#** simple app, which runs from terminal and asks to the user the Arduino's **COM** port at startup. The load value is sent as a single printable **ASCII** character, representing a number between `0` and `100`. The Arduino sketch will intepret that character and convert it to a number between `0` and `255`, to write that value to analog outputs. 

Requires an **RGB LED** connected to PWM-capable pins.
