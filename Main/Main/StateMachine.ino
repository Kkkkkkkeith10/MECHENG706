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
      scan_until_normal();
      Serial1.println(movement_phase);
      // sonar_reading = HC_SR04_range(); //sonar read
      // Serial1.println(sonar_reading);

      break;
    case 1:
      driveStrightUntilDistance(10);
      Serial1.println(movement_phase);
      //execute code
      break;
    case 2:
      //execute code
      //go straight along the 
      trunDegree(-90);
      Serial1.println(movement_phase);
      break;
    case 3:
      homing_normal_system(0,0,0,1,6);
      Serial1.println(movement_phase);
      break;
    case 4:
      moving_alone_wall_until_cm(20,100,0, 1,0);
      Serial1.println(movement_phase);
      break;
    case 5:
      trunDegree(-90);
      Serial1.println(movement_phase);
      break;
    case 6:
      checkForLongSide();
      Serial1.println(movement_phase);
      break;
    case 7:
      driveStrightUntilDistance(10);
      Serial1.println(movement_phase);
      break;
    case 8:
      trunDegree(-90);
      Serial1.println(movement_phase);
      break;
    case 9:
      driveStrightUntilDistance(10);
      Serial1.println(movement_phase);
      break;
    case 10:
      trunDegree(-90);
      Serial1.println(movement_phase);
      break;
    case 11:
      driveStringhtForDistance(10);
      Serial1.println(movement_phase);
      break;
    case 12:
      trunDegree(-90);
      Serial1.println(movement_phase);
      break;
    case 13:
      driveStrightUntilDistance(10);
      Serial1.println(movement_phase);
      break;
    case 14:
      trunDegree(90);
      Serial1.println(movement_phase);
      break;
    case 15:
      driveStringhtForDistance(10);
      Serial1.println(movement_phase);
      break;
    case 16:
      trunDegree(90);
      Serial1.println(movement_phase);
      break;
    case 17:
      movement_phase = 9;
      break;
    


    
    default:
      stop();
      break;

  }
}