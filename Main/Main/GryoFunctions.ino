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
  Serial.println("please keep the sensor still for calibration");
  Serial.println("get the gyro zero voltage");
  for (i = 0; i < 100; i++) // read 100 values of voltage when gyro is at still, to calculate the zero-drift
  {
    sensorValue = analogRead(sensorPin);
    sum += sensorValue;
    delay(5);
  }
  gyroZeroVoltage = sum / 100; // average the sum as the zero drifting
}

void readGyro1()
{
  GyroTimeNow = (float)millis() / 1000;

  gyroRate = (analogRead(sensorPin) * gyroSupplyVoltage) / 1023; // find the voltage offset the value of voltage when gyro is zero (still)

  gyroRate -= (gyroZeroVoltage / 1023 * 5);

  float angularVelocity = gyroRate / gyroSensitivity; // read out voltage divided the gyro sensitivity to calculate the angular velocity

  // if the angular velocity is less than the threshold, ignore it
  if (angularVelocity >= rotationThreshold || angularVelocity <= -rotationThreshold)
  {
    // we are running a loop in T. one second will run (1000/T).
    float angleChange = -angularVelocity * (GyroTimeNow - GyroTimePrevious);
    currentAngle += angleChange -0.003;
  }
  char message[8];
  dtostrf(currentAngle,6,2,message);
  BluetoothSerial.println(currentAngle);
  GyroTimePrevious = GyroTimeNow;
}