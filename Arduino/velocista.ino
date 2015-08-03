#include "nucleo.h"
/* Sensores de Reflectancia */
#include <QTRSensors.h>

/* velociddes*/
#define vel_base 85
#define vel_min 0
#define vel_max 110
#define vel_fre 30
#define tim_fre 1

/* PID */
#define Kp 0.1
#define Ki 0
#define Kd 6
#define centro 1000

using namespace robot;
nucleo velocista(vel_base,vel_min,vel_max,vel_fre,tim_fre,Kp,Kd,Ki,centro);

void setup(){
  velocista.inicializar();
}
void loop(){
  velocista.run();
}
