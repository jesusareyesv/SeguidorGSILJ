#include <Arduino.h>
#define proportional_c 0.2
#define integral_c 0.2
#define derivative_c 0.2

bool activo = false;
int led = 13;
float P_constant = proportional_c;
float I_constant = integral_c;
float D_constant = derivative_c;
int clave = 1234;

void setup(){
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}

void loop(){
  comunicacion();

  if(activo){
    digitalWrite(led,HIGH);
    //poner las interrupciones
  }else{
    //desactivar las interrupciones
    digitalWrite(led,LOW);
  }
}

void comunicacion(){
  //desactivar interrupciones
  communication_read();
  if(activo)
    communication_write();
  //activar interrupciones
}

void communication_read(){
  if(Serial.available()){
    char ordenActual = Serial.read();

    /*if(ordenActual != )
      Serial.read();
      */

    switch(ordenActual){
      case 'p':activo = false; break;//correr

      case 'r':activo = true ; break;//parar

      case 's': status(); break;//comprobar estado

      case 'v'://cambia los valores de las constantes PID
        P_constant = Serial.parseFloat();
        I_constant = Serial.parseFloat();
        D_constant = Serial.parseFloat();
        break;

      case 'a'://activa sensores
          int n_sensores = Serial.parseInt(),count = 0;
          char sensor = '\0';
          while(count < n_sensores && Serial.available()){
            Serial.read();
            sensor = Serial.read();
            if(sensor == 'i')
              infrarrojos_activos = true;
            else
              if(sensor == 'u')
                ultrasonido_activo = true;

            count++;
          }
        break;
      case 'd': //desactiva sensores
          int n_sensores = Serial.parseInt(),count = 0;
          char sensor = '\0';
          while(count < n_sensores && Serial.available()){
            Serial.read();
            sensor = Serial.read();
            if(sensor == 'i')
              infrarrojos_activos = false;
            else
              if(sensor == 'u')
                ultrasonido_activo = false;

            count++;
          }
        break;

        case 'k':
            clave = Serial.readInt();
          break;

    }
  }
}

void communication_write(){
  Serial.print(clave);
  Serial.print("/");
  Serial.print(proportional);
  Serial.print("/");
  Serial.print(integral);
  Serial.print("/");
  Serial.print(derivative);
  Serial.print("/");
  Serial.print(suma);
  Serial.print("/");
  Serial.print(PWMI);
  Serial.print("/");
  Serial.print(PWMR);
  Serial.print("/");
  Serial.print(DUTY_CYCLE);
  Serial.print("/");
  Serial.print(line_position);
  Serial.print("/");
  Serial.print(sensor_distancia);
  Serial.print("/");
}

void status(){//funcion para comprobar el robot| Se llama desde la consola de la telemetría

}
