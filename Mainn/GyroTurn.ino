
//Define Variables we'll be connecting to
double Setpoint, Input, Output;
//output is a value between 0 and 255
//need to map to 0 being -500 and 255 being 500ca
//Specify the links and initial tuning parameters
double Kp_Turn=8, Ki_Turn=0, Kd_Turn=0;
//TO GO CW use DIRECT and CW
//To GO CCW use REVERSE and CCW
PID myPID(&currentAngle, &Output, &Setpoint, Kp_Turn, Ki_Turn, Kd_Turn, DIRECT);

void GyroTurn(double target)
{
  static unsigned long previous_millis;
  static char msg;
  static double speed_value;
  static unsigned long start_turn;
  static double tolerance = 5;
  static double error = 0 ;
  static double cumm_error = 0;

  while(currentAngle < (target - tolerance) || currentAngle > (target + tolerance))
  {
    if (millis()-previous_millis > 50)
    {
      readGyro1();
      error = target - currentAngle;
      cumm_error += error;
      speed_value = error*Kp_Turn + cumm_error*Ki_Turn;


      left_font_motor.writeMicroseconds(1500 - saturation(speed_value));
      left_rear_motor.writeMicroseconds(1500 - saturation(speed_value));
      right_rear_motor.writeMicroseconds(1500 - saturation(speed_value));
      right_font_motor.writeMicroseconds(1500 - saturation(speed_value));


      // Serial1.println(currentAngle);
      previous_millis = millis();
      ReadAllSensor();
      // Serial1.println(saturation(100+speed_value));

    }
  }
  // Serial1.println("Stopping");
  stop();
  return;
}






void GyroTurn1(double target)
{
  static unsigned long previous_millis;
  static char msg;
  static double speed_value;
  static unsigned long start_turn;
  static double tolerance = 1;
  static double error = 0 ;
  static double cumm_error = 0;

  while(currentAngle < (target - tolerance) || currentAngle > (target + tolerance))
  {
    if (millis()-previous_millis > 50)
    {
      readGyro1();
      error = target - currentAngle;
      cumm_error += error;
      speed_value = error*Kp_Turn + cumm_error*Ki_Turn;

      if (speed_value > 0)
      {
        speed_value = speed_value + 100;
      }
      else if(speed_value < 0)
      {
        speed_value = speed_value - 100;
      }
      else{}


      left_font_motor.writeMicroseconds(1500 - saturation(speed_value));
      left_rear_motor.writeMicroseconds(1500 - saturation(speed_value));
      right_rear_motor.writeMicroseconds(1500 - saturation(speed_value));
      right_font_motor.writeMicroseconds(1500 - saturation(speed_value));


      // Serial1.println(currentAngle);
      previous_millis = millis();
      ReadAllSensor();
      // Serial1.println(saturation(100+speed_value));

    }
  }
  // Serial1.println("Stopping");
  stop();
  return;
}

















double get_motor_value(double input)//input is between 0 and 255 and maps it so that the output is -500 when input = 0 and 500 when input = 255
{
  double output;
  output = -300+input*2.353; //
  // output = -500+input*3.92;
  return output;
}



