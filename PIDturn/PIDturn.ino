#include <Servo.h> //Need for Servo pulse output
#include <SoftwareSerial.h>

// #define NO_READ_GYRO  //Uncomment of GYRO is not attached.
// #define NO_HC-SR04 //Uncomment of HC-SR04 ultrasonic ranging sensor is not attached.
// #define NO_BATTERY_V_OK //Uncomment of BATTERY_V_OK if you do not care about battery damage.

// State machine states
enum STATE
{
  INITIALISING,
  RUNNING,
  STOPPED
};

#define BLUETOOTH_RX 10
// Serial Data output pin
#define BLUETOOTH_TX 11

SoftwareSerial BluetoothSerial(BLUETOOTH_RX, BLUETOOTH_TX);

// Refer to Shield Pinouts.jpg for pin locations

// Default motor control pins
const byte left_front = 46;
const byte left_rear = 47;
const byte right_rear = 50;
const byte right_front = 51;

// Default ultrasonic ranging sensor pins, these pins are defined my the Shield
const int TRIG_PIN = 48;
const int ECHO_PIN = 49;

// Default IR sensor pins, these pins are defined by the Shield
#define IR_41_01 12
#define IR_41_02 13
#define IR_41_03 13
// #define IR_2Y_01 14
#define IR_2Y_02 14
// uncomment if these IR sensors are used
//  #define IR_2Y_03 14
#define IR_2Y_04 15

// Anything over 400 cm (23200 us pulse) is "out of range". Hit:If you decrease to this the ranging sensor but the timeout is short, you may not need to read up to 4meters.
const unsigned int MAX_DIST = 23200;

Servo left_font_motor;  // create servo object to control Vex Motor Controller 29
Servo left_rear_motor;  // create servo object to control Vex Motor Controller 29
Servo right_rear_motor; // create servo object to control Vex Motor Controller 29
Servo right_font_motor; // create servo object to control Vex Motor Controller 29
Servo turret_motor;

int speed_val = 300;
int speed_change;

// gyro
int sensorPin = A2;            // define the pin that gyro is connected
int sensorValue = 0;           // read out value of sensor
float gyroSupplyVoltage = 5;   // supply voltage for gyro
float gyroZeroVoltage = 0;     // the value of voltage when gyro is zero
float gyroSensitivity = 0.007; // gyro sensitivity unit is (mv/degree/second) get from datasheet
float rotationThreshold = 1.5; // because of gyro drifting, defining rotation angular velocity less than
// this value will not be ignored
float gyroRate = 0;     // read out value of sensor in voltage
float currentAngle = 0; // current angle calculated by angular velocity integral on

// statemachine
int currentState = 1;

// Serial Pointer
HardwareSerial *SerialCom;

int pos = 0;

int i;
float sum = 0;




void setup() {
  // put your setup code here, to run once:
  turret_motor.attach(11);
  pinMode(LED_BUILTIN, OUTPUT);

  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  // Setup the Serial port and pointer, the pointer allows switching the debug info through the USB port(Serial) or Bluetooth port(Serial1) with ease.
  SerialCom = &Serial;
  SerialCom->begin(115200);
  SerialCom->println("MECHENG706_Base_Code_25/01/2018");

  BluetoothSerial.begin(115200);

  delay(1000);
  SerialCom->println("Setup....");

  Serial.println("please keep the sensor still for calibration");
  Serial.println("get the gyro zero voltage");
  for (i = 0; i < 100; i++) // read 100 values of voltage when gyro is at still, to calculate the zero-drift
  {
    sensorValue = analogRead(sensorPin);
    sum += sensorValue;
    delay(5);
  }
  gyroZeroVoltage = sum / 100; // average the sum as the zero drifting
}

void loop() {
  // put your main code here, to run repeatedly:
  stateMachine(currentState);
}

float HC_SR04_range()
{
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float inches;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  t1 = micros();
  while (digitalRead(ECHO_PIN) == 0)
  {
    t2 = micros();
    pulse_width = t2 - t1;
    if (pulse_width > (MAX_DIST + 1000))
    {
      SerialCom->println("HC-SR04: NOT found");
      return;
    }
  }

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min

  t1 = micros();
  while (digitalRead(ECHO_PIN) == 1)
  {
    t2 = micros();
    pulse_width = t2 - t1;
    if (pulse_width > (MAX_DIST + 1000))
    {
      SerialCom->println("HC-SR04: Out of range");
      return;
    }
  }

  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed
  // of sound in air at sea level (~340 m/s).
  cm = pulse_width / 58.0;
  inches = pulse_width / 148.0;

  // Print out results
  if (pulse_width > MAX_DIST)
  {
    SerialCom->println("HC-SR04: Out of range");
  }
  else
  {
    SerialCom->print("HC-SR04:");
    SerialCom->print(cm);
    SerialCom->println("cm");
  }

  return cm;
}

float GyroTimePrevious = 0.0;
float GyroTimeNow = 0.0;

void readGyro1()
{
  GyroTimeNow = (float)millis() / 1000;

  gyroRate = (analogRead(sensorPin) * gyroSupplyVoltage) / 1023; // find the voltage offset the value of voltage when gyro is zero (still)

  gyroRate -= (gyroZeroVoltage / 1023 * 5);

  float angularVelocity = gyroRate / gyroSensitivity; // read out voltage divided the gyro sensitivity to calculate the angular velocity

  // if the angular velocity is less than the threshold, ignore it
  if (angularVelocity >= rotationThreshold || angularVelocity <= -rotationThreshold)
  {
    // we are running a loop in T. one second will run (1000/T).
    float angleChange = -angularVelocity * (GyroTimeNow - GyroTimePrevious);
    currentAngle += angleChange;
  }

  GyroTimePrevious = GyroTimeNow;
}

int SVRF = 0;
int SVRR = 0;
int SVLF = 0;
int SVLR = 0;

int Kp = 1000;
int SV_P = 0;

float TargetAngle_Radius = 0.0;
float ErrorAngle_Radius = 0.0; // TargetAngle - CurrentAngle
float torlance = 10.0;         // degree

void MoveStraightAlongAngle(float TargetAngle_Degree, float Power)
{
  SVRF = (int)300 * (Power / 100);
  SVRR = SVRF;
  SVLF = SVRF;
  SVLR = SVRF;

  TargetAngle_Radius = 2 * 3.1415926 * TargetAngle_Degree / (float)360.0;
  ///(float)360

  SVRR = SVRR * (cos(TargetAngle_Radius) - sin(TargetAngle_Radius));
  SVRF = SVRF * (cos(TargetAngle_Radius) + sin(TargetAngle_Radius));
  SVLF = -SVLF * (cos(TargetAngle_Radius) - sin(TargetAngle_Radius));
  SVLR = -SVLR * (cos(TargetAngle_Radius) + sin(TargetAngle_Radius));

  readGyro1();
  ErrorAngle_Radius = TargetAngle_Radius - (2 * 3.1415926 * currentAngle / 360 + TargetAngle_Radius);
  SV_P = -Kp * ErrorAngle_Radius;

  SVRF += SV_P;
  SVRR += SV_P;
  SVLF += SV_P;
  SVLR += SV_P;

  SVRF = saturation(SVRF);
  SVRR = saturation(SVRR);
  SVLF = saturation(SVLF);
  SVLR = saturation(SVLR);

  left_font_motor.writeMicroseconds(1500 + SVLF);
  left_rear_motor.writeMicroseconds(1500 + SVLR);
  right_rear_motor.writeMicroseconds(1500 + SVRR);
  right_font_motor.writeMicroseconds(1500 + SVRF);

  // Serial.print(currentAngle);
  // Serial.print(" ");
  // Serial.print(TargetAngle_Radius);
  // Serial.print(" ");
  // Serial.print(ErrorAngle_Radius);
  // Serial.print(" ");
  // Serial.print(SV_P);
  // Serial.print(" ");
  // Serial.print(SVRR);
  // Serial.print(" ");
  // Serial.print(SVRF);
  // Serial.print(" ");
  // Serial.print(SVLF);
  // Serial.print(" ");
  // Serial.println(SVLR);

  delay(20);
}

void trunDegree(float TargetAngle_Degree)
{
  float Power = 100;
  float torlance = 0.5;
  while ((currentAngle < TargetAngle_Degree - torlance) || (currentAngle > TargetAngle_Degree + torlance))
  {
    SVRF = (int)300 * (Power / 100);
    SVRR = SVRF;
    SVLF = SVRF;
    SVLR = SVRF;

    TargetAngle_Radius = 2 * 3.1415926 * TargetAngle_Degree / 360;

    SVLF = -SVLF * ((cos(TargetAngle_Radius - sin(TargetAngle_Radius))));
    SVLR = -SVLR * ((cos(TargetAngle_Radius) + sin(TargetAngle_Radius)));
    SVRR = SVRR * ((cos(TargetAngle_Radius - sin(TargetAngle_Radius))));
    SVRF = SVRF * ((cos(TargetAngle_Radius) + sin(TargetAngle_Radius)));

    readGyro1();
    SerialCom->println(currentAngle);
    ErrorAngle_Radius = TargetAngle_Radius - 2 * 3.1415926 * currentAngle / 360;
    SV_P = -Kp * ErrorAngle_Radius;

    SVRF += SV_P;
    SVRR += SV_P;
    SVLF += SV_P;
    SVLR += SV_P;

    SVRF = saturation(SVRF);
    SVRR = saturation(SVRR);
    SVLF = saturation(SVLF);
    SVLR = saturation(SVLR);

    left_font_motor.writeMicroseconds(1500 + SVLR);
    left_rear_motor.writeMicroseconds(1500 + SVLF);
    right_rear_motor.writeMicroseconds(1500 + SVRR);
    right_font_motor.writeMicroseconds(1500 + SVRF);

    delay(20);
  }
  currentState++;
  //stop
}

int saturation(int value)
{
  if (value > 500)
  {
    return 500;
  }
  else if (value < -500)
  {
    return -500;
  }
  else
  {
    return value;
  }
}

void driveStrightUntilDistance(int cm)
{
  readGyro1();
  float target = currentAngle;
  while (HC_SR04_range() > cm)
  {
    MoveStraightAlongAngle(target, 100);
  }
  currentState++;
  SerialCom->println("stop");
}

void driveStringhtForDistance(int cm)
{
  readGyro1();
  float target = currentAngle;
  float torlance = 3; // degree
  float currentDistance = HC_SR04_range();

  while (HC_SR04_range() > (currentDistance - cm))
  {
    MoveStraightAlongAngle(target, 100);
  }
  currentState++;
  SerialCom->println("stop");
}

void turnAngleWithGyro(float angle, float millisecond)
{
  readGyro1();
  float target = currentAngle + angle;
  float torlance = 10; // degree
  unsigned long timeAtDestination = millis() + millisecond;

  while (millis() < timeAtDestination)
  {
    readGyro1();
    SerialCom->print(currentAngle);
    SerialCom->print(" ");

    if ((currentAngle < (torlance + target)) && (currentAngle > (-torlance + target)))
    {

      SerialCom->println("forward");
    }
    else if ((currentAngle > (torlance + target)) && (currentAngle < (180 + target)))
    {

      SerialCom->println("ccw");
    }
    else
    {

      SerialCom->println("cw");
    }

    delay(40);
  }
}

void stateMachine(int adress)
{
  
  switch (adress)
  {
  case 1:
    driveStrightUntilDistance(35);
    SerialCom->println("1");
    break;
  case 2:
    trunDegree(90);
    SerialCom->println("2");
    break;
  case 3:
    driveStringhtForDistance(35);
    SerialCom->println("3");
    break;
  case 4:
    trunDegree(180);
    SerialCom->println(currentState);
    break;
  case 5:
    driveStrightUntilDistance(35);
    SerialCom->println(currentState);
    break;
  case 6:
    trunDegree(270);
    SerialCom->println(currentState);
    break;
  case 7:
    currentState = 1;
  }
}