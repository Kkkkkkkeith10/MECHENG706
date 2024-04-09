//this file contains functions for finding the corner 

void find_normal()
{
  int direction;
  int prev_direction;
  float millis_prev = 0;
  bool found_normal = false;
  int thresh = 1;

  //initialize it spinning
  ccw_low();
  //take some initial readings
  for (int i = 0; i < 6; i++)
  {
      sonar_reading_prev5 = sonar_reading_prev4;
      sonar_reading_prev4 = sonar_reading_prev3;
      sonar_reading_prev3 = sonar_reading_prev2;
      sonar_reading_prev2 = sonar_reading_prev1;
      sonar_reading_prev1 = sonar_reading;
      sonar_reading = HC_SR04_range(); //sonar read
      //update the average reading of the sensor
      sonar_average_prev1 = sonar_average;
      sonar_average = (sonar_reading_prev3+sonar_reading_prev4+sonar_reading_prev5+sonar_reading_prev2 + sonar_reading_prev1 + sonar_reading)/6;
      //determine direction
      if (sonar_average-sonar_average_prev1 > thresh)
      {
        //distance increasing
        prev_direction = direction;
        direction = 1;
      }
      else if (sonar_average-sonar_average_prev1 < -thresh)
      {
        //distance decreasing
        prev_direction = direction;
        direction = 0;

      }
    }

    
  Serial1.println("searching");
  //while not found normal
  while (found_normal == false)
  {
    //update sonar reading every 200ms
      sonar_reading_prev5 = sonar_reading_prev4;
      sonar_reading_prev4 = sonar_reading_prev3;
      sonar_reading_prev3 = sonar_reading_prev2;
      sonar_reading_prev2 = sonar_reading_prev1;
      sonar_reading_prev1 = sonar_reading;
      sonar_reading = HC_SR04_range(); //sonar read
      //update the average reading of the sensor
      sonar_average_prev1 = sonar_average;
      sonar_average = (sonar_reading_prev3+sonar_reading_prev4+sonar_reading_prev5+sonar_reading_prev2 + sonar_reading_prev1 + sonar_reading)/6;
      //determine direction
      if (sonar_average-sonar_average_prev1 > thresh)
      {
        //distance increasing
        prev_direction = direction;
        direction = 1;
      }
      else if (sonar_average-sonar_average_prev1 < -thresh)
      {
        //distance decreasing
        prev_direction = direction;
        direction = 0;

      }
      millis_prev = millis();
    
    Serial1.println(sonar_average-sonar_average_prev1);
    if (prev_direction != direction)
    {
      stop();
      movement_phase++;
      found_normal = true;
    }
  }
}



