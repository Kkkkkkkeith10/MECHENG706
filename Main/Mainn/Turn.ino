//This file contains functions for turning the robot a specified amount

void turnAngleWithGyro(float angle, float millisecond)
{
  readGyroTurn();
  float target = currentAngle + angle;
  float torlance = 10; // degree
  unsigned long timeAtDestination = millis() + millisecond;

  while (millis() < timeAtDestination)
  {
    readGyroTurn();
    Serial1.print(currentAngle);
    Serial1.print(" ");

    if ((currentAngle < (torlance + target)) && (currentAngle > (-torlance + target)))
    {
      forward();
      Serial1.println("forward");
    }
    else if ((currentAngle > (torlance + target)) && (currentAngle < (180 + target)))
    {
      ccw();
      Serial1.println("ccw");
    }
    else
    {
      cw();
      Serial1.println("cw");
    }

    delay(40);
  }
}




void trunDegree(float TargetAngle_Degree )
{
  //Serial1.println(movement_phase);
  float Power = 100;
  float torlance = 0.5;
  currentAngle =0;
  while ((currentAngle < TargetAngle_Degree - torlance) || (currentAngle > TargetAngle_Degree + torlance))
  {
    //Serial1.println(currentAngle);
    readGyro1();
    //Serial1.println(currentAngle);
    if(currentAngle < TargetAngle_Degree - torlance){
      ccw();
    }else{
      cw();
    }
  }
  stop();
}
