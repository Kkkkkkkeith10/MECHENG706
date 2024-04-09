//this file contains all functions used to execute the homing functionality


void homing_normal_system(bool use_Gyro, bool use_sonar, bool use_left_side_IRs, bool use_right_side_IRs, float tolarence)
{
  //use left or right side IRs to make the system parallel to the wall, only one side can be used at a sigle call
  //IR sensors groups are:     use_left_side_IRs: 41_02 & 2Y_04         use_right_side_IRs: 41_03 & 2Y_02
  //use_Gyro will reset the gyro
  //currently no sonar related actions are done
  
  
  
  
    temp_4103 = IR_sensorReadDistance("41_03");
    temp_2Y02 = IR_sensorReadDistance("2Y_02") + 15;
    


    while(temp_4103 <30.0 && temp_2Y02 <30.0){
      ccw();
      Serial.print("cw");
    }
      while((temp_4103 - temp_2Y02) > tolarence)
      {
        cw_low();
        Serial.print("cw low");
        temp_4103 = IR_sensorReadDistance("41_03");
        temp_2Y02 = IR_sensorReadDistance("2Y_02") + 10;
        Serial.print("temp_4103: ");
        Serial.print(temp_4103);
        Serial.print("temp_2Y02: ");
        Serial.println(temp_2Y02);
      }
      stop();
      while((temp_2Y02 - temp_4103) > tolarence)
      {
        ccw_low();
        Serial.print("ccw low");
        temp_4103 = IR_sensorReadDistance("41_03");
        temp_2Y02 = IR_sensorReadDistance("2Y_02") + 10;
        Serial.print("temp_4103: ");
        Serial.print(temp_4103);
        Serial.print("temp_2Y02: ");
        Serial.println(temp_2Y02);
      }
      stop();
    
    
  


  if(use_Gyro)
  {
    resetGyro();
  }
  stop();
  currentState++; //going to move all the currentState updates outside of functios where they are hidden. State should be updated manually after the function is called in the state machine
}
