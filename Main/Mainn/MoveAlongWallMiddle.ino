// float VALUE_2Y04 = 0.0;
// float VALUE_4102 = 0.0;
// float VALUE_4103 = 0.0;
// float VALUE_2Y02 = 0.0;

  int temp_SV_abs = 0;
  int temp_SV_dif = 0;
  int abs_move_C = 0;
  int temp_GV_dif = 0;


  static float temp_IR_distance_abs = 0.0;
  //float temp_IR_distance_abs_prev = 0.0;
  static float temp_IR_distance_error_abs = 0.0;
  static float cumm_IR_distance_error_abs = 0.0;

  static float temp_IR_distance_dif = 0.0;
  //float temp_IR_distance_dif_prev = 0.0;
  float cumm_IR_distance_dif = 0.0;

  float angle_error = 0;
  static float angle_error_cumm = 0;

void moving_alone_wall_middle(int go_reverse, float target_distance_IR, bool use_left_side_IRs, bool use_right_side_IRs,float Kp_IR_abs,float Ki_IR_abs,float Kp_IR_dif,float Ki_IR_dif,float Kp_GV_dif,
float Ki_GV_dif)
{
  //This function mainly using two IR sensors to making the robot moving parallal with the wall.
  //use left or right side IRs to make the system parallel to the wall, only one side can be used at a sigle call
  //IR sensors groups are:     use_left_side_IRs: 41_02 & 2Y_04         use_right_side_IRs: 41_03 & 2Y_02
  //Gyro is also used as help, set [using_gyro] as TRUE to enable gyro 
  //The input is the target distance between the robot and the wall
  //%%%%This function using global sensor readings%%%%
  //Pass -1 for reverse and 1 for forward



    // Serial1.print(sonar_reading);
    // Serial1.print(" ");
    static float time_curr = (float)millis()/1000;
    static float time_prev = time_curr;
    static float time_delta = time_curr - time_prev;

    if(use_left_side_IRs)
    {
      // disregard large changes in measurements
      // if ((target_distance_IR - IR_sensorReadDistance("2Y04") >80) | (target_distance_IR - IR_sensorReadDistance("2Y04") < -80))
      // {
      //   //do nothing
      // }
      // else
      // {
      //   PREVIOUS_2Y04_VALUE = VALUE_2Y04;
      //   VALUE_2Y04 = IR_sensorReadDistance("2Y_04");
      //   // Serial1.print(VALUE_2Y04);
      //   // Serial1.print(" ");
      //   // Serial1.println(PREVIOUS_2Y04_VALUE);
      // }

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
      // if ((target_distance_IR - IR_sensorReadDistance("2Y02") >80) | (target_distance_IR - IR_sensorReadDistance("2Y02") < -80))
      // {
      //   //do nothing
      // }
      // else
      // {
      //   //update
      //   PREVIOUS_2Y02_VALUE = VALUE_2Y02;
      //   VALUE_2Y02 = IR_sensorReadDistance("2Y_02");
      //   // Serial1.print(VALUE_2Y02);
      //   // Serial1.print(" ");
      //   // Serial1.println(PREVIOUS_2Y02_VALUE); 
      // }

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

    readGyro1();
    angle_error = 0 - currentAngle;
    angle_error_cumm += angle_error; //add the error to cummulative error
    // Serial1.print(currentAngle);
    // Serial1.print(" ");
    // Serial1.println(temp_GV_dif);

    temp_GV_dif = (int)(Kp_GV_dif*angle_error + Ki_GV_dif*angle_error_cumm);

    // SVRF = saturation(500 + temp_SV_dif  + temp_SV_abs*abs_move_C);
    // SVRR = saturation(500 + temp_SV_dif  - temp_SV_abs*abs_move_C);
    // SVLF = saturation(-500 + temp_SV_dif  + temp_SV_abs*abs_move_C);
    // SVLR = saturation(-500 + temp_SV_dif  - temp_SV_abs*abs_move_C);

    SVRF = saturation(500*go_reverse   + temp_SV_abs*abs_move_C - temp_GV_dif + temp_SV_dif);
    SVRR = saturation(500*go_reverse   - temp_SV_abs*abs_move_C - temp_GV_dif + temp_SV_dif);
    SVLF = saturation(-500*go_reverse   + temp_SV_abs*abs_move_C - temp_GV_dif + temp_SV_dif);
    SVLR = saturation(-500*go_reverse   - temp_SV_abs*abs_move_C - temp_GV_dif + temp_SV_dif);

    left_font_motor.writeMicroseconds(1500 + SVLF);
    left_rear_motor.writeMicroseconds(1500 + SVLR);
    right_rear_motor.writeMicroseconds(1500 + SVRR);
    right_font_motor.writeMicroseconds(1500 + SVRF);
}

void PID_Zero()
{
    int temp_SV_abs = 0;
  int temp_SV_dif = 0;
  int abs_move_C = 0;
  int temp_GV_dif = 0;


  static float temp_IR_distance_abs = 0.0;
  //float temp_IR_distance_abs_prev = 0.0;
  static float temp_IR_distance_error_abs = 0.0;
  static float cumm_IR_distance_error_abs = 0.0;

  static float temp_IR_distance_dif = 0.0;
  //float temp_IR_distance_dif_prev = 0.0;
  float cumm_IR_distance_dif = 0.0;

  float angle_error = 0;
  static float angle_error_cumm = 0;

  return;
}