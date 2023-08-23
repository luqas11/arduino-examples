// To compile this .cs file into and .exe file, use an installation of Microsoft.NET.
// In my case:
// C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe CSDataSender.cs
using System;
using System.IO;
using System.IO.Ports;
using System.Threading;

namespace CPULoadReader {
  class Program {
    static SerialPort ArduinoPort;
    // The baud rate of the Arduino's serial communication
    const int BAUD_RATE = 9600;
    // The delay between value sendings
    const int DELAY_TIME_MS = 300;
    // The name of the file where the value is stored
    const String FILENAME = "value.txt";

    static void Main(String[] args) {
      // Initialize the program and ask to input the COM port
      Console.Title = "CS Data Sender";
      Console.WriteLine("----------------------");
      Console.WriteLine("Starting CS Data Sender");
      Console.WriteLine("----------------------\n");
      connectToCOM();
    }

    // Ask to input the COM port number and try to connect to the Arduino
    static void connectToCOM() {
      Console.WriteLine("Write the COM port number where the Arduino is connected and press ENTER:");
      // Read user input
      String comPortNumber = Console.ReadLine();

      // Try to connect to Arduino through the given port
      try {
        ArduinoPort = new SerialPort();
        ArduinoPort.PortName = "COM" + comPortNumber;
        ArduinoPort.BaudRate = BAUD_RATE;
        ArduinoPort.Open();
      // If error, ask the user to retry
      } catch {
        Console.WriteLine("\n----------------------");
        Console.WriteLine("Invalid COM port number, check the connection to the Arduino and try again.");
        Console.WriteLine("----------------------\n");
        connectToCOM();
        return;
      }

      Console.WriteLine("\n----------------------");
      Console.WriteLine("Connected");
      Console.WriteLine("----------------------");

      // When connection is successful, start reading values from the file and sending it to the Arduino
      sendValue();
    }

    // Read the value from the file and sent it to the Arduino
    static void sendValue() {
      // Try to get the current value and send it
      try {
			  String value = File.ReadAllText(FILENAME);
			  if (!string.IsNullOrEmpty(value)) {
			    Console.WriteLine("Current value: " + value);
          ArduinoPort.Write(value + "x");
			  }
      // If any error occurs, show an error message
      } catch {
        Console.WriteLine("Unable to send the current value.");
      }

      // Repeat all the process indefinetly, waiting a given time between repetitions
      Thread.Sleep(DELAY_TIME_MS);
      sendValue();
    }
  }
}
