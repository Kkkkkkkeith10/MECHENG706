//This file implements the state machines used for control flow of the robot when it's executing it's task. It executes project 1 of ME706

void execute_movement_phase()
{
  switch (movement_phase)
  {
    case 0:
      //find normal
      find_normal();
      break;
    case 1:
      //execute code
      break;
    case 2:
      //execute code
      //go straight along the 
      break;

    default:
      stop();
      break;

  }
}