#include <AccelStepper.h>

#define IN1_MOTOR_ROLDANA 8
#define IN2_MOTOR_ROLDANA 9
#define IN3_MOTOR_ROLDANA 10
#define IN4_MOTOR_ROLDANA 11

#define IN1_MOTOR_GARRA 7
#define IN2_MOTOR_GARRA 6
#define IN3_MOTOR_GARRA 5
#define IN4_MOTOR_GARRA 4

#define IN1_MOTOR_BASE A2
#define IN2_MOTOR_BASE A3
#define IN3_MOTOR_BASE A4
#define IN4_MOTOR_BASE A5

#define MAX_DISTANCE
#define MIN_DISTANCE


unsigned long
tempo;

long
Posicao_Roldana ,
Posicao_Base ,
distance,
Posicao_Garra ;

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
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    distance = input.toInt();
    Serial.println(distance);
  }
  motorRoldana.moveTo(distance);
  motorRoldana.setSpeed(500);
  motorRoldana.runSpeedToPosition();

  motorGarra.moveTo(distance);
  motorGarra.setSpeed(500);
  motorGarra.runSpeedToPosition();

  motorBase.moveTo(distance);
  motorBase.setSpeed(500);
  motorBase.runSpeedToPosition();

  if (tempo + 400 < millis()) {
    Serial.print("Posiçao atual do motor roldana é ");
    Serial.println(motorRoldana.currentPosition());
    Serial.print("Posiçao atual do motor base é ");
    Serial.println(motorBase.currentPosition());
    Serial.print("Posiçao atual do motor garra é ");
    Serial.println(motorGarra.currentPosition());
    tempo = millis();
  }
}
