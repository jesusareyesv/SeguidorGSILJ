#include <Arduino.h>

#define baudRate_const 9600
#define t_key 4
#define LED_P

namespace robot{
  class RobotCommunicator{
    int baudRate;
    char key[t_key];
    int pinLed;
    Robot * robot;

    RobotCommunicator(Robot* robotI, ){
      this->robot = robotI;
      baudRate = baudRate_const;
      strcpy(key,"1234");
      this->pinLed = LED_P;

      this->setupCommunication();
    }

    void setupCommunication();
    void readAlways();
    void writeData_whileRun();
    void onOffSensors(bool estado);
    void status();

    void communication_principal(bool activo);
  };
}

using namespace robot;

void RobotCommunicator::setupCommunication(){
  Serial1.begin(this->baudRate);

}

void communication_principal(void) {
  this->readAlways();

}

void RobotCommunicator::readAlways(){
  if(Serial1.available()){
    char ordenActual = Serial1.read();

    /*if(ordenActual != )
      Serial.read();
      */

    switch(ordenActual){
      case 'p':activo = false; Serial1.println("message/Detenido");break;//correr

      case 'r':activo = true ; Serial1.println("message/Activo");break;//parar

      case 's': status(); break;//comprobar estado

      case 'v'://cambia los valores de las constantes PID
        P_const = Serial1.parseFloat();
        I_const = Serial1.parseFloat();
        D_const = Serial1.parseFloat();

        Serial1.print("message/Constantes cambiadas -> P=");Serial1.print(P_const);Serial1.print("/I=");Serial1.print(I_const);Serial1.print("/D=");Serial1.println(D_const);
        //Serial.print("message/Constantes cambiadas -> P=");Serial.print(P_const);Serial.print("/I=");Serial.print(I_const);Serial.print("/D=");Serial.println(D_const);
        break;

      case 'a'://activa sensores
        onOffSensors(true);
        break;

      case 'd': //desactiva sensores
          onOffSensors(false);
        break;

        case 'k':
            clave = Serial1.parseInt();
            Serial1.print("message/Clave cambiada a:");Serial1.println(clave);
            //Serial.print("message/Clave cambiada a:");Serial.println(clave);
          break;
        case 'e':
          String s = Serial1.readString();
          Serial1.print("message/ECHO=");Serial1.println(s);
          //Serial.print("message/ECHO=");Serial.println(s);
          break;

    }
    Serial1.flush();
  }
}
