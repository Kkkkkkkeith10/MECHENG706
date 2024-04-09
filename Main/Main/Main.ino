/*
  MechEng 706 Base Code
  This code provides basic movement and sensor reading for the MechEng 706 Mecanum Wheel Robot Project
  Hardware:
    Arduino Mega2560 https://www.arduino.cc/en/Guide/ArduinoMega2560
    MPU-9250 https://www.sparkfun.com/products/13762
    Ultrasonic Sensor - HC-SR04 https://www.sparkfun.com/products/13959
    Infrared Proximity Sensor - Sharp https://www.sparkfun.com/products/242
    Infrared Proximity Sensor Short Range - Sharp https://www.sparkfun.com/products/12728
    Servo - Generic (Sub-Micro Size) https://www.sparkfun.com/products/9065
    Vex Motor Controller 29 https://www.vexrobotics.com/276-2193.html
    Vex Motors https://www.vexrobotics.com/motors.html
    Turnigy nano-tech 2200mah 2S https://hobbyking.com/en_us/turnigy-nano-tech-2200mah-2s-25-50c-lipo-pack.html
  Date: 11/11/2016
  Author: Logan Stuart
  Modified: 15/02/2018
  Author: Logan Stuart
*/
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
#define IR_41_02 A8
#define IR_41_03 A10
// #define IR_2Y_01 14
#define IR_2Y_02 A11
// uncomment if these IR sensors are used
//  #define IR_2Y_03 14
#define IR_2Y_04 A9

//Prototype functions
void resetGyro();
void homing_normal_system(bool use_Gyro, bool use_sonar, bool use_left_side_IRs, bool use_right_side_IRs, float tolarence);
void findCorner();
void move_along_wall(bool use_Gyro, bool use_sonar, bool use_left_side_IRs, bool use_right_side_IRs, float tolarence);
void homeStateMachine(int adress);
void checkForLongSide();
void ccw_low();
void cw_low();
void MoveStraightPID(float Power);
void stateMachine(int adress);
void turnAngleWithGyro(float angle, float millisecond);
void driveStrightUntilDistance(int cm);
void driveStringhtForDistance(int cm);
void MoveStraightAlongAngle(float TargetAngle_Degree, float Power);
int saturation(int value);
void readGyro();
void readGyro1();
void disable_motors();
void enable_motors();
void stop();
void forward();
void reverse();
void ccw();
void cw();
void strafe_left();
void strafe_right();
void trunDegree(float TargetAngle_Degree );
void Car_Move_withIRSensor(String left_front_IR, String left_back_IR, String right_front_IR, String right_back_IR);
double IR_sensorReadDistance(String sensor);
void interpret_command(char command);
float HC_SR04_range();




// Anything over 400 cm (23200 us pulse) is "out of range". Hit:If you decrease to this the ranging sensor but the timeout is short, you may not need to read up to 4meters.
const unsigned int MAX_DIST = 23200;

Servo left_font_motor;  // create servo object to control Vex Motor Controller 29
Servo left_rear_motor;  // create servo object to control Vex Motor Controller 29
Servo right_rear_motor; // create servo object to control Vex Motor Controller 29
Servo right_font_motor; // create servo object to control Vex Motor Controller 29
Servo turret_motor;

//Speed and motor movement
int speed_val = 500;
int speed_change;
int speed_val_low = 100;

//PID
int KP = 100;
float ErrorAngle_Degree = 0.0;
float offset_angle = -0.1;


int SVRF = 0;
int SVRR = 0;
int SVLF = 0;
int SVLR = 0;

int Kp = 1000;
int SV_P = 0;

float TargetAngle_Radius = 0.0;
float ErrorAngle_Radius = 0.0; // TargetAngle - CurrentAngle
float torlance = 10.0;         // degree


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
float GyroTimePrevious = 0.0;
float GyroTimeNow = 0.0;


// statemachine
int currentState = 0;

//IR Readings
float temp_4102 = 0.0;
float temp_4103 = 0.0;
float temp_2Y02 = 0.0;
float temp_2Y04 = 0.0;

// Serial Pointer
HardwareSerial *SerialCom;

int pos = 0;

int i;
float sum = 0;





void setup(void)
{
  turret_motor.attach(11);
  pinMode(LED_BUILTIN, OUTPUT);

  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  BluetoothSerial.begin(115200);


  // // setting up gyro

  // pinMode(sensorPin, INPUT);
  // Serial.println("please keep the sensor still for calibration");
  // Serial.println("get the gyro zero voltage");
  // for (i = 0; i < 100; i++) // read 100 values of voltage when gyro is at still, to calculate the zero-drift
  // {
  //   sensorValue = analogRead(sensorPin);
  //   sum += sensorValue;
  //   delay(5);
  // }
  // gyroZeroVoltage = sum / 100; // average the sum as the zero drifting

  delay(1000); // settling time but no really needed
}

void loop(void) // main loop
{
  static STATE machine_state = INITIALISING;
  // Finite-state machine Code
  switch (machine_state)
  {
  case INITIALISING:
    machine_state = initialising();
    break;
  case RUNNING: // Lipo Battery Volage OK
                // machine_state =  running();
                // BluetoothSerial.println(String(currentAngle));
                // BluetoothSerial.print(String(currentAngle));
                // BluetoothSerial.print("\n");

    // driveStrightWithGyro(6000);
    // delay(5);
    // break; 
  //    if (millis() - previous_millis > 200) //only send every 200ms
  // {
  //   previous_millis = millis();
  //   char message[8];
  //   dtostrf(currentAngle,6,2,message);
  //   BluetoothSerial.println(message);
  //   //Serial.println(message);
  //   // Serial.print(" : ");
  //   // Serial.println(time);
  // }

  // if (BluetoothSerial.available() > 0)
  // {
  //   command = BluetoothSerial.read();
  //   BluetoothSerial.println(command);
  //   interpret_command(command);

  // }
  // while(true)
  // {
  //   //MoveStraightAlongAngle(0,100);
  //   stateMachine(currentState);
  // }
  while(true){
    if(currentState<=8){
      homeStateMachine(currentState);
    }
    else{
      stateMachine(currentState);
    }
    
  }
  break;
  

    // stateMachine(currentState);
    // break;

  case STOPPED: // Stop of Lipo Battery voltage is too low, to protect Battery
    machine_state = stopped();
    break;
  };
}

STATE initialising()
{
  // initialising
  BluetoothSerial.println("INITIALISING....");
  // delay(1000); // One second delay to see the serial String "INITIALISING...."
  BluetoothSerial.println("Enabling Motors...");
  enable_motors();
  BluetoothSerial.println("RUNNING STATE...");

  // setting up gyro
  // int i;
  // float sum = 0;
  // pinMode(sensorPin, INPUT);
  Serial.println("please keep the sensor still for calibration");
  Serial.println("get the gyro zero voltage");
  for (i = 0; i < 100; i++) // read 100 values of voltage when gyro is at still, to calculate the zero-drift
  {
    sensorValue = analogRead(sensorPin);
    sum += sensorValue;
    delay(5);
  }
  gyroZeroVoltage = sum / 100; // average the sum as the zero drifting

  return RUNNING;
}

STATE running()
{
  // // read_serial_command();
  // fast_flash_double_LED_builtin();

  //check battery is ok
  #ifndef NO_BATTERY_V_OK
    if (!is_battery_voltage_OK())
      return STOPPED;
  #endif

//get sensor readings using timed statement
  static unsigned long previous_millis;
  if (millis() - previous_millis > 500)
  { // Arduino style 500ms timed execution statement
    previous_millis = millis();

    #ifndef NO_READ_GYRO
    //read gyro here
    //GYRO_reading();
    #endif

    #ifndef NO_HC - SR04
        HC_SR04_range(); //sonar read
    #endif

    //BluetoothSerial.println("RUNNING---------");
    //speed_change_smooth();
    //Analog_Range_A4();
  }

  //   turret_motor.write(pos);

  //   if (pos == 0)
  //   {
  //     pos = 45;
  //   }
  //   else
  //   {
  //     pos = 0;
  //   }
  // }

  return RUNNING;
}

// Stop of Lipo Battery voltage is too low, to protect Battery
STATE stopped()
{
  static byte counter_lipo_voltage_ok;
  static unsigned long previous_millis;
  int Lipo_level_cal;
  disable_motors();
  slow_flash_LED_builtin();

  if (millis() - previous_millis > 500)
  { // print massage every 500ms
    previous_millis = millis();
    BluetoothSerial.println("STOPPED---------");

#ifndef NO_BATTERY_V_OK
    // 500ms timed if statement to check lipo and output speed settings
    if (is_battery_voltage_OK())
    {
      BluetoothSerial.print("Lipo OK waiting of voltage Counter 10 < ");
      BluetoothSerial.println(counter_lipo_voltage_ok);
      counter_lipo_voltage_ok++;
      if (counter_lipo_voltage_ok > 10)
      { // Making sure lipo voltage is stable
        counter_lipo_voltage_ok = 0;
        enable_motors();
        BluetoothSerial.println("Lipo OK returning to RUN STATE");
        return RUNNING;
      }
    }
    else
    {
      counter_lipo_voltage_ok = 0;
    }
#endif
  }
  return STOPPED;
}

void fast_flash_double_LED_builtin()
{
  static byte indexer = 0;
  static unsigned long fast_flash_millis;
  if (millis() > fast_flash_millis)
  {
    indexer++;
    if (indexer > 4)
    {
      fast_flash_millis = millis() + 700;
      digitalWrite(LED_BUILTIN, LOW);
      indexer = 0;
    }
    else
    {
      fast_flash_millis = millis() + 100;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
  }
}

void slow_flash_LED_builtin()
{
  static unsigned long slow_flash_millis;
  if (millis() - slow_flash_millis > 2000)
  {
    slow_flash_millis = millis();
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}

void speed_change_smooth()
{
  speed_val += speed_change;
  if (speed_val > 1000)
    speed_val = 1000;
  speed_change = 0;
}

#ifndef NO_BATTERY_V_OK
boolean is_battery_voltage_OK()
{
  static byte Low_voltage_counter;
  static unsigned long previous_millis;

  int Lipo_level_cal;
  int raw_lipo;
  // the voltage of a LiPo cell depends on its chemistry and varies from about 3.5V (discharged) = 717(3.5V Min) https://oscarliang.com/lipo-battery-guide/
  // to about 4.20-4.25V (fully charged) = 860(4.2V Max)
  // Lipo Cell voltage should never go below 3V, So 3.5V is a safety factor.
  raw_lipo = analogRead(A0);
  Lipo_level_cal = (raw_lipo - 717);
  Lipo_level_cal = Lipo_level_cal * 100;
  Lipo_level_cal = Lipo_level_cal / 143;

  if (Lipo_level_cal > 0 && Lipo_level_cal < 160)
  {
    previous_millis = millis();
    BluetoothSerial.print("Lipo level:");
    BluetoothSerial.print(Lipo_level_cal);
    BluetoothSerial.print("%");
    // BluetoothSerial.print(" : Raw Lipo:");
    // BluetoothSerial.println(raw_lipo);
    BluetoothSerial.println("");
    Low_voltage_counter = 0;
    return true;
  }
  else
  {
    if (Lipo_level_cal < 0)
      BluetoothSerial.println("Lipo is Disconnected or Power Switch is turned OFF!!!");
    else if (Lipo_level_cal > 160)
      BluetoothSerial.println("!Lipo is Overchanged!!!");
    else
    {
      BluetoothSerial.println("Lipo voltage too LOW, any lower and the lipo with be damaged");
      BluetoothSerial.print("Please Re-charge Lipo:");
      BluetoothSerial.print(Lipo_level_cal);
      BluetoothSerial.println("%");
    }

    Low_voltage_counter++;
    if (Low_voltage_counter > 5)
      return false;
    else
      return true;
  }
}
#endif



