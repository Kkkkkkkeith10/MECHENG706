//This file contains all helper functions for the Gyro


// void readGyro()
// {
//   int T = 50;
//   gyroRate = (analogRead(sensorPin) * gyroSupplyVoltage) / 1023;
//   // find the voltage offset the value of voltage when gyro is zero (still)
//   gyroRate -= (gyroZeroVoltage / 1023 * 5);
//   // read out voltage divided the gyro sensitivity to calculate the angular velocity
//   float angularVelocity = gyroRate / gyroSensitivity;
//   // if the angular velocity is less than the threshold, ignore it
//   if (angularVelocity >= rotationThreshold || angularVelocity <= -rotationThreshold)
//   {
//     // we are running a loop in T. one second will run (1000/T).
//     float angleChange = angularVelocity / (1000 / T);
//     currentAngle += angleChange +0.1;
//   }
//   // keep the angle between 0-360
//   if (currentAngle < 0)
//   {
//     currentAngle += 360;
//   }
//   else if (currentAngle > 359)
//   {
//     currentAngle -= 360;
//   }
// }



void resetGyro()
{
  int sum = 0;
  for (int i = 0; i < 100; i++) // read 100 values of voltage when gyro is at still, to calculate the zero-drift
  {
    sensorValue = analogRead(sensorPin);
    sum += sensorValue;
    delay(5);
  }
  gyroZeroVoltage = sum / 100; // average the sum as the zero drifting
}

void readGyro1(float timeDif)
{
  gyroRate = (analogRead(sensorPin) * gyroSupplyVoltage) / 1023; // find the voltage offset the value of voltage when gyro is zero (still)
  gyroRate -= (gyroZeroVoltage / 1023 * 5); //5 is the number of ms delay the gryozerovoltage is taken over
  float angularVelocity = gyroRate / gyroSensitivity; // read out voltage divided the gyro sensitivity to calculate the angular velocity
  // if the angular velocity is less than the threshold, ignore it
  if (angularVelocity >= rotationThreshold || angularVelocity <= -rotationThreshold)
  {
    // we are running a loop in T. one second will run (1000/T).
    float angleChange = -angularVelocity * (timeDif); //calculate the angle change based on the angular velocity
    currentAngle += angleChange -0.003; //0.003 is a compensation factor obtained through tuning
  }
}