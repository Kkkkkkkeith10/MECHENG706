// Author: Marshall Lim

#include <SoftwareSerial.h>

#define INTERNAL_LED 13

// Serial Data input pin
#define BLUETOOTH_RX 10
// Serial Data output pin
#define BLUETOOTH_TX 11

#define STARTUP_DELAY 10 // Seconds
#define LOOP_DELAY 10 // miliseconds
#define SAMPLE_DELAY 10 // miliseconds


// USB Serial Port
#define OUTPUTMONITOR 0
#define OUTPUTPLOTTER 0

// Bluetooth Serial Port
#define OUTPUTBLUETOOTHMONITOR 1

volatile int32_t Counter = 1;

SoftwareSerial BluetoothSerial(BLUETOOTH_RX, BLUETOOTH_TX);

void delaySeconds(int TimedDelaySeconds)
{
  for (int i = 0; i < TimedDelaySeconds; i++)
  {
    delay(1000);
  }
}

void flashLED(int LedNumber, int TimedDelay)
{
  digitalWrite(LedNumber, HIGH);
  delaySeconds(TimedDelay);
  digitalWrite(LedNumber, LOW);
  delaySeconds(TimedDelay);
}

void serialOutputMonitor(int32_t Value1, int32_t Value2, int32_t Value3)
{
  String Delimiter = ", ";
  
  Serial.print(Value1, DEC);
  Serial.print(Delimiter);
  Serial.print(Value2, DEC);
  Serial.print(Delimiter);
  Serial.println(Value3, DEC);
}

void serialOutputPlotter(int32_t Value1, int32_t Value2, int32_t Value3)
{
  String Delimiter = ", ";
  
  Serial.print(Value1, DEC);
  Serial.print(Delimiter);
  Serial.print(Value2, DEC);
  Serial.print(Delimiter);
  Serial.println(Value3, DEC);
}

void bluetoothSerialOutputMonitor(int32_t Value1, int32_t Value2, int32_t Value3)
{
  String Delimiter = ", ";
  
  BluetoothSerial.print(Value1, DEC);
  BluetoothSerial.print(Delimiter);
  BluetoothSerial.print(Value2, DEC);
  BluetoothSerial.print(Delimiter);
  BluetoothSerial.println(Value3, DEC);
}

void serialOutput(int32_t Value1, int32_t Value2, int32_t Value3)
{
  if (OUTPUTMONITOR)
  {
    serialOutputMonitor(Value1, Value2, Value3);
  }

  if (OUTPUTPLOTTER)
  {
    serialOutputPlotter(Value1, Value2, Value3);
  }

  if (OUTPUTBLUETOOTHMONITOR)
  {
    bluetoothSerialOutputMonitor(Value1, Value2, Value3);;
  }
}

void setup()
{  
  pinMode(INTERNAL_LED, OUTPUT);

  Serial.begin(115200);

  BluetoothSerial.begin(115200);

  Serial.print("Ready, waiting for ");
  Serial.print(STARTUP_DELAY, DEC);
  Serial.println(" seconds");

  delaySeconds(STARTUP_DELAY);
}

void loop()
{
//  flashLED(INTERNAL_LED, 1);
//  delaySeconds(1);
  delay(LOOP_DELAY);

  delay(SAMPLE_DELAY);
  if (BluetoothSerial.available() > 0)
  {
    BluetoothSerial.write(BluetoothSerial.read());
  }
  // BluetoothSerial.write("A");


}
