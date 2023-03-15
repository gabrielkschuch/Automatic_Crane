#include <Arduino.h>
#include <AccelStepper.h>
#include "defines.h"

int
    escolha_Garra;
unsigned long
    tempo;
long
    distance_Base,
    distance_Roldana;
bool
    controle_garra = 0;

AccelStepper motorRoldana(AccelStepper::FULL4WIRE, IN1_MOTOR_ROLDANA, IN3_MOTOR_ROLDANA, IN2_MOTOR_ROLDANA, IN4_MOTOR_ROLDANA);
AccelStepper motorGarra(AccelStepper::FULL4WIRE, IN1_MOTOR_GARRA, IN3_MOTOR_GARRA, IN2_MOTOR_GARRA, IN4_MOTOR_GARRA);
AccelStepper motorBase(AccelStepper::FULL4WIRE, IN1_MOTOR_BASE, IN3_MOTOR_BASE, IN2_MOTOR_BASE, IN4_MOTOR_BASE);

void setup()
{
    motorRoldana.setMaxSpeed(500);
    motorGarra.setMaxSpeed(500);
    motorBase.setMaxSpeed(500);
    Serial.begin(9600);
}
void loop()
{
    if (Serial.available() >= 3)
    {
        Serial.println("Qual a distancia que tu queres para que a garra chegue? ");
        String input = Serial.readStringUntil('\n');
        distance_Roldana = input.toInt();

        Serial.println('Quer descer ou subir a garra do guindaste? (1= descer/ 2= subir)');
        String input_Garra = Serial.readStringUntil('\n');
        escolha_Garra = input_Garra.toInt();

        Serial.println("Quanto que quer movimentar a base do guindaste? ");
        String input_Base = Serial.readStringUntil('\n');
        distance_Base = input_Base.toInt();

        Serial.println(distance_Roldana);
        Serial.println(escolha_Garra);
        Serial.println(distance_Base);
    }

    // ROLDANA

    motorRoldana.moveTo(distance_Roldana);
    motorRoldana.setSpeed(400);
    motorRoldana.runSpeedToPosition();

    // GARRA

    switch (controle_garra)
    {
    case 1:
        switch (escolha_Garra)
        {
        case 1:                    // descer
            motorGarra.moveTo(10); // valor especifico d teste
            motorGarra.setSpeed(500);
            motorGarra.runSpeedToPosition();
            break;
        case 2:
            break;                 // subir
            motorGarra.moveTo(-10); // valor especifico d teste
            motorGarra.setSpeed(500);
            motorGarra.runSpeedToPosition();
        }
        break;
    case 0:
        motorGarra.moveTo(distance_Roldana);
        motorGarra.setSpeed(500);
        motorGarra.runSpeedToPosition();
        break;
    }

    // BASE

    motorBase.moveTo(distance_Base);
    motorBase.setSpeed(500);
    motorBase.runSpeedToPosition();

    if (motorGarra.currentPosition() == distance_Roldana)
    {
        controle_garra = 1;
    }
    if (motorGarra.currentPosition() == distance_Roldana && controle_garra == 1)
    {
        controle_garra = 0;
    }

    /*
    if (tempo + 700 < millis())
        {
            Serial.print("Posiçao atual do motor roldana é ");
            Serial.println(motorRoldana.currentPosition());
            Serial.print("Posiçao atual do motor base é ");
            Serial.println(motorBase.currentPosition());
            Serial.print("Posiçao atual do motor garra é ");
            Serial.println(motorGarra.currentPosition());
            tempo = millis();
        }
    */
}