
//----------------------Motor moments------------------------
// The Vex Motor Controller 29 use Servo Control signals to determine speed and direction, with 0 degrees meaning neutral https://en.wikipedia.org/wiki/Servo_control

void disable_motors()
{
  left_font_motor.detach();  // detach the servo on pin left_front to turn Vex Motor Controller 29 Off
  left_rear_motor.detach();  // detach the servo on pin left_rear to turn Vex Motor Controller 29 Off
  right_rear_motor.detach(); // detach the servo on pin right_rear to turn Vex Motor Controller 29 Off
  right_font_motor.detach(); // detach the servo on pin right_front to turn Vex Motor Controller 29 Off

  pinMode(left_front, INPUT);
  pinMode(left_rear, INPUT);
  pinMode(right_rear, INPUT);
  pinMode(right_front, INPUT);
}

void enable_motors()
{
  left_font_motor.attach(left_front);   // attaches the servo on pin left_front to turn Vex Motor Controller 29 On
  left_rear_motor.attach(left_rear);    // attaches the servo on pin left_rear to turn Vex Motor Controller 29 On
  right_rear_motor.attach(right_rear);  // attaches the servo on pin right_rear to turn Vex Motor Controller 29 On
  right_font_motor.attach(right_front); // attaches the servo on pin right_front to turn Vex Motor Controller 29 On
}
void stop() // Stop
{
  left_font_motor.writeMicroseconds(1500);
  left_rear_motor.writeMicroseconds(1500);
  right_rear_motor.writeMicroseconds(1500);
  right_font_motor.writeMicroseconds(1500);
}

void forward()
{
  left_font_motor.writeMicroseconds(1500 + speed_val);
  left_rear_motor.writeMicroseconds(1500 + speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_font_motor.writeMicroseconds(1500 - speed_val);
}

void reverse()
{
  left_font_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_font_motor.writeMicroseconds(1500 + speed_val);
}

void ccw()
{
  left_font_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_font_motor.writeMicroseconds(1500 - speed_val);
}

void cw()
{
  left_font_motor.writeMicroseconds(1500 + speed_val);
  left_rear_motor.writeMicroseconds(1500 + speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_font_motor.writeMicroseconds(1500 + speed_val);
}

void strafe_left()
{
  left_font_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 + speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_font_motor.writeMicroseconds(1500 - speed_val);
}

void strafe_right()
{
  left_font_motor.writeMicroseconds(1500 + speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_font_motor.writeMicroseconds(1500 + speed_val);
}


void strafe_left_until(float target_distance_IRs, int F_B, float delay_time)
{

  VALUE_4103 = find_average_IR("41_03");
  VALUE_2Y02 = find_average_IR("2Y_02");
  int temp_SV_F = 0;
  int temp_SV_B = 0;

  if(F_B == 1)
  {
    temp_SV_F = 400;
  }
  else if(F_B == -1)
  {
    temp_SV_B = 400;
  }

  if (delay_time != 0)
  {
    left_font_motor.writeMicroseconds(1500 - speed_val + temp_SV_B);
    left_rear_motor.writeMicroseconds(1500 + speed_val - temp_SV_F);
    right_rear_motor.writeMicroseconds(1500 + speed_val - temp_SV_B);
    right_font_motor.writeMicroseconds(1500 - speed_val + temp_SV_F);
    delay(delay_time);
    stop();
  }
  else
  {
    while((VALUE_4103 + VALUE_2Y02)/2 > target_distance_IRs)
    {
     left_font_motor.writeMicroseconds(1500 - speed_val + temp_SV_B);
     left_rear_motor.writeMicroseconds(1500 + speed_val - temp_SV_F);
     right_rear_motor.writeMicroseconds(1500 + speed_val - temp_SV_B);
     right_font_motor.writeMicroseconds(1500 - speed_val + temp_SV_F);

     VALUE_4103 = find_average_IR("41_03");
     VALUE_2Y02 = find_average_IR("2Y_02");
    }
  }
}

void strafe_right_until(float target_distance_IRs, int F_B, float delay_time)
{
  Serial.print("right");
  VALUE_2Y04 = find_average_IR("2Y_04");
  VALUE_4102 = find_average_IR("41_02");
  int temp_SV_F = 0;
  int temp_SV_B = 0;

  if(F_B == 1)
  {
    temp_SV_F = 400;
  }
  else if(F_B == -1)
  {
    // Serial.print("back");
    temp_SV_B = 400;
  }
  else{}

  if (delay_time != 0)
  {
    left_font_motor.writeMicroseconds(1500 + speed_val - temp_SV_F);
    left_rear_motor.writeMicroseconds(1500 - speed_val + temp_SV_B);
    right_rear_motor.writeMicroseconds(1500 - speed_val + temp_SV_F);
    right_font_motor.writeMicroseconds(1500 + speed_val - temp_SV_B);
    delay(delay_time);
    stop();
  }
  else
  {
    while((VALUE_2Y04 + VALUE_4102)/2 > target_distance_IRs)
   {
     left_font_motor.writeMicroseconds(1500 + speed_val - temp_SV_F);
     left_rear_motor.writeMicroseconds(1500 - speed_val + temp_SV_B);
     right_rear_motor.writeMicroseconds(1500 - speed_val + temp_SV_F);
     right_font_motor.writeMicroseconds(1500 + speed_val - temp_SV_B);

     VALUE_2Y04 = find_average_IR("2Y_04");
     VALUE_4102 = find_average_IR("41_02");
   }
  }
}




void ccw_low()
{
  left_font_motor.writeMicroseconds(1500 - speed_val_low);
  left_rear_motor.writeMicroseconds(1500 - speed_val_low);
  right_rear_motor.writeMicroseconds(1500 - speed_val_low);
  right_font_motor.writeMicroseconds(1500 - speed_val_low);
}

void cw_low()
{
  left_font_motor.writeMicroseconds(1500 + speed_val_low);
  left_rear_motor.writeMicroseconds(1500 + speed_val_low);
  right_rear_motor.writeMicroseconds(1500 + speed_val_low);
  right_font_motor.writeMicroseconds(1500 + speed_val_low);
}