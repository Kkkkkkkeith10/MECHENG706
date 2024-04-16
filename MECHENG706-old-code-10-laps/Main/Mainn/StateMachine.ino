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
      movement_phase++;
      break;
    case 1:
      // Serial1.println(movement_phase);
      driveStrightUntilDistance(10);
      stop();
      movement_phase++;
      break;
    case 2:
      resetGyro();
      //delay(100);
      GyroTurn(90);
      //delay(100);
      movement_phase++;
      break;
    case 3:
      sonar_reading = HC_SR04_range(); //sonar read
      moving_alone_wall(10,90,0,0,1,1);
      //delay(100);
      movement_phase++;
      break;
    case 4:
      resetGyro();
      //delay(100);
      GyroTurn(90);

      movement_phase++;
      break;
    case 5:
      checkForLongSide();
      //no movement_phase++;
      break;
    case 6:
      //moving_alone_wall(-1,90,90,0,0,1);
      strafe_right();
      delay(2500);
      strafe_right_until(90, -1, 0);
      //delay(100);
      movement_phase = movement_phase + 2;
      break;
    case 7:
      resetGyro();
      GyroTurn(90);
      //delay(100);
      movement_phase++;
      break;
    case 8:
      sonar_reading = HC_SR04_range(); //sonar read
      moving_alone_wall(10,90,0,1,0,1);
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
      // reverse();
      // delay(50);
      stop();
      movement_phase++;
      break;
    case 10:
      //execute code
      //go straight along the 
      delay(400); //allow robot to settle
      sonar_reading = HC_SR04_range(); //sonar read
      resetGyro();
      delay(50);
      moving_alone_wall_middle(170,190,1,0, -1);
      movement_phase++;
      break;
    case 11:
      strafe_left();
      delay(300);
      // forward();
      // delay(50);
      stop();
      movement_phase++;
      break;
    case 12:
      delay(400); //allow robot to settle
      sonar_reading = HC_SR04_range(); //sonar read
      resetGyro();
      moving_alone_wall_middle(10,290,1,0,1);
      movement_phase++;
      break;
    case 13:
      strafe_left();
      delay(500);
      // reverse();
      // delay(50);
      stop();
      movement_phase++;
      break;
    case 14:
      delay(400);
      resetGyro();
      sonar_reading = HC_SR04_range();
      moving_alone_wall_middle(170,390,1,0,-1);
      movement_phase++;
      break;
    case 15:
      strafe_left();
      delay(200);
      // forward();
      // delay(50);
      stop();
      movement_phase++;
      break;
    case 16:
      delay(400);
      resetGyro();
      sonar_reading = HC_SR04_range();
      moving_alone_wall_middle(10,490,1,0,1);
      movement_phase++;
    case 17:
      // Serial1.println(movement_phase);
      strafe_left();
      delay(400);
      stop();
      GyroTurn(180);
      forward();
      delay(150);
      stop();
      movement_phase++;
    case 18:
      // Serial1.println(movement_phase);
      //delay(400); //allow robot to settle
      sonar_reading = HC_SR04_range(); //sonar read
      resetGyro();
      moving_alone_wall_middle(10,490,1,0,1);
      movement_phase++;
      break;
    case 19:
      strafe_right();
      delay(300);
      stop();
      movement_phase++;
      break;
    case 20:
      delay(400); //allow robot to settle
      sonar_reading = HC_SR04_range(); //sonar read
      resetGyro();
      moving_alone_wall_middle(170,390,1,0,-1);
      movement_phase++;
      break;
    case 21:
      strafe_right();
      delay(300);
      stop();
      movement_phase++;
      break;
    case 22:
      delay(400); //allow robot to settle
      sonar_reading = HC_SR04_range(); //sonar read
      resetGyro();
      moving_alone_wall_middle(10,290,1,0,1);
      movement_phase++;
      break;
    case 23:
      strafe_right();
      delay(300);
      stop();
      movement_phase++;
      break;
    case 24:
      delay(500); //allow robot to settle
      sonar_reading = HC_SR04_range(); //sonar read
      resetGyro();
      moving_alone_wall_middle(160,200,1,0,-1);
      movement_phase++;
      break;
    case 25:
      // Serial1.println(movement_phase);
      sonar_reading = HC_SR04_range(); //sonar read
      moving_alone_wall(10,100,0,1,0,1);
      movement_phase++;
      break;

    default:
      stop();
      break;

  }
}