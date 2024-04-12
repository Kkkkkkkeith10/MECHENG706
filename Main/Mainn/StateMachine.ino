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
    Serial1.println(movement_phase);
    case 0:
      //find normal
      // find_normal();
      // scan_until_normal();
      // Serial1.println(movement_phase);
      // sonar_reading = HC_SR04_range(); //sonar read
      // Serial1.println(sonar_reading);
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
    case 1:
      // driveStrightUntilDistance(10);
      // Serial1.println(movement_phase);
      //execute code
      strafe_left();
      delay(200);
      stop();
      movement_phase++;
      break;
    case 2:
      //execute code
      //go straight along the 
      GyroTurn(180);
      movement_phase++;
      break;
    case 3:
      forward();
      delay(200);
      stop();
      resetGyro();
      // reverse();
      // delay(200);
      // cw();
      // delay(10);
      movement_phase++;
      break;
    case 4:
      delay(100);
      moving_alone_wall_middle(10,255,0,1);
      movement_phase++;
      break;
    case 5:
      // driveStrightUntilDistance(10);
      // Serial1.println(movement_phase);
      //execute code
      strafe_right();
      delay(200);
      stop();
      movement_phase++;
      break;
    case 6:
      //execute code
      //go straight along the 
      GyroTurn(180);
      movement_phase++;
      break;
    case 7:
      forward();
      delay(400);
      stop();
      resetGyro();
      // reverse();
      // delay(200);
      // cw();
      // delay(10);
      movement_phase++;
      break;
    case 8:
      moving_alone_wall_middle(10,255,1,0);
      movement_phase++;
      break;
    


    
    default:
      stop();
      break;

  }
}