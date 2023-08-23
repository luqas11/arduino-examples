// To compile this .cs file into and .exe file, use an installation of Microsoft.NET.
// In my case:
// C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe CPULoadReader.cs
using System;
using System.Management;
using System.IO.Ports;
using System.Threading;

namespace CPULoadReader {
  class Program {
    static SerialPort ArduinoPort;
    // The baud rate of the Arduino's serial communication
    const int BAUD_RATE = 9600;
    // The delay between CPU load readings
    const int DELAY_TIME_MS = 100;
    // A char offset to prevent the terminal from printing non-printable characters (space is the first printable character of the ASCII table)
    const char CHAR_OFFSET = ' ';

    static void Main(String[] args) {
      // Initialize the program and ask to input the COM port
      Console.Title = "CPU Load Reader";
      Console.WriteLine("----------------------");
      Console.WriteLine("Starting CPU Load Reader");
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

      // When connection is successful, start sending CPU Load values
      sendCPULoadValue();
    }

    // Send CPU load values to the Arduino indefinetly
    static void sendCPULoadValue() {
      ManagementObjectSearcher searcher = new ManagementObjectSearcher("root\\CIMV2", "SELECT * FROM Win32_Processor");

      // Try to get the current CPU load value and send it to the Arduino
      try {
        foreach(ManagementObject obj in searcher.Get()) {
          // Get the load value as an int, between 0 and 100
          int intValue = int.Parse(obj["LoadPercentage"].ToString());
          // Divide the int by two and cast it to a char, to be able to send the value in a single byte
          char charValue = (char) (intValue / 2);
          // Add an offset to prevent the console to print non-printable characters
          charValue += CHAR_OFFSET;
          // Print the read values to the terminal
          Console.WriteLine("\nCurrent value:");
          Console.WriteLine("As int: " + intValue);
          Console.WriteLine("As char: " + charValue);
          // Send the char through the COM port
          ArduinoPort.Write(charValue.ToString());
        }
      // If any error occurs, show an error message
      } catch {
        Console.WriteLine("Unable to read the current CPU load value.");
      }

      // Repeat all the process indefinetly, waiting a given time between repetitions
      Thread.Sleep(DELAY_TIME_MS);
      sendCPULoadValue();
    }
  }
}
