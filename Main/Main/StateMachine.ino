//This file implements the state machines used for control flow of the robot when it's executing it's task

void homeStateMachine(int adress){
  switch (adress)
  {
    case 0:
    findCorner();
    SerialCom->println("0");
    break;

  case 1:
    driveStrightUntilDistance(20);
    SerialCom->println("1");
    break;
  case 2:
     //trunDegree(90);
    currentState++;
    SerialCom->println(currentState);
    break;

  //need funtion
  case 3:
    homing_normal_system(0,0,0,1,10);
    SerialCom->println("2");
    break;
  case 4:
    driveStrightUntilDistance(35);
    SerialCom->println("3");
    break;
  case 5:
    trunDegree(90);
    SerialCom->println(currentState);
    break;
  case 6:
    checkForLongSide();
    //goto case 6 if shortside
    SerialCom->println(currentState);
    break;
  case 7:
    //if short side
    driveStrightUntilDistance(35);
    SerialCom->println(currentState);
    break;
  // case 8:
  //   //=======================================================main start=============================
  //   driveStringhtForDistance(35);
  //   SerialCom->println("3");
  //   break;
  // case 8:
  //   trunDegree(-90);
  //   SerialCom->println(currentState);
  //   break;
  // case 9:
  //   currentState = 1;
  //   break;
  }

}



void stateMachine(int adress)
{

  switch (adress)
  {
  case 8:
    driveStrightUntilDistance(35);
    SerialCom->println("1");
    break;
  case 9:
    trunDegree(90);
    SerialCom->println("2");
    break;
  case 10:
    driveStringhtForDistance(35);
    SerialCom->println("3");
    break;
  case 11:
    trunDegree(90);
    SerialCom->println(currentState);
    break;
  case 12:
    driveStrightUntilDistance(35);
    SerialCom->println(currentState);
    break;
  case 13:
    trunDegree(-90);
    SerialCom->println(currentState);
    break;
    case 14:
    driveStringhtForDistance(35);
    SerialCom->println("3");
    break;
  case 15:
    trunDegree(-90);
    SerialCom->println(currentState);
    break;
  case 16:
    currentState = 8;
    break;
  }
}

