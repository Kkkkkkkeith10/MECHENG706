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
      moving_alone_wall(10,90,0,0,1);
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
      moving_alone_wall(10,90,0,0,1);
      delay(100);
      movement_phase++;
      break;
    case 7:
    resetGyro();
      GyroTurn(90);
      delay(100);
      movement_phase++;
      break;




    case 8:

      moving_alone_wall(10,90,0,1,0);
      movement_phase++;

      // while(1)
      // {
      // MoveStraightPID(100);
      // }
      // static unsigned long previous_sensor_read;
      // if (millis()-previous_sensor_read > 250)
      // {
      //   Serial1.println(IR_sensorReadDistance("2Y_02"));//right long range
      //   // Serial1.println(IR_sensorReadDistance("2Y_04"));//left long range
      //   previous_sensor_read = millis();
      // }
      
      // moving_alone_wall_middle(10,350,0,1);
      break;
    case 9:
      // driveStrightUntilDistance(10);
      // Serial1.println(movement_phase);
      //execute code
      strafe_left();
      delay(500);
      stop();
      movement_phase++;
      break;
    case 10:
      //execute code
      //go straight along the 
      delay(500); //allow robot to settle
      sonar_reading = HC_SR04_range(); //sonar read
      resetGyro();
      moving_alone_wall_middle(160,255,1,0, -1);
      movement_phase++;
      break;
    case 11:
      strafe_left();
      delay(300);
      stop();
      movement_phase++;
      break;
    case 12:
      // delay(100);
      delay(500); //allow robot to settle
      resetGyro();
      sonar_reading = HC_SR04_range(); //sonar read
      resetGyro();
      moving_alone_wall_middle(10,450,1,0,1);
      movement_phase++;
      break;
    case 13:
      strafe_left();
      delay(500);
      stop();
      movement_phase++;
      break;
    case 14:
      // Serial1.println(movement_phase);
      GyroTurn(180);
      forward();
      delay(150);
      stop();
      movement_phase++;
    case 15:
      // Serial1.println(movement_phase);
      delay(500); //allow robot to settle
      sonar_reading = HC_SR04_range(); //sonar read
      resetGyro();
      moving_alone_wall_middle(10,450,1,0,1);
      movement_phase++;
      break;
    case 16:
      strafe_right();
      delay(300);
      stop();
      movement_phase++;
      break;
    case 17:
      delay(500); //allow robot to settle
      sonar_reading = HC_SR04_range(); //sonar read
      resetGyro();
      moving_alone_wall_middle(160,255,1,0,-1);
      movement_phase++;
      break;
    case 18:
      // Serial1.println(movement_phase);
      moving_alone_wall(10,90,0,1,0);
      movement_phase++;
      break;

    default:
      stop();
      break;

  }
}