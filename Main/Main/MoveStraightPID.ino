//this file contains functions which use only the gyro to move straight

void MoveStraightPID(float Power)
{
  SVRF = (int)500*(Power/100);
  SVRR = SVRF;
  SVLF = -SVRF;
  SVLR = -SVRF;

  readGyro1();
  //currentAngle -= offset_angle;
  ErrorAngle_Degree = currentAngle;
  SV_P = KP*ErrorAngle_Degree;

  SVRF += SV_P;
  SVRR += SV_P;
  SVLF += SV_P;
  SVLR += SV_P;

  SVRF = saturation(SVRF);
  SVRR = saturation(SVRR);
  SVLF = saturation(SVLF);
  SVLR = saturation(SVLR);

  // Serial.println(currentAngle);
  // Serial.print(" ");
  // Serial.print(ErrorAngle_Degree);
  // Serial.print(" ");
  // Serial.print(SV_P);
  // Serial.print(" ");
  // Serial.print(1500 + SVRR);
  // Serial.print(" ");
  // Serial.print(1500 + SVRF);
  // Serial.print(" ");
  // Serial.print(1500 + SVLF);
  // Serial.print(" ");
  // Serial.println(1500 + SVLR);


  left_font_motor.writeMicroseconds(1500 + SVLF);
  left_rear_motor.writeMicroseconds(1500 + SVLR);
  right_rear_motor.writeMicroseconds(1500 + SVRR);
  right_font_motor.writeMicroseconds(1500 + SVRF);

  delay(50);
}


void MoveStraightAlongAngle(float TargetAngle_Degree, float Power)
{
  SVRF = (int)300 * (Power / 100);
  SVRR = SVRF;
  SVLF = SVRF;
  SVLR = SVRF;

  TargetAngle_Radius = 2 * 3.1415926 * TargetAngle_Degree / (float)360.0;
  ///(float)360

  SVRR = SVRR * (cos(TargetAngle_Radius) - sin(TargetAngle_Radius));
  SVRF = SVRF * (cos(TargetAngle_Radius) + sin(TargetAngle_Radius));
  SVLF = -SVLF * (cos(TargetAngle_Radius) - sin(TargetAngle_Radius));
  SVLR = -SVLR * (cos(TargetAngle_Radius) + sin(TargetAngle_Radius));

  readGyro1();
  ErrorAngle_Radius = TargetAngle_Radius - (2 * 3.1415926 * currentAngle / 360 + TargetAngle_Radius);
  SV_P = -Kp * ErrorAngle_Radius;

  SVRF += SV_P;
  SVRR += SV_P;
  SVLF += SV_P;
  SVLR += SV_P;

  SVRF = saturation(SVRF);
  SVRR = saturation(SVRR);
  SVLF = saturation(SVLF);
  SVLR = saturation(SVLR);

  left_font_motor.writeMicroseconds(1500 + SVLF);
  left_rear_motor.writeMicroseconds(1500 + SVLR);
  right_rear_motor.writeMicroseconds(1500 + SVRR);
  right_font_motor.writeMicroseconds(1500 + SVRF);

  // Serial.print(currentAngle);
  // Serial.print(" ");
  // Serial.print(TargetAngle_Radius);
  // Serial.print(" ");
  // Serial.print(ErrorAngle_Radius);
  // Serial.print(" ");
  // Serial.print(SV_P);
  // Serial.print(" ");
  // Serial.print(SVRR);
  // Serial.print(" ");
  // Serial.print(SVRF);
  // Serial.print(" ");
  // Serial.print(SVLF);
  // Serial.print(" ");
  // Serial.println(SVLR);

  delay(20);
}


int saturation(int value)
{
  if (value > 500)
  {
    return 500;
  }
  else if (value < -500)
  {
    return -500;
  }
  else
  {
    return value;
  }
}


void driveStrightUntilDistance(int cm)
{
  readGyro1();
  currentAngle=0;
  float torlance = 0.5; // degree
  

  while (HC_SR04_range() > cm)
  {
    MoveStraightPID(100);
    delay(20);
  }
  currentState++;
  stop();
}

void driveStringhtForDistance(int cm)
{
  readGyro();
  currentAngle=0;
  float torlance = 3; // degree
  float currentDistance = HC_SR04_range();

  while (HC_SR04_range() > (currentDistance - cm))
  {
    MoveStraightAlongAngle(0, 100);
  }
  currentState++;
  stop();
}

