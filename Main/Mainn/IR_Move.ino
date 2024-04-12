//This file contains a function which uses the IR distance only to move the car.

//-------------------------------Car Movement-----------------------------------
void Car_Move_withIRSensor(String left_front_IR, String left_back_IR, String right_front_IR, String right_back_IR)
{
  float torlance = 3; // mm

  float left_front_distance = IR_sensorReadDistance(left_front_IR);
  float left_back_distance = IR_sensorReadDistance(left_back_IR);
  float right_front_distance = IR_sensorReadDistance(right_front_IR);
  float right_back_distance = IR_sensorReadDistance(right_back_IR);

  // demo only, only work with left sensor
  // need to be modified after logic of car movement is determined
  if (left_front_distance - left_back_distance > torlance)
  {
    ccw();
  }
  else if (left_back_distance - left_front_distance > torlance)
  {
    cw();
  }
  else
  {
    forward();
  }
}