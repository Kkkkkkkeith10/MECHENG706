//This file contains serial functions


// Serial command pasing for serial move
void interpret_command(char command)
{
    // Perform an action depending on the command
    switch (command)
    {
    case 'w': // Move Forward
    case 'W':
      forward();
      break;
    case 's': // Move Backwards
    case 'S':
      reverse();
      break;
    case 'q': // Turn Left
    case 'Q':
      strafe_left();
      break;
    case 'e': // Turn Right
    case 'E':
      strafe_right();
      break;
    case 'a': // Turn Right
    case 'A':
      ccw();
      break;
    case 'd': // Turn Right
    case 'D':
      cw();
      break;
    case '-': // Turn Right
    case '_':
      speed_change = -100;
      break;
    case '=':
    case '+':
      speed_change = 100;
      break;
    default:
      stop();
      //SerialCom->println("stop");
      break;
    }
}
