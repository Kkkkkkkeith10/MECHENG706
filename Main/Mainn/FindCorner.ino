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



void scan_until_normal()
{
  float threathod = 0.2;  //mm
  float current_ave_distance = find_average_distance();
  float previous_ave_distance = current_ave_distance + 1;

  ccw_low();
  delay(50);
  stop();
  while ((current_ave_distance - previous_ave_distance) < threathod)
  {
    ccw_low();
    delay(20);
    stop();
    previous_ave_distance = current_ave_distance;
    current_ave_distance = find_average_distance();
  }
  stop();

  cw_low();
  delay(200);
  stop();
  previous_ave_distance = current_ave_distance;
  current_ave_distance = find_average_distance();
  while((current_ave_distance - previous_ave_distance) < threathod)
  {
    cw_low();
    delay(20);
    stop();
    previous_ave_distance = current_ave_distance;
    current_ave_distance = find_average_distance();
  }
  stop();
  movement_phase++;
}

float find_average_distance()
{
  float distances = 0.0;
  float reading;
  int i = 0;
  for (i = 0; i <= 9; i++)
  {
    reading = HC_SR04_range();
    distances += reading;
    delay(5);
  }
  distances = distances/10;
  return distances;
}

