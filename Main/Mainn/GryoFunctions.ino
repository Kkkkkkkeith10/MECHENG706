//This file contains all helper functions for the Gyro


void readGyro()
{
  
  int T = 50;
  gyroRate = (analogRead(sensorPin) * gyroSupplyVoltage) / 1023;
  // find the voltage offset the value of voltage when gyro is zero (still)
  gyroRate -= (gyroZeroVoltage / 1023 * 5);
  // read out voltage divided the gyro sensitivity to calculate the angular velocity
  float angularVelocity = gyroRate / gyroSensitivity;
  // if the angular velocity is less than the threshold, ignore it
  if (angularVelocity >= rotationThreshold || angularVelocity <= -rotationThreshold)
  {
    // we are running a loop in T. one second will run (1000/T).
    float angleChange = angularVelocity / (1000 / T);
    currentAngle += angleChange +0.1;
  }
  // keep the angle between 0-360
  if (currentAngle < 0)
  {
    currentAngle += 360;
  }
  else if (currentAngle > 359)
  {
    currentAngle -= 360;
  }
}



void resetGyro()
{
  long sum = 0;
  for (int i = 0; i < 100; i++) // read 100 values of voltage when gyro is at still, to calculate the zero-drift
  {
    sensorValue = analogRead(sensorPin);
    // Serial1.print("delta sum: ");
    // Serial1.println(sensorValue);
    sum += sensorValue;
    // Serial1.print("sum: ");
    // Serial1.println(sum);
    delay(5);
  }
  gyroZeroVoltage = int(sum / 100); // average the sum as the zero drifting
  Serial1.println(gyroZeroVoltage);
}

void readGyro1()
{
  //Serial1.println(analogRead(sensorPin));
  GyroTimeNow = (float)millis() / 1000;
  gyroRate = (analogRead(sensorPin) * gyroSupplyVoltage) / 1023; // find the voltage offset the value of voltage when gyro is zero (still)
  gyroRate -= (gyroZeroVoltage / 1023 * 5); //5 is the number of ms delay the gryozerovoltage is taken over
  float angularVelocity = gyroRate / gyroSensitivity; // read out voltage divided the gyro sensitivity to calculate the angular velocity
  // if the angular velocity is less than the threshold, ignore it
  if (angularVelocity >= rotationThreshold || angularVelocity <= -rotationThreshold)
  {
    // we are running a loop in T. one second will run (1000/T).
    float angleChange = -angularVelocity * (GyroTimeNow - GyroTimePrevious); //calculate the angle change based on the angular velocity
    currentAngle += angleChange; //0.003 is a compensation factor obtained through tuning
  }
  GyroTimePrevious = GyroTimeNow;
}
void readGyroTurn()
{
  //Serial1.println(analogRead(sensorPin));
  GyroTimeNow = (float)millis() / 1000;
  gyroRate = (analogRead(sensorPin) * gyroSupplyVoltage) / 1023; // find the voltage offset the value of voltage when gyro is zero (still)
  gyroRate -= (gyroZeroVoltage / 1023 * 5); //5 is the number of ms delay the gryozerovoltage is taken over
  float angularVelocity = gyroRate / gyroSensitivity; // read out voltage divided the gyro sensitivity to calculate the angular velocity
  // if the angular velocity is less than the threshold, ignore it
  if (angularVelocity >= rotationThreshold || angularVelocity <= -rotationThreshold)
  {
    // we are running a loop in T. one second will run (1000/T).
    float angleChange = -angularVelocity * (GyroTimeNow - GyroTimePrevious);
    if(angleChange != 0){
          currentAngle += angleChange +0.029*(abs(angleChange)/angleChange) ; //0.003 is a compensation factor obtained through tuning
    } //calculate the angle change based on the angular velocity

  }
  GyroTimePrevious = GyroTimeNow;
}