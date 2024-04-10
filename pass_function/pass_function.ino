//This script is only used to transfer functions, can not use directly.




void normal_system(bool use_Gyro, bool use_sonar, bool use_left_side_IRs, bool use_right_side_IRs, float tolarence)
{
  //use left or right side IRs to make the system parallel to the wall, only one side can be used at a sigle call
  //IR sensors groups are:     use_left_side_IRs: 41_02 & 2Y_04         use_right_side_IRs: 41_03 & 2Y_02
  //use_Gyro will reset the gyro
  //currently no sonar related actions are done
  
  if(use_left_side_IRs)
  {
    while((IR_sensorReadDistance("41_02")-IR_sensorReadDistance("2Y_04")) > tolarence)
    {
      ccw();
    }
    while((IR_sensorReadDistance("2Y_04")-IR_sensorReadDistance("41_02")) > tolarence)
    {
      cw();
    }
  }
  else if(use_right_side_IRs)
  {
    while((IR_sensorReadDistance("41_03")-IR_sensorReadDistance("2Y_02")) > tolarence)
    {
      cw();
    }
    while((IR_sensorReadDistance("2Y_02")-IR_sensorReadDistance("41_03")) > tolarence)
    {
      ccw();
    }
  }
  else {}

  if(use_Gyro)
  {
    resetGyro();
  }
}






void resetGyro()
{
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













float temp_4102 = 0.0;
float temp_4103 = 0.0;
float temp_2Y02 = 0.0;
float temp_2Y04 = 0.0;

void normal_system(bool use_Gyro, bool use_sonar, bool use_left_side_IRs, bool use_right_side_IRs, float tolarence)
{
  //use left or right side IRs to make the system parallel to the wall, only one side can be used at a sigle call
  //IR sensors groups are:     use_left_side_IRs: 41_02 & 2Y_04         use_right_side_IRs: 41_03 & 2Y_02
  //use_Gyro will reset the gyro
  //currently no sonar related actions are done
  
  if(use_left_side_IRs)
  {
    temp_4102 = IR_sensorReadDistance("41_02") + 7;
    temp_2Y04 = IR_sensorReadDistance("2Y_04");

    while((temp_4102 - temp_2Y04) > tolarence)
    {
      ccw_low();

      temp_4102 = IR_sensorReadDistance("41_02") + 7;
      temp_2Y04 = IR_sensorReadDistance("2Y_04");
    }
    stop();
    while((temp_2Y04 - temp_4102) > tolarence)
    {
      cw_low();

      temp_4102 = IR_sensorReadDistance("41_02") + 7;
      temp_2Y04 = IR_sensorReadDistance("2Y_04");
    }
    stop();
  }
  else if(use_right_side_IRs)
  {
    temp_4103 = IR_sensorReadDistance("41_03");
    temp_2Y02 = IR_sensorReadDistance("2Y_02") + 19;

    while((temp_4103 - temp_2Y02) > tolarence)
    {
      cw_low();

      temp_4103 = IR_sensorReadDistance("41_03");
      temp_2Y02 = IR_sensorReadDistance("2Y_02") + 19;
    }
    stop();
    while((temp_2Y02 - temp_4103) > tolarence)
    {
      ccw_low();

      temp_4103 = IR_sensorReadDistance("41_03");
      temp_2Y02 = IR_sensorReadDistance("2Y_02") + 19;
    }
    stop();
  }
  else {}

  if(use_Gyro)
  {
    resetGyro();
  }
  stop();
}


int speed_val_low = 100;
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











void scan_until_normal()
{
  float threathod = 0.2;  //mm
  float current_ave_distance = find_average_distance();
  float previous_ave_distance = current_ave_distance + 1;

  ccw_low();
  delay(200);
  stop();
  while ((current_ave_distance - previous_ave_distance) < threathod)
  {
    ccw_low();
    delay(100);
    stop();
    previous_ave_distance = current_ave_distance;
    current_ave_distance = find_average_distance();
  }
  stop();

  cw_low();
  delay(200);
  stop();
  previous_ave_distance = current_ave_distance;
  current_ave_distance = find_average_distance();
  while((current_ave_distance - previous_ave_distance) < threathod)
  {
    cw_low();
    delay(100);
    stop();
    previous_ave_distance = current_ave_distance;
    current_ave_distance = find_average_distance();
  }
  stop();
}

float find_average_distance()
{
  float distances = 0.0;
  float reading;

  for (i = 0; i <= 9; i++)
  {
    reading = HC_SR04_range();
    distances += reading;
    delay(5);
  }
  distances = distances/10;
  return distances;
}
















float Kp_IR_dif = 15;
float Kp_IR_abs = 10;
float threathod_IR = 1000;

    while(true)
    {
      // input can be : "//41_01", "41_02", "41_03", "//2Y_01", "2Y_02", "//2Y_03", "2Y_04",
      // return distance in mm
      VALUE_2Y04 = IR_sensorReadDistance("2Y_04");
      VALUE_4102 = IR_sensorReadDistance("41_02");
      VALUE_4103 = IR_sensorReadDistance("41_03");
      VALUE_2Y02 = IR_sensorReadDistance("2Y_02");

      //moving_alone_wall(float target_distance, bool using_gyro, bool use_left_side_IRs, bool use_right_side_IRs)
      moving_alone_wall(100, 0, 1, 0);
      delay(100);
    }

void moving_alone_wall(float target_distance, bool using_gyro, bool use_left_side_IRs, bool use_right_side_IRs)
{
  //This function mainly using two IR sensors to making the robot moving parallal with the wall.
  //use left or right side IRs to make the system parallel to the wall, only one side can be used at a sigle call
  //IR sensors groups are:     use_left_side_IRs: 41_02 & 2Y_04         use_right_side_IRs: 41_03 & 2Y_02
  //Gyro is also used as help, set [using_gyro] as TRUE to enable gyro 
  //The input is the target distance between the robot and the wall
  //%%%%This function using global sensor readings%%%%
  //%%%%This function needs to be called in a loop%%%%

  int temp_SV = 0;
  int turn_C = 0;

  if(use_left_side_IRs)
  {
    if(abs(VALUE_2Y04 - VALUE_4102) > threathod_IR)
    {
      turn_C = 500*(VALUE_2Y04 - VALUE_4102);
    }
    else
    {
      temp_SV = (int)(Kp_IR_dif*(VALUE_2Y04 - VALUE_4102) + Kp_IR_abs*(target_distance - (VALUE_2Y04 + VALUE_4102)/2));
    }
  }
  else if(use_right_side_IRs)
  {
    if(abs(VALUE_4103 - VALUE_2Y02) > threathod_IR)
    {
      turn_C = 500*(VALUE_4103 - VALUE_2Y02);
    }
    else
    {
      temp_SV = (int)(Kp_IR_dif*(VALUE_4103 - VALUE_2Y02) + Kp_IR_abs*((VALUE_4103 + VALUE_2Y02)/2 - target_distance));
    }
  }
  else{}

  if(using_gyro){}


  SVRF = saturation(500 + temp_SV + turn_C);
  SVRR = saturation(500 + temp_SV + turn_C);
  SVLF = saturation(-500 + temp_SV + turn_C);
  SVLR = saturation(-500 + temp_SV + turn_C);


  Serial.print(VALUE_4102);
  Serial.print(" ");
  Serial.print(VALUE_2Y04);
  Serial.print(" ");
  // Serial.print(temp_SV);
  // Serial.print(" ");
  // Serial.print(temp_SV);
  // Serial.print(" ");
  // Serial.print(temp_SV);
  // Serial.print(" ");
  // Serial.print(ErrorAngle_Degree);
  // Serial.print(" ");
  // Serial.print(SV_P);
  // Serial.print(" ");
  Serial.print(1500 + SVRR);
  Serial.print(" ");
  Serial.print(1500 + SVRF);
  Serial.print(" ");
  Serial.print(1500 + SVLF);
  Serial.print(" ");
  Serial.println(1500 + SVLR);

  left_font_motor.writeMicroseconds(1500 + SVLF);
  left_rear_motor.writeMicroseconds(1500 + SVLR);
  right_rear_motor.writeMicroseconds(1500 + SVRR);
  right_font_motor.writeMicroseconds(1500 + SVRF);

  //ccw == all (-)
  //cw === all (+)
}
