#include <QTRSensors.h>
#include <Encoder.h>
#include "Seguidor.h"

#define Kp 0.02
#define Ki 1.2903
#define Kd 0.19

#define muestras_sensor 4

#define TELEMETRIA_ON

#ifndef TELEMETRIA_ON
  #define encoderA1_pin 3
  #define encoderB1_pin 0
  #define encoderA2_pin 2
  #define encoderB2_pin 1 //CAMBIE LOS PINES

  #define nSensors 8
  QTRSensorsAnalog qtra((unsigned char[]){0,2,1,3,11,4,5,9},nSensors,muestras_sensor, QTR_NO_EMITTER_PIN);
#else
  #define encoderA1_pin 3
  #define encoderB1_pin 14
  #define encoderA2_pin 2
  #define encoderB2_pin 9  //tambien lo cambie

  #define nSensors 6
  QTRSensorsAnalog qtra((unsigned char[]){2,1,3,11,4,5},nSensors,muestras_sensor, QTR_NO_EMITTER_PIN);
#endif

unsigned int valuesS[nSensors], line_pos;

long pE1, pE2;
Encoder encoder_M1(encoderA1_pin, encoderB1_pin), encoder_M2(encoderA2_pin,encoderB2_pin);

Seguidor seguidor(Kp,Ki,Kd);//cambiar 0's por las constantes
void setup(){
  pinMode(encoderA1_pin,INPUT);
  pinMode(encoderA2_pin,INPUT);
  pinMode(encoderB1_pin,INPUT);
  pinMode(encoderB2_pin,INPUT);
  Serial.begin(9600);
  Serial.println("Inicio C");
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  Serial.println("Fin C");
}

void loop(){
  if(seguidor.isRobot_active()){
    line_pos = qtra.readLine(valuesS);
    seguidor.set_SensorsValues_LinePosition(valuesS,line_pos);

    /*lee encoders y pone sus valores*/
    pE1 = encoder_M1.read();
    pE2 = encoder_M2.read();

    seguidor.set_Positions_Encoders(pE1,pE2);

  }

  seguidor.runing_Seguidor();
}


