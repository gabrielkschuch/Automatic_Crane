#include <AccelStepper.h>

/*  Project Name: Automatic bridge
    Creators: Gabriel Schuch and Érick Lindemann
    Objective: Using the stepper motors to control a bridge to get up and down, using the serial port of the Arduino Uno
*/

#define IN1_MOTOR_ROLDANA 8
#define IN2_MOTOR_ROLDANA 9
#define IN3_MOTOR_ROLDANA 10
#define IN4_MOTOR_ROLDANA 11

#define IN1_MOTOR_GARRA 7
#define IN2_MOTOR_GARRA 6
#define IN3_MOTOR_GARRA 5
#define IN4_MOTOR_GARRA 4

unsigned long
  tempo;
String
  choice;

/*
   creation of the objetcs
*/
AccelStepper motorRoldana(AccelStepper::FULL4WIRE, IN1_MOTOR_ROLDANA, IN3_MOTOR_ROLDANA, IN2_MOTOR_ROLDANA, IN4_MOTOR_ROLDANA);
AccelStepper motorGarra(AccelStepper::FULL4WIRE, IN1_MOTOR_GARRA, IN3_MOTOR_GARRA, IN2_MOTOR_GARRA, IN4_MOTOR_GARRA);

void setup() {
  motorRoldana.setMaxSpeed(1000);
  motorGarra.setMaxSpeed(1000);
  Serial.begin(9600);
  Serial.setTimeout(100);
}
void loop() {
  /*
     while tha will hapens only if the varialble String choice isn't equal to 'get up' or 'get down'
     if the variable is equal to 'get up' or 'get down' the while won't work until the variable is reseted
     In this while loop it will chck if it has space in the serial port, if it has it'll wait until we inform a string to it
     then it'll print the value of the string in the serial port
     if you type oder word than 'get down' or 'get up' it'll ask you again until it gets right
  */
  while (choice != "get up" && choice != "get down") {
    Serial.println("What do you want to do? ");
    Serial.println("To get up");
    Serial.println("To get down");
    while (Serial.available() == 0) {};
    choice = Serial.readString();

    Serial.println(choice);
    
    if (choice != "get up" && choice != "get down") {
      Serial.println("I did not comprehend waht you wrote");
      Serial.println("Please write 'get up' or 'get down'");

      while (Serial.available() == 0) {};
      choice = Serial.readString();
      Serial.println(choice);      
    }
  }
  /*
     This if will check that the value of the string is equal to 'get up', if it's it will move the stepper motors until they open completely
  */
  if (choice == "get up") {

    motorGarra.moveTo(4500);
    motorGarra.setSpeed(1000);
    motorGarra.runSpeedToPosition();

    motorRoldana.moveTo(-4500);
    motorRoldana.setSpeed(1000);
    motorRoldana.runSpeedToPosition();
  }
  /*
    This if will check that the value of the string is equal to 'get down', if it's it will move the stepper motors until they close completely(straight line)
  */
  if (choice == "get down") {
    motorGarra.moveTo(0);
    motorGarra.setSpeed(1000);
    motorGarra.runSpeedToPosition();

    motorRoldana.moveTo(0);
    motorRoldana.setSpeed(1000);
    motorRoldana.runSpeedToPosition();
  }
  /*
     This if will check that the current position of both stepper motors has matched if the position that they need to stop
     if it has the loop will stop and will reset the variable choice to wait new intruction
  */
  if ((motorRoldana.currentPosition() == -4500 and motorGarra.currentPosition() == 4500) or (motorRoldana.currentPosition() == 0 and motorGarra.currentPosition() == 0)) {
    choice = "reset";
  }
  /*
     only for debugging
     to check the values and to know it is working
  */
  if (tempo + 10 < millis()) {
    Serial.print("Posiçao atual do motor roldana é ");
    Serial.println(motorRoldana.currentPosition());
    Serial.print("Posiçao atual do motor garra é ");
    Serial.println(motorGarra.currentPosition());
    tempo = millis();
  }
}