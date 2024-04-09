//this file contains functions for finding the corner 
//It does so by measuring the distance of the sonar, until the rate of change of distance has an inflexion point, this is then the corner


void findCorner() 
{
    const int readingsCount = 20;
    float pastReadings[readingsCount] = {0};
    float currentReadings[readingsCount];
    float pastAverage, currentAverage;

    // Initialize past readings, assuming you have a way to fill this up before the loop starts
    for (int i = 0; i < readingsCount; ++i) {
        pastReadings[i] = HC_SR04_range();
        delay(5); // Initial delay to fill the past readings
    }

    while (true) {  // Replace true with a condition to stop if necessary
      ccw_low();
        pastAverage = 0;
        currentAverage = 0;

        // Get current 5 readings with a delay between each
        for (int i = 0; i < readingsCount; ++i) {
            currentReadings[i] = HC_SR04_range();
            delay(5); // Delay for 20 milliseconds
        }

        // Calculate the averages
        for (int i = 0; i < readingsCount; ++i) {
            pastAverage += pastReadings[i];
            currentAverage += currentReadings[i];
        }
        pastAverage /= readingsCount;
        currentAverage /= readingsCount;

        // Determine whether to continue rotating or stop
        if (currentAverage < pastAverage) {
            ccw_low();  // If the average distance is not increasing, continue rotating
        } else {
            stop();  // If the average distance is increasing, stop
            break;  // Exit the loop if you want to stop checking after stopping
        }

        // Update past readings for the next iteration
        for (int i = 0; i < readingsCount; ++i) {
            pastReadings[i] = currentReadings[i];
        }
    }
    while (true) {  // Replace true with a condition to stop if necessary
     cw_low();
        pastAverage = 0;
        currentAverage = 0;

        // Get current 5 readings with a delay between each
        for (int i = 0; i < readingsCount; ++i) {
            currentReadings[i] = HC_SR04_range();
            delay(5); // Delay for 20 milliseconds
        }

        // Calculate the averages
        for (int i = 0; i < readingsCount; ++i) {
            pastAverage += pastReadings[i];
            currentAverage += currentReadings[i];
        }
        pastAverage /= readingsCount;
        currentAverage /= readingsCount;

        // Determine whether to continue rotating or stop
        if (currentAverage < pastAverage) {
            cw_low();  // If the average distance is not increasing, continue rotating
        } else {
            stop();  // If the average distance is increasing, stop
            break;  // Exit the loop if you want to stop checking after stopping
        }

        // Update past readings for the next iteration
        for (int i = 0; i < readingsCount; ++i) {
            pastReadings[i] = currentReadings[i];
        }
    }
    currentState++; //will move out of here eventually
}


