
/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>
#include <Servo.h> //Need for Servo pulse output



// Default motor control pins
const byte left_front = 46;
const byte left_rear = 47;
const byte right_rear = 50;
const byte right_front = 51;

Servo left_font_motor;  // create servo object to control Vex Motor Controller 29
Servo left_rear_motor;  // create servo object to control Vex Motor Controller 29
Servo right_rear_motor; // create servo object to control Vex Motor Controller 29
Servo right_font_motor; // create servo object to control Vex Motor Controller 29
Servo turret_motor;

//gyro
int sensorPin = A7;            // define the pin that gyro is connected
int sensorValue = 0;           // read out value of sensor
float gyroSupplyVoltage = 5;   // supply voltage for gyro
float gyroZeroVoltage = 0;     // the value of voltage when gyro is zero
float gyroSensitivity = 0.007; // gyro sensitivity unit is (mv/degree/second) get from datasheet
float rotationThreshold = 1.5; // because of gyro drifting, defining rotation angular velocity less than
// this value will not be ignored
float gyroRate = 0;     // read out value of sensor in voltage

double currentAngle;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
//output is a value between 0 and 255
//need to map to 0 being -500 and 255 being 500ca

//Specify the links and initial tuning parameters
double Kp=2, Ki=0.72, Kd=0;
//TO GO CW use DIRECT and CW
//To GO CCW use REVERSE and CCW
PID myPID(&currentAngle, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
  enable_motors();

  resetGyro();
  Serial1.begin(115200);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  delay(100);
  Serial1.println("Beginning turn");
  resetGyro();
  Setpoint = 180;
}

void loop()
{
  static unsigned long previous_millis;
  static char msg;
  static double speed_value;
  static unsigned long start_turn;
  static double tolerance = 0.1;

  static int SVRF;
  static int SVRR;
  static int SVLF;
  static int SVLR;

  if (Serial1.available() > 1)
  {
    msg = 'a';
    start_turn = millis();
  }

  if (msg == 'a')
  {
    Serial1.println("recieved:");
    Serial1.println(currentAngle);
    Serial1.println(Setpoint);
    while(currentAngle < (Setpoint - tolerance) || currentAngle > (Setpoint + tolerance))
    {
      static unsigned long previous_millis;
      if (millis()-previous_millis > 50)
      {
        readGyro();
        myPID.Compute();
        speed_value = get_motor_value(Output);


        SVRF = saturation(speed_value);
        SVRR = saturation(speed_value);
        SVLF = saturation(speed_value);
        SVLR = saturation(speed_value);

        left_font_motor.writeMicroseconds(1500 + SVLF);
        left_rear_motor.writeMicroseconds(1500 + SVLR);
        right_rear_motor.writeMicroseconds(1500 + SVRR);
        right_font_motor.writeMicroseconds(1500 + SVRF);


        Serial1.println(currentAngle);
        previous_millis = millis();
      }
    }
    stop();
  }
}

double get_motor_value(double input)//input is between 0 and 255 and maps it so that the output is -500 when input = 0 and 500 when input = 255
{
  double output;
  output = -300+input*2.353; //
  // output = -500+input*3.92;
  return output;
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




