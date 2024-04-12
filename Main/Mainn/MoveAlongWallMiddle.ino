// float VALUE_2Y04 = 0.0;
// float VALUE_4102 = 0.0;
// float VALUE_4103 = 0.0;
// float VALUE_2Y02 = 0.0;

void moving_alone_wall_middle(float target_distance_Sonar, float target_distance_IR, bool use_left_side_IRs, bool use_right_side_IRs)
{
  //This function mainly using two IR sensors to making the robot moving parallal with the wall.
  //use left or right side IRs to make the system parallel to the wall, only one side can be used at a sigle call
  //IR sensors groups are:     use_left_side_IRs: 41_02 & 2Y_04         use_right_side_IRs: 41_03 & 2Y_02
  //Gyro is also used as help, set [using_gyro] as TRUE to enable gyro 
  //The input is the target distance between the robot and the wall
  //%%%%This function using global sensor readings%%%%

  resetGyro();

  float time_curr = (float)millis()/1000;
  float time_prev = time_curr;
  float time_delta = time_curr - time_prev;

  int temp_SV_abs = 0;
  int temp_SV_dif = 0;
  int abs_move_C = 0;

  int temp_GV_dif = 0;

  // float Kp_IR_abs = 15;
  // float Ki_IR_abs = 1;
  // float Kp_IR_dif = 10;
  // float Ki_IR_dif = 1;
  // float threathod_IR = 50;

  float temp_IR_distance_abs = 0.0;
  //float temp_IR_distance_abs_prev = 0.0;
  float temp_IR_distance_error_abs = 0.0;
  float cumm_IR_distance_error_abs = 0.0;

  float temp_IR_distance_dif = 0.0;
  //float temp_IR_distance_dif_prev = 0.0;
  float cumm_IR_distance_dif = 0.0;

  float angle_error = 0;
  static float angle_error_cumm = 0;


  //for using both
  float temp_IR_distance_abs_right;
  float temp_IR_distance_abs_left;
  float cumm_IR_distance_abs_right;
  float cumm_IR_distance_abs_left;
  float temp_IR_distance_error_abs_right;
  float temp_IR_distance_error_abs_left;
  float cumm_IR_distance_error_abs_right;
  float cumm_IR_distance_error_abs_left;

  float target_distance_IR_right;
  float target_distance_IR_left;

  
  if(use_left_side_IRs) 
  {
    Kp_IR_abs = 20;
    Ki_IR_abs = 0;
    Kp_IR_dif = 1;
    Ki_IR_dif = 0.8;

    Kp_GV_dif = 10;
    Ki_GV_dif = 1;



    // float VALUE_2Y04 = find_average_IR("2Y_04");
    // float VALUE_4102 = find_average_IR("41_02");
    // temp_IR_distance_abs_prev = (VALUE_2Y04 + VALUE_4102)/2;
    // temp_IR_distance_dif_prev = (VALUE_2Y04 - VALUE_4102);
  }
  else if (use_right_side_IRs)
  { 
    Kp_IR_abs = 20;
    Ki_IR_abs = 0;
    Kp_IR_dif = 1;
    Ki_IR_dif = 0.8;

    Kp_GV_dif = 10;
    Ki_GV_dif = 1;

    // float VALUE_4103 = find_average_IR("41_03");
    // float VALUE_2Y02 = find_average_IR("2Y_02");
    // temp_IR_distance_abs_prev = (VALUE_4103 + VALUE_2Y02)/2;
    // temp_IR_distance_dif_prev = (VALUE_4103 - VALUE_2Y02);
  }
  else if (use_right_side_IRs && use_left_side_IRs)
  {
      float averages_sum_left = 0;
      float averages_sum_right = 0;
      for (int i = 0; i < 10; i++)
      {
        averages_sum_left += find_average_IR("2Y_02");
        averages_sum_right += find_average_IR("2Y_04");
      }
      float target_distance_IR_right = averages_sum_right /10;
      float target_distance_IR_left = averages_sum_left /10;
  }


  while(HC_SR04_range() > target_distance_Sonar)
  {
    time_prev = time_curr;
    time_curr = (float)millis()/1000;
    time_delta = time_curr - time_prev;

    if(use_left_side_IRs)
    {
      PREVIOUS_2Y04_VALUE = VALUE_2Y04;
      VALUE_2Y04 = find_average_IR("2Y_04");
      //temp_IR_distance_abs_prev = temp_IR_distance_abs;
      temp_IR_distance_abs = (VALUE_2Y04 + PREVIOUS_2Y04_VALUE)/2;
      temp_IR_distance_error_abs = target_distance_IR - temp_IR_distance_abs;
      cumm_IR_distance_error_abs = cumm_IR_distance_error_abs + temp_IR_distance_error_abs*time_delta;

      //temp_IR_distance_dif_prev = temp_IR_distance_dif;
      temp_IR_distance_dif = (VALUE_2Y04 - PREVIOUS_2Y04_VALUE);
      cumm_IR_distance_dif = cumm_IR_distance_dif + temp_IR_distance_dif*time_delta;

      temp_SV_abs = (int)(Kp_IR_abs*temp_IR_distance_error_abs + Ki_IR_abs*cumm_IR_distance_error_abs);
      abs_move_C = -1;

      temp_SV_dif = (int)(Kp_IR_dif*temp_IR_distance_dif + Ki_IR_dif*cumm_IR_distance_dif);
    }
    else if(use_right_side_IRs)
    {
      PREVIOUS_2Y02_VALUE = VALUE_2Y02;
      VALUE_2Y02 = find_average_IR("2Y_02");
      //temp_IR_distance_abs_prev = temp_IR_distance_abs;
      temp_IR_distance_abs = (PREVIOUS_2Y02_VALUE + VALUE_2Y02)/2;
      temp_IR_distance_error_abs = target_distance_IR - temp_IR_distance_abs;
      cumm_IR_distance_error_abs = cumm_IR_distance_error_abs + temp_IR_distance_error_abs*time_delta;

      //temp_IR_distance_dif_prev = temp_IR_distance_dif;
      temp_IR_distance_dif = (PREVIOUS_2Y02_VALUE - VALUE_2Y02);
      cumm_IR_distance_dif = cumm_IR_distance_dif + temp_IR_distance_dif*time_delta;


      temp_SV_abs = (int)(Kp_IR_abs*temp_IR_distance_error_abs + Ki_IR_abs*cumm_IR_distance_error_abs);
      abs_move_C = 1;

      temp_SV_dif = (int)(Kp_IR_dif*temp_IR_distance_dif + Ki_IR_dif*cumm_IR_distance_dif);
    }
    else if (use_right_side_IRs & use_left_side_IRs)
    {

      PREVIOUS_2Y04_VALUE = VALUE_2Y04;
      VALUE_2Y04 = find_average_IR("2Y_04");
      PREVIOUS_2Y02_VALUE = VALUE_2Y02;
      VALUE_2Y02 = find_average_IR("2Y_02");
      //temp_IR_distance_abs_prev = temp_IR_distance_abs;
      temp_IR_distance_abs_right = (PREVIOUS_2Y02_VALUE + VALUE_2Y02)/2;
      temp_IR_distance_error_abs_right = target_distance_IR_right - temp_IR_distance_abs_right;
      cumm_IR_distance_error_abs_right = cumm_IR_distance_error_abs_right + temp_IR_distance_error_abs_right*time_delta;

      temp_IR_distance_abs_left = (PREVIOUS_2Y04_VALUE + VALUE_2Y04)/2;
      temp_IR_distance_error_abs_left = target_distance_IR_left - temp_IR_distance_abs_left;
      cumm_IR_distance_error_abs_left = cumm_IR_distance_error_abs_left + temp_IR_distance_error_abs_left*time_delta;

      // //temp_IR_distance_dif_prev = temp_IR_distance_dif;
      // temp_IR_distance_dif = (PREVIOUS_2Y02_VALUE - VALUE_2Y02);
      // cumm_IR_distance_dif = cumm_IR_distance_dif + temp_IR_distance_dif*time_delta;


      temp_SV_abs = (int)(Kp_IR_abs*(temp_IR_distance_error_abs_right+temp_IR_distance_error_abs_left) + Ki_IR_abs*(cumm_IR_distance_error_abs_right+cumm_IR_distance_error_abs_left));
      abs_move_C = 1;

      // temp_SV_dif = (int)(Kp_IR_dif*temp_IR_distance_dif + Ki_IR_dif*cumm_IR_distance_dif);
    }

    readGyro1();
    angle_error = 0 - currentAngle;
    angle_error_cumm += angle_error; //add the error to cummulative error
    Serial1.print(currentAngle);
    Serial1.print(" ");
    Serial1.println(temp_GV_dif);

    temp_GV_dif = (int)(Kp_GV_dif*angle_error + Ki_GV_dif*angle_error_cumm);

    // SVRF = saturation(500 + temp_SV_dif  + temp_SV_abs*abs_move_C);
    // SVRR = saturation(500 + temp_SV_dif  - temp_SV_abs*abs_move_C);
    // SVLF = saturation(-500 + temp_SV_dif  + temp_SV_abs*abs_move_C);
    // SVLR = saturation(-500 + temp_SV_dif  - temp_SV_abs*abs_move_C);

    SVRF = saturation(500   + temp_SV_abs*abs_move_C - temp_GV_dif + temp_SV_dif);
    SVRR = saturation(500   - temp_SV_abs*abs_move_C - temp_GV_dif + temp_SV_dif);
    SVLF = saturation(-500   + temp_SV_abs*abs_move_C - temp_GV_dif + temp_SV_dif);
    SVLR = saturation(-500   - temp_SV_abs*abs_move_C - temp_GV_dif + temp_SV_dif);

    // SVRF = saturation(500   + temp_SV_abs*abs_move_C + temp_GV_dif*abs_move_C);
    // SVRR = saturation(500   - temp_SV_abs*abs_move_C + temp_GV_dif*abs_move_C);
    // SVLF = saturation(-500   + temp_SV_abs*abs_move_C + temp_GV_dif*abs_move_C);
    // SVLR = saturation(-500   - temp_SV_abs*abs_move_C + temp_GV_dif*abs_move_C);

    // Serial1.print(VALUE_2Y04);
    // Serial1.print(" ");
    // Serial1.print(VALUE_4102);
    // Serial1.println();
    // Serial.print(temp_SV);
    // Serial.print(" ");
    // Serial.println(Crab_move_C);
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
    // Serial.print(1500 + SVRR);
    // Serial.print(" ");
    // Serial.print(1500 + SVRF);
    // Serial.print(" ");
    // Serial.print(1500 + SVLF);
    // Serial.print(" ");
    // Serial.println(1500 + SVLR);
    // Serial.println();

    left_font_motor.writeMicroseconds(1500 + SVLF);
    left_rear_motor.writeMicroseconds(1500 + SVLR);
    right_rear_motor.writeMicroseconds(1500 + SVRR);
    right_font_motor.writeMicroseconds(1500 + SVRF);

    //ccw == all (-)
    //cw === all (+)
    delay(100);
  }
    stop();
}