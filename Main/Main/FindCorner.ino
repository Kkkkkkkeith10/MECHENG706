//this file contains functions for finding the corner 
//It does so by measuring the distance of the sonar, until the rate of change of distance has an inflexion point, this is then the corner



  // if (millis() - previous_millis_sonar_read > 110)
  // {
  //   previous_millis_sonar_read = millis();
  //   //store the previous 3 sonar readings
  //   #ifndef NO_HC - SR04
  //   sonar_reading_prev2 = sonar_reading_prev1;
  //   sonar_reading_prev1 = sonar_reading;
  //   sonar_reading = HC_SR04_range(); //sonar read
  //   //update the average reading of the sensor
  //   sonar_average_prev1 = sonar_average;
  //   sonar_average = (sonar_reading_prev2 + sonar_reading_prev1 + sonar_reading)/3;
  //   #endif
  // }



void find_normal()
{
  float millis_prev = 0;
  bool found_normal = false;
  //initialize it spinning
  ccw_low();
  delay(200);

  //while not found normal
  while (bool found_normal = false)
  {
    //update sonar reading every 10ms
    if (millis() - millis_prev > 10)
    {
      sonar_reading_prev2 = sonar_reading_prev1;
      sonar_reading_prev1 = sonar_reading;
      sonar_reading = HC_SR04_range(); //sonar read
      //update the average reading of the sensor
      sonar_average_prev1 = sonar_average;
      sonar_average = (sonar_reading_prev2 + sonar_reading_prev1 + sonar_reading)/3;
    }

    if (sonar_average > sonar_average_prev1)
    {
      //do nothing
    }
    else
    {
      stop();
      found_normal = true;
      movement_phase = 1;
    }
    char message[8];
    dtostrf((sonar_average-sonar_average_prev1),6,2,message);
    Serial1.println(message);

  }
}

//   float threathod = 0.2;  //mm
//   float current_ave_distance = find_average_distance();
//   float previous_ave_distance = current_ave_distance + 1;

//   ccw_low();
//   delay(200);
//   stop();
//   while ((current_ave_distance - previous_ave_distance) < threathod)
//   {
//     ccw_low();
//     delay(100);
//     stop();
//     previous_ave_distance = current_ave_distance;
//     current_ave_distance = find_average_distance();
//   }
//   stop();

//   cw_low();
//   delay(200);
//   stop();
//   previous_ave_distance = current_ave_distance;
//   current_ave_distance = find_average_distance();
//   while((current_ave_distance - previous_ave_distance) < threathod)
//   {
//     cw_low();
//     delay(100);
//     stop();
//     previous_ave_distance = current_ave_distance;
//     current_ave_distance = find_average_distance();
//   }
//   stop();
// }

// float find_average_distance()
// {
//   float distances = 0.0;
//   float reading;

//   for (i = 0; i <= 9; i++)
//   {
//     reading = HC_SR04_range();
//     distances += reading;
//     delay(5);
//   }
//   distances = distances/10;
//   return distances;
// }

