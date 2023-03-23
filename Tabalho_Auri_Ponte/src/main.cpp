/*
    Project Name: Automatic bridge
    Creators: Gabriel Schuch and Érick Lindemann
    Objective: Using the stepper motors to control a bridge to get up and down, using the serial port of the Arduino Uno
*/
#include <Arduino.h>
#include <AccelStepper.h>
#include "defines.h"

unsigned long
    tempo;
String
    choice;

/*
   creation of the objetcs
*/
AccelStepper LeftMotor(AccelStepper::FULL4WIRE, IN1_MOTOR_ROLDANA, IN3_MOTOR_ROLDANA, IN2_MOTOR_ROLDANA, IN4_MOTOR_ROLDANA);
AccelStepper RightMotor(AccelStepper::FULL4WIRE, IN1_MOTOR_GARRA, IN3_MOTOR_GARRA, IN2_MOTOR_GARRA, IN4_MOTOR_GARRA);

void setup()
{
    LeftMotor.setMaxSpeed(1000);
    RightMotor.setMaxSpeed(1000);
    Serial.begin(9600);
    Serial.setTimeout(100);
}
void loop()
{
    /*
       while tha will hapens only if the varialble String choice isn't equal to 'get up' or 'get down'
       if the variable is equal to 'get up' or 'get down' the while won't work until the variable is reseted
       In this while loop it will chck if it has space in the serial port, if it has it'll wait until we inform a string to it
       then it'll print the value of the string in the serial port
       if you type oder word than 'get down' or 'get up' it'll ask you again until it gets right
    */
    while (choice != "get up" and choice != "get down")
    {
        Serial.println("What do you want to do? ");
        Serial.println("To get up");
        Serial.println("To get down");
        while (Serial.available() == 0)
        {
        };
        choice = Serial.readString();

        Serial.println(choice);

        if (choice != "get up" and choice != "get down")
        {
            Serial.println("I did not comprehend waht you wrote");
            Serial.println("Please write 'get up' or 'get down'");

            while (Serial.available() == 0)
            {
            };
            choice = Serial.readString();
            Serial.println(choice);
        }
    }
    /*
       This if will check that the value of the string is equal to 'get up', if it's it will move the stepper motors until they open completely
    */
    if (choice == "get up")
    {

        RightMotor.moveTo(4500);
        RightMotor.setSpeed(1000);
        RightMotor.runSpeedToPosition();

        LeftMotor.moveTo(-4500);
        LeftMotor.setSpeed(1000);
        LeftMotor.runSpeedToPosition();
    }
    /*
      This if will check that the value of the string is equal to 'get down', if it's it will move the stepper motors until they close completely(straight line)
    */
    if (choice == "get down")
    {
        RightMotor.moveTo(0);
        RightMotor.setSpeed(1000);
        RightMotor.runSpeedToPosition();

        LeftMotor.moveTo(0);
        LeftMotor.setSpeed(1000);
        LeftMotor.runSpeedToPosition();
    }
    /*
       This if will check that the current position of both stepper motors has matched if the position that they need to stop
       if it has the loop will stop and will reset the variable choice to wait new intruction
    */
    if ((LeftMotor.currentPosition() == -4500 and RightMotor.currentPosition() == 4500) or (LeftMotor.currentPosition() == 0 and RightMotor.currentPosition() == 0))
    {
        choice = "reset";
    }
    /*
       only for debugging
       to check the values and to know it is working
    */
    if (tempo + 10 < millis())
    {
        Serial.print("Current position of the Left motor ");
        Serial.println(LeftMotor.currentPosition());
        Serial.print("Current position of the Right motor ");
        Serial.println(RightMotor.currentPosition());
        tempo = millis();
    }
}