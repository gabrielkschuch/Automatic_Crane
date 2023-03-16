# include <AccelStepper.h>

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


int
escolha_Garra;
unsigned long
tempo;
long
distance_Base,
distance_Roldana;

AccelStepper motorRoldana(AccelStepper::FULL4WIRE, IN1_MOTOR_ROLDANA, IN3_MOTOR_ROLDANA, IN2_MOTOR_ROLDANA, IN4_MOTOR_ROLDANA);
AccelStepper motorGarra(AccelStepper::FULL4WIRE, IN1_MOTOR_GARRA, IN3_MOTOR_GARRA, IN2_MOTOR_GARRA, IN4_MOTOR_GARRA);
AccelStepper motorBase(AccelStepper::FULL4WIRE, IN1_MOTOR_BASE, IN3_MOTOR_BASE, IN2_MOTOR_BASE, IN4_MOTOR_BASE);

void setup()
{
  motorRoldana.setMaxSpeed(500);
  motorGarra.setMaxSpeed(500);
  motorBase.setMaxSpeed(500);
  Serial.begin(9600);
  Serial.setTimeout(100);
}
void loop()
{
  while (distance_Base == 0 && distance_Roldana == 0 && escolha_Garra == 0) {


    Serial.println("Qual a distancia que tu queres para que a garra chegue? ");
    while (Serial.available() == 0) {};
    distance_Roldana = Serial.parseInt();

    Serial.println("Quer descer ou subir a garra do guindaste? (1= descer/ 2= subir)");
    while (Serial.available() == 0) {};
    escolha_Garra = Serial.parseInt();

    Serial.println("Quanto que quer movimentar a base do guindaste? ");
    while (Serial.available() == 0) {};
    distance_Base = Serial.parseInt();

    Serial.println(distance_Roldana);
    Serial.println(escolha_Garra);
    Serial.println(distance_Base);
  }
  // ROLDANA

  motorBase.moveTo(distance_Base);
  motorBase.setSpeed(500);
  motorBase.runSpeedToPosition();



  motorRoldana.moveTo(distance_Roldana);
  motorRoldana.setSpeed(400);
  motorRoldana.runSpeedToPosition();

  motorGarra.moveTo(distance_Roldana);
  motorGarra.setSpeed(500);
  motorGarra.runSpeedToPosition();



  // GARRA

  switch (escolha_Garra)
  {
    case 1:                    // descer
      motorGarra.moveTo(10); // valor especifico d teste
      motorGarra.setSpeed(500);
      motorGarra.runSpeedToPosition();
      break;
    case 2:
      // subir
      motorGarra.moveTo(-10); // valor especifico d teste
      motorGarra.setSpeed(500);
      motorGarra.runSpeedToPosition();
      break;
  }

  if (motorRoldana.currentPosition() == distance_Roldana && motorBase.currentPosition() == distance_Base) {
    distance_Base = 0 ;
    distance_Roldana = 0 ;
    escolha_Garra = 0;
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
