//This file implements the state machines used for control flow of the robot when it's executing it's task. It executes project 1 of ME706

void execute_movement_phase()
{
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
      driveStrightUntilDistance(20);
      //execute code
      break;
    case 2:
      //execute code
      //go straight along the 
      trunDegree(-90);
      break;
    
    default:
      stop();
      break;

  }
}