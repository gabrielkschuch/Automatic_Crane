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
escolha_Garra,
distance_garra;
unsigned long
tempo;
long
distance_Base,
distance_Roldana;
bool
flag_descida,
flag_subida;

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
  while (distance_Base == 0 && distance_Roldana == 0) { // while para informar os valores por meio da porta serial

    Serial.println("Qual a distancia que tu queres para que a garra chegue? ");
    while (Serial.available() == 0) {};
    distance_Roldana = Serial.parseInt();

    Serial.println("Quanto que quer movimentar a base do guindaste? ");
    while (Serial.available() == 0) {};
    distance_Base = Serial.parseInt();

    Serial.println(distance_Roldana);
    Serial.println(distance_Base);
  }
  // ROLDANA

  motorBase.moveTo(distance_Base);
  motorBase.setSpeed(500);
  motorBase.runSpeedToPosition();



  motorRoldana.moveTo(distance_Roldana);
  motorRoldana.setSpeed(400);
  motorRoldana.runSpeedToPosition();
  
if (motorGarra.currentPosition() < distance_Roldana){
  motorGarra.moveTo(distance_Roldana);
    motorGarra.setSpeed(500);
    motorGarra.runSpeedToPosition();
}
    
  


  distance_garra = distance_Roldana + 3000;

  // GARRA

  if (motorGarra.currentPosition() == distance_Roldana) {
    flag_descida = 1;
  }
  if (motorGarra.currentPosition() == (distance_garra) && flag_descida == 1) {
    flag_subida = 1;
    flag_descida = 0;
  }


  if (flag_descida == 1) {
    motorGarra.moveTo(distance_garra);
    motorGarra.setSpeed(500);
    motorGarra.runSpeedToPosition();
  }

  if (flag_subida == 1) {
    motorGarra.moveTo(distance_Roldana);
    motorGarra.setSpeed(500);
    motorGarra.runSpeedToPosition();
  }

  if (motorRoldana.currentPosition() == distance_Roldana && motorBase.currentPosition() == distance_Base && flag_subida == 1 && flag_descida == 0 && motorGarra.currentPosition() == distance_Roldana) { // reseta os valores para que podemos informar os novos valores
    distance_Base = 0 ;
    distance_Roldana = 0 ;
    escolha_Garra = 0;
  }


  if (tempo + 10 < millis())
  {
    //Serial.print("Posiçao atual do motor roldana é ");
    //Serial.println(motorRoldana.currentPosition());
    //Serial.print("Posiçao atual do motor base é ");
    //Serial.println(motorBase.currentPosition());
    Serial.print("Posiçao atual do motor garra é ");
    Serial.println(motorGarra.currentPosition());
    tempo = millis();
  }



}
