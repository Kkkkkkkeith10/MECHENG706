//this file contains all functions used to execute the homing functionality


void homing_normal_system(bool use_Gyro, bool use_sonar, bool use_left_side_IRs, bool use_right_side_IRs, float tolarence)
{
  //use left or right side IRs to make the system parallel to the wall, only one side can be used at a sigle call
  //IR sensors groups are:     use_left_side_IRs: 41_02 & 2Y_04         use_right_side_IRs: 41_03 & 2Y_02
  //use_Gyro will reset the gyro
  //currently no sonar related actions are done
  
    Serial1.print(movement_phase);
  
  
    temp_4102 = IR_sensorReadDistance("41_02");
    temp_2Y04 = IR_sensorReadDistance("2Y_04");
    


    while(temp_4102 <30.0 && temp_2Y04 <30.0){
      ccw();
      Serial1.print("cw");
    }
    while((temp_4102 - temp_2Y04) > tolarence || (temp_2Y04 - temp_4102) > tolarence)
    {
      if((temp_4102 - temp_2Y04)>0){
        ccw_low();
        Serial1.print("cw low");
      }
      else{
        cw_low();
        Serial1.print("ccw low");
      }
       

      
      temp_4102 = IR_sensorReadDistance("41_03");
      temp_2Y04 = IR_sensorReadDistance("2Y_02");
      Serial1.print("temp_4102: ");
      Serial1.print(temp_4102);
      Serial1.print("temp_2Y04: ");
      Serial1.println(temp_2Y04);
    }
    stop();
    
    
  


  if(use_Gyro)
  {
    resetGyro();
  }
  stop();
  delay(500);
  movement_phase++; //going to move all the currentState updates outside of functios where they are hidden. State should be updated manually after the function is called in the state machine
}



float VALUE_2Y04 = 0.0;
float VALUE_4102 = 0.0;
float VALUE_4103 = 0.0;
float VALUE_2Y02 = 0.0;

float Kp_IR_dif = 10;
float Kp_IR_abs = 15;
float threathod_IR = 10000;



void moving_alone_wall_until_cm(int until_distance,float target_distance, bool using_gyro, bool use_left_side_IRs, bool use_right_side_IRs)
{
  //This function mainly using two IR sensors to making the robot moving parallal with the wall.
  //use left or right side IRs to make the system parallel to the wall, only one side can be used at a sigle call
  //IR sensors groups are:     use_left_side_IRs: 41_02 & 2Y_04         use_right_side_IRs: 41_03 & 2Y_02
  //Gyro is also used as help, set [using_gyro] as TRUE to enable gyro 
  //The input is the target distance between the robot and the wall
  //%%%%This function using global sensor readings%%%%
  //%%%%This function needs to be called in a loop%%%%
  VALUE_2Y04 = IR_sensorReadDistance("2Y_04");
  VALUE_4102 = IR_sensorReadDistance("41_02");
  VALUE_4103 = IR_sensorReadDistance("41_03");
  VALUE_2Y02 = IR_sensorReadDistance("2Y_02");

  while (HC_SR04_range() > until_distance)
  {
    Serial1.println(movement_phase);
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


    // Serial.print(VALUE_4102);
    // Serial.print(" ");
    // Serial.print(VALUE_2Y04);
    // Serial.print(" ");
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
    delay(20);
  }
  stop();
  movement_phase++;
}

