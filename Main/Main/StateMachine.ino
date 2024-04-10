//This file implements the state machines used for control flow of the robot when it's executing it's task. It executes project 1 of ME706

void execute_movement_phase()
{ 
  //state0: scan for normal
  //state1: drive to wall
  //state2: turn until parallel
  //state3: drive to corner
  //state4: determine which side is the long side, short => state5, long=>state6
  //state5: (if facing short side) drive to corner, next state => state6
  //state6(main start): (if facing long side, start main), 
  switch (movement_phase)
  {
    case 0:
      //find normal
      // find_normal();
      scan_until_normal();
      // sonar_reading = HC_SR04_range(); //sonar read
      // Serial1.println(sonar_reading);

      break;
    case 1:
      driveStrightUntilDistance(15);
      //execute code
      break;
    case 2:
      //execute code
      //go straight along the 
      trunDegree(90);
      break;

    case 3:
      homing_normal_system(0,0,0,1,6);
      break;
    case 4:
      moving_alone_wall_until_cm(15,150,0, 0,1);
      break;
    default:
      stop();
      break;

  }
}