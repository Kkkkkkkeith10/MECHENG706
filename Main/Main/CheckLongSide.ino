//This file checks for the long side

void checkForLongSide()
{
  const int readingsCount = 5;
  float sum = 0;
  float average = 0;

  // Take 5 readings, with a 20ms delay between each
  for (int i = 0; i < readingsCount; ++i) {
      sum += HC_SR04_range();  // Assuming HC_SR04_range() returns distance in cm
      delay(20);  // Delay for 20 milliseconds
  }

  // Calculate the average distance
  average = sum / readingsCount;

  // Convert average to meters for comparison (1cm = 0.01m)
  average /= 100.0;  // Convert cm to meters

  // Update currentStats based on the average distance
  if (average < 1.2) {
      currentState += 1;
  } else {
      currentState += 2;
  }
}