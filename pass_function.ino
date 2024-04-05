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
