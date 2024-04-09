//this file implements the robots behaviour during the running state

STATE running()
{
  static unsigned long previous_millis_battery_check;

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
  

  execute_movement_phase();

  // Serial.println(movement_phase);
  // // char message[4];
  // // dtostrf(movement_phase,6,0,message);
  // // Serial1.println(message);
  //   char message[10] = "Hello";
  //   dtostrf(sonar_average,6,2,message);
  //   Serial.print(message);
  //   Serial.print(":");
  //   dtostrf(sonar_average_prev1,6,2,message);
  //   Serial.println(message);



  return RUNNING;
}