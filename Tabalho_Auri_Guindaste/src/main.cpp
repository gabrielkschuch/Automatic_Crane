#include <Arduino.h>
#include <AccelStepper.h>
#include "defines.h"

AccelStepper motorRoldana(AccelStepper::FULL4WIRE, IN1_MOTOR_ROLDANA, IN3_MOTOR_ROLDANA, IN2_MOTOR_ROLDANA, IN4_MOTOR_ROLDANA);
AccelStepper motorGarra(AccelStepper::FULL4WIRE, IN1_MOTOR_GARRA, IN3_MOTOR_GARRA, IN2_MOTOR_GARRA, IN4_MOTOR_GARRA);
AccelStepper motorBase(AccelStepper::FULL4WIRE, IN1_MOTOR_BASE, IN3_MOTOR_BASE, IN2_MOTOR_BASE, IN4_MOTOR_BASE);

void setup()
{
    motorRoldana.setMaxSpeed(500);
    motorGarra.setMaxSpeed(500);
    motorBase.setMaxSpeed(500);
}

void loop()
{
    motorRoldana.moveTo(100);
    motorRoldana.setSpeed(300);
    motorRoldana.runSpeedToPosition();

    motorGarra.moveTo(150);
    motorGarra.setSpeed(300);
    motorGarra.runSpeedToPosition();

    motorBase.moveTo(100);
    motorBase.setSpeed(300);
    motorBase.runSpeedToPosition();

    delay(1000);

    motorRoldana.moveTo(-100);
    motorRoldana.setSpeed(300);
    motorRoldana.runSpeedToPosition();

    motorGarra.moveTo(-150);
    motorGarra.setSpeed(300);
    motorGarra.runSpeedToPosition();

    motorBase.moveTo(-100);
    motorBase.setSpeed(300);
    motorBase.runSpeedToPosition();
}