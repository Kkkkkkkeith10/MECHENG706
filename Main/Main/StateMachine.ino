//This file implements the state machines used for control flow of the robot when it's executing it's task. It executes project 1 of ME706

void execute_movement_phase()
{
  switch (movement_phase)
  {
    case 0:
      //initialize the spinning
      static unsigned long execution_time;
      ccw();
      if (millis()- execution_time > 500)
      {
        movement_phase = 1;
      }
      //scan
      //execute code
      //find corner
      break;
    case 1:
      //execute code
      find_normal();
      //position along long side
      //BluetoothSerial.println("Phase 1");
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