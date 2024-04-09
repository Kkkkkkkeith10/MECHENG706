//This file contains the functions used to implement the moving straight along a wall functionality
//


void move_along_wall(bool use_Gyro, bool use_sonar, bool use_left_side_IRs, bool use_right_side_IRs, float tolarence)
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
    temp_2Y02 = IR_sensorReadDistance("2Y_02") + 15;

    while((temp_4103 - temp_2Y02) > tolarence)
    {
      cw_low();

      temp_4103 = IR_sensorReadDistance("41_03");
      temp_2Y02 = IR_sensorReadDistance("2Y_02") + 15;
    }
    stop();
    while((temp_2Y02 - temp_4103) > tolarence)
    {
      ccw_low();

      temp_4103 = IR_sensorReadDistance("41_03");
      temp_2Y02 = IR_sensorReadDistance("2Y_02") + 15;
    }
    stop();
  }
  else {}

  if(use_Gyro)
  {
    resetGyro();
  }
  stop();
  currentState++;
}