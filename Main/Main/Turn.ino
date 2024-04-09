//This file contains functions for turning the robot a specified amount

void turnAngleWithGyro(float angle, float millisecond)
{
  readGyro();
  float target = currentAngle + angle;
  float torlance = 10; // degree
  unsigned long timeAtDestination = millis() + millisecond;

  while (millis() < timeAtDestination)
  {
    readGyro();
    SerialCom->print(currentAngle);
    SerialCom->print(" ");

    if ((currentAngle < (torlance + target)) && (currentAngle > (-torlance + target)))
    {
      forward();
      SerialCom->println("forward");
    }
    else if ((currentAngle > (torlance + target)) && (currentAngle < (180 + target)))
    {
      ccw();
      SerialCom->println("ccw");
    }
    else
    {
      cw();
      SerialCom->println("cw");
    }

    delay(40);
  }
}




void trunDegree(float TargetAngle_Degree )
{
  float Power = 100;
  float torlance = 0.5;
  currentAngle =0;
  while ((currentAngle < TargetAngle_Degree - torlance) || (currentAngle > TargetAngle_Degree + torlance))
  {
    SerialCom->println(currentAngle);
    readGyro1();
    if(currentAngle < TargetAngle_Degree - torlance){
      ccw();
    }else{
      cw();
    }
  }
  stop();

  
  currentState++;
}
