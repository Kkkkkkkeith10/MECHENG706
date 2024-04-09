//this file implements the robots behaviour during the running state

STATE running()
{
  static unsigned long previous_millis_battery_check;
  static unsigned long previous_millis_gyro_read;
  static unsigned long previous_millis_ir_read;
  static unsigned long previous_millis_sonar_read;

  //check battery health every 1s
  if (millis() - previous_millis_battery_check > 1000)
  {
    previous_millis_battery_check = millis(); //previous time the battery was checked
      //check battery is ok
    #ifndef NO_BATTERY_V_OK
      if (!is_battery_voltage_OK())
        return STOPPED;
    #endif
  }
  //read gyro every 10ms
  if (millis() - previous_millis_gyro_read > 10)
  { // Arduino style 500ms timed execution statement
    #ifndef NO_READ_GYRO
    //read gyro here
    //GYRO_reading();
    readGyro1(10);
    previous_millis_gyro_read = millis(); //previous time the gryo was read
    #endif
    // char message[8];
    // dtostrf(currentAngle,6,2,message);
    // BluetoothSerial.println(currentAngle);
  }


  //read IR every 100ms
  if (millis() - previous_millis_ir_read > 100)
  {
    previous_millis_ir_read = millis();
    //read the IR sensors in here
  }

  //read sonar every 110ms
  if (millis() - previous_millis_sonar_read > 110)
  {
    previous_millis_sonar_read = millis();
    #ifndef NO_HC - SR04
    HC_SR04_range(); //sonar read
    #endif
  }


  execute_movement_phase();

  return RUNNING;
}