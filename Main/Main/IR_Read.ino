//This file contains the IR sensor conversion. 

//----------------------Sensor Reading & conversion to mm-------------------------

double IR_sensorReadDistance(String sensor)
// input can be : "41_01", "04_02", "02_01", "02_02", "02_03", "02_04",
// return distance in mm
{
  double distance;
  double sensor_value;
  if (sensor == "41_01")
  {
    sensor_value = analogRead(IR_41_01);
    distance = 27592 * pow(sensor_value, -1.018);
  }
  else if (sensor == "41_02")
  {
    sensor_value = analogRead(IR_41_02);
    distance = 7935.4 * pow(sensor_value, -0.827);
  }
  else if (sensor == "41_03")
  {
    sensor_value = analogRead(IR_41_03);
    distance = 30119 * pow(sensor_value, -1.039);
  }
  // else if(sensor == "2Y_01")
  // {
  //   sensor_value = analogRead(IR_2Y_01);
  //   distance = 1888777 * pow(sensor_value, -1.237);
  // }
  else if (sensor == "2Y_02")
  {
    sensor_value = analogRead(IR_2Y_02);
    distance = 92838 * pow(sensor_value, -1.097);
  }
  // else if(sensor = "2Y_03")
  // {
  //   sensor_value = analogRead(IR_2Y_03);
  //   distance = 7927.4 * pow(sensor_value, -0.687);
  // }
  else if (sensor = "2Y_04")
  {
    sensor_value = analogRead(IR_2Y_04);
    distance = 50857 * pow(sensor_value, -0.994);
  }
  else
  {
    BluetoothSerial.println("Invalid sensor");
    distance = 0;
  }
  return distance;
}

