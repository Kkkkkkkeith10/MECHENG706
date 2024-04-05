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

