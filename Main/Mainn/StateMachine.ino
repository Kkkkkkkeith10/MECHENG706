//This file implements the state machines used for control flow of the robot when it's executing it's task. It executes project 1 of ME706

void execute_movement_phase()
{ 
  //state0: scan for normal
  //state1: drive to wall
  //state2: turn to parallel approximation
  //state3: parallel confirmation
  //state4: drive to corner
  //state5: turn 90 degree to ready chekc for long side
  //state6: determine which side is the long side, short => state7, long=>state 8
  //state7: (if facing short side) drive to corner, next state => state7
  //state8: turn 90 degree, readying to start
  //state9: (main start tarting pos)


  switch (movement_phase)
  {
    // Serial1.println(movement_phase);

    case 0:
      scan_until_normal();
      delay(100);
      movement_phase++;
      // GyroTurn(-180);
      break;
    case 1:
      // Serial1.println(movement_phase);
      driveStrightUntilDistance(10);
      stop();
      delay(100);
      movement_phase++;
      break;
    case 2:
      // resetGyro();
      GyroTurn(90);
      delay(100);
      movement_phase++;
      break;
    case 3:
    //drive along wall until
      sonar_reading = HC_SR04_range();
      //right side PID values
      Kp_IR_abs = 10;
      Ki_IR_abs = 0;
      Kp_IR_dif = 10;
      Ki_IR_dif = 0;
      while(HC_SR04_range() > 10) //execute until it is 10cm away from wall
      {
        sonar_reading = HC_SR04_range();
        moving_alone_wall(1,90,0,1, Kp_IR_abs, Ki_IR_abs, Kp_IR_dif,Ki_IR_dif);
        ReadAllSensor();
      }
      stop();
      delay(100);
      movement_phase++;
      break;
    case 4:
      resetGyro();
      GyroTurn(90);
      delay(100);
      movement_phase++;
      break;
    case 5:
      checkForLongSide();
      //no movement_phase++;
      break;
    case 6:
      sonar_reading = HC_SR04_range();
      //right side PID values
      Kp_IR_abs = 10;
      Ki_IR_abs = 0;
      Kp_IR_dif = 10;
      Ki_IR_dif = 0;
      while(HC_SR04_range() > 10) //execute until it is 10cm away from wall
      {
        sonar_reading = HC_SR04_range();
        moving_alone_wall(1,90,0,1, Kp_IR_abs, Ki_IR_abs, Kp_IR_dif,Ki_IR_dif);
        ReadAllSensor();
      }
      stop();
      delay(100);
      movement_phase++;
      break;
    case 7:
    resetGyro();
      GyroTurn(90);
      delay(100);
      movement_phase++;
      break;


//Run

    case 8:
      //first pass
      sonar_reading = HC_SR04_range();
      //left side PID values
      Kp_IR_abs = 20;
      Ki_IR_abs = 0;
      Kp_IR_dif = 20;
      Ki_IR_dif = 0;

      PID_Zero();
      while(HC_SR04_range() > 10) //execute until it is 10cm away from wall
      {
        sonar_reading = HC_SR04_range();
        moving_alone_wall(1,90,1,0, Kp_IR_abs, Ki_IR_abs, Kp_IR_dif,Ki_IR_dif);
        ReadAllSensor();
      }
      stop();
      delay(100);
      strafe_left();
      delay(100);
      stop();
      movement_phase++;
      break;
    case 9:
      //second pass
      sonar_reading = HC_SR04_range();
      // resetGyro();
      //left side PID values
      Kp_IR_abs = 20;
      Ki_IR_abs = 0;
      Kp_IR_dif = 5;
      Ki_IR_dif = 0;


      PID_Zero();
      while(HC_SR04_range() < 160) //execute until it is 10cm away from wall
      {
        sonar_reading = HC_SR04_range();
        moving_alone_wall_middle(-1,190,1,0, Kp_IR_abs, Ki_IR_abs, Kp_IR_dif,Ki_IR_dif,Kp_GV_dif, Ki_GV_dif);
        ReadAllSensor();
        // if (millis()- previous_sonar_read > 800)
        // {
        //   sonar_reading = HC_SR04_range(); //sonar read
        //   previous_sonar_read = millis();
        // }
      }
      stop();
      delay(100);
      strafe_left();
      delay(300);
      stop();
      movement_phase++;
      break;
    case 10:
      resetGyro();
      //third pass
      sonar_reading = HC_SR04_range();
      // resetGyro();
      //left side PID values
      Kp_IR_abs = 10;
      Ki_IR_abs = 0;
      Kp_IR_dif = 5;
      Ki_IR_dif = 0.8;

      Kp_GV_dif = 10;
      Ki_GV_dif = 1;

      PID_Zero();
      while(HC_SR04_range() > 10) //execute until it is 10cm away from wall
      {
        sonar_reading = HC_SR04_range();
        moving_alone_wall_middle(1,290,1,0, Kp_IR_abs, Ki_IR_abs, Kp_IR_dif,Ki_IR_dif,Kp_GV_dif, Ki_GV_dif);
        ReadAllSensor();
      }
      stop();
      delay(100);
      while (find_average_IR("2Y_04") < 390)
      {
        strafe_left();
      }
      stop();
      movement_phase++;
      break;
    case 11:
      resetGyro();
      //fourth pass
      sonar_reading = HC_SR04_range();
      // resetGyro();
      //left side PID values
      Kp_IR_abs = 10;
      Ki_IR_abs = 0;
      Kp_IR_dif = 5;
      Ki_IR_dif = 0.8;

      Kp_GV_dif = 0;
      Ki_GV_dif = 0;

      PID_Zero();
      while(HC_SR04_range() < 160) //execute until it is 10cm away from wall
      {
        sonar_reading = HC_SR04_range();
        moving_alone_wall_middle(-1,390,1,0, Kp_IR_abs, Ki_IR_abs, Kp_IR_dif,Ki_IR_dif,Kp_GV_dif, Ki_GV_dif);
        ReadAllSensor();
        // if (millis()- previous_sonar_read > 800)
        // {
        //   sonar_reading = HC_SR04_range(); //sonar read
        //   previous_sonar_read = millis();
        // }
      }
      stop();
      delay(100);
      while (find_average_IR("2Y_04") < 490)
      {
        strafe_left();
      }
      stop();
      movement_phase++;
      break;
    case 12:
      resetGyro();
      //Fifth pass
      sonar_reading = HC_SR04_range();
      // resetGyro();
      //left side PID values
      Kp_IR_abs = 10;
      Ki_IR_abs = 0;
      Kp_IR_dif = 4;
      Ki_IR_dif = 0.8;

      Kp_GV_dif = 0;
      Ki_GV_dif = 0;

      PID_Zero();
      while(HC_SR04_range() > 10) //execute until it is 10cm away from wall
      {
        sonar_reading = HC_SR04_range();
        moving_alone_wall_middle(1,490,1,0, Kp_IR_abs, Ki_IR_abs, Kp_IR_dif,Ki_IR_dif,Kp_GV_dif, Ki_GV_dif);
        ReadAllSensor();
      }
      stop();
      delay(100);
      movement_phase++;
      break;
    case 13:
      // Flip
      GyroTurn(180);
      while (find_average_IR("2Y_04") > 450)
      {
        strafe_left();
      }
      stop();
      forward();
      delay(150);
      resetGyro();
      delay(200);
      stop();
      movement_phase++;
    case 14:
      //sixth pass
      sonar_reading = HC_SR04_range();
      // resetGyro();
      //left side PID values
      Kp_IR_abs = 10;
      Ki_IR_abs = 0;
      Kp_IR_dif = 4;
      Ki_IR_dif = 0.8;

      Kp_GV_dif = 0;
      Ki_GV_dif = 0;

      PID_Zero();
      while(HC_SR04_range() > 10) //execute until it is 10cm away from wall
      {
        sonar_reading = HC_SR04_range();
        moving_alone_wall_middle(1,450,1,0, Kp_IR_abs, Ki_IR_abs, Kp_IR_dif,Ki_IR_dif,Kp_GV_dif, Ki_GV_dif);
        ReadAllSensor();
      }
      stop();
      delay(100);
      while (find_average_IR("2Y_04") > 390)
      {
        strafe_right();
      }
      stop();
      delay(100);
      stop();
      movement_phase++;
      break;
    case 15:
      //seventh pass
      sonar_reading = HC_SR04_range();
      //left side PID values
      Kp_IR_abs = 10;
      Ki_IR_abs = 0;
      Kp_IR_dif = 5;
      Ki_IR_dif = 0.8;

      Kp_GV_dif = 0;
      Ki_GV_dif = 0;

      PID_Zero();
      while(HC_SR04_range() < 160) //execute until it is 10cm away from wall
      {
        
        sonar_reading = HC_SR04_range(); //sonar read
        moving_alone_wall_middle(-1,390,1,0, Kp_IR_abs, Ki_IR_abs, Kp_IR_dif,Ki_IR_dif,Kp_GV_dif, Ki_GV_dif);
        ReadAllSensor();
      }
      stop();
      delay(100);
      while (find_average_IR("2Y_04") > 290)
      {
        strafe_right();
      }
      stop();
      movement_phase++;
      break;
    case 16:
    //8th pass
      sonar_reading = HC_SR04_range();
      //left side PID values
      Kp_IR_abs = 10;
      Ki_IR_abs = 0;
      Kp_IR_dif = 5;
      Ki_IR_dif = 0.8;

      Kp_GV_dif = 0;
      Ki_GV_dif = 0;

      PID_Zero();
      while(HC_SR04_range() > 10) //execute until it is 10cm away from wall
      {
        
        sonar_reading = HC_SR04_range(); //sonar read
        moving_alone_wall_middle(1,290,1,0, Kp_IR_abs, Ki_IR_abs, Kp_IR_dif,Ki_IR_dif,Kp_GV_dif, Ki_GV_dif);
        ReadAllSensor();
      }
      stop();
      while (find_average_IR("2Y_04") > 190)
      {
        strafe_right();
      }
      stop();
      movement_phase++;
      break;
    case 17:
      //9th pass
      sonar_reading = HC_SR04_range();
      //left side PID values
      Kp_IR_abs = 10;
      Ki_IR_abs = 0;
      Kp_IR_dif = 5;
      Ki_IR_dif = 0.8;

      Kp_GV_dif = 0;
      Ki_GV_dif = 0;

      PID_Zero();
      while(HC_SR04_range() < 160) //execute until it is 10cm away from wall
      {
        
        sonar_reading = HC_SR04_range(); //sonar read
        moving_alone_wall_middle(-1,190,1,0, Kp_IR_abs, Ki_IR_abs, Kp_IR_dif,Ki_IR_dif,Kp_GV_dif, Ki_GV_dif);
        ReadAllSensor();
      }
      stop();
      while (find_average_IR("2Y_04") > 120)
      {
        strafe_right();
      }
      stop();
      movement_phase++;
      break;
    case 18:
      //10th pass
      sonar_reading = HC_SR04_range();
      //left side PID values
      Kp_IR_abs = 20;
      Ki_IR_abs = 0;
      Kp_IR_dif = 20;
      Ki_IR_dif = 0;

      PID_Zero();
      while(HC_SR04_range() > 10) //execute until it is 10cm away from wall
      {
        sonar_reading = HC_SR04_range();
        moving_alone_wall(1,90,1,0, Kp_IR_abs, Ki_IR_abs, Kp_IR_dif,Ki_IR_dif);
        ReadAllSensor();
      }
      stop();
      delay(100);
      strafe_right();
      delay(100);
      stop();
      movement_phase++;
      break;

    default:
      stop();
      break;

  }
}