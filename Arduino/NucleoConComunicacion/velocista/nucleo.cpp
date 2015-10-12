#include "nucleo.h"

robot::nucleo::nucleo(int v_base,int v_min,int v_max,int v_fre,int t_fre,float k_p,float k_d,float k_i,int cen){
  this->vel_base = v_base;
  this->vel_min  = v_min;
  this->vel_max  = v_max;
  this->vel_fre  = v_fre;
  this->tim_fre  = t_fre;
  this->k_pro    = k_p;
  this->k_der    = k_d;
  this->k_int    = k_i;
  this->centro   = cen;
  this->proportional = this->integral = this->derivative = this->sumaPID = this->v_angular1 = this->v_angular2 = this->a_angular1 = this->a_angular2 = 0;

}
void robot::nucleo::inicializar(){
  tiempo_encoders = tiempo_antes = tiempo_actual = millis();
  distancia_activo = infrarrojos_activo = true;
  pinMode(pin_dig_obs, INPUT);
  //-----------------------OUTPUT??? REALLY?
  pinMode(pin_in1,OUTPUT);
  pinMode(pin_in2,OUTPUT);
  pinMode(pin_in3,OUTPUT);
  pinMode(pin_in4,OUTPUT);
  //------------------------
  pinMode(pin_pwm_m1,OUTPUT);
  pinMode(pin_pwm_m2,OUTPUT);
  //------------------------
  this->error    = 0;
  this->err_ant  = 0;
  this->vel_mot1 = 0;
  this->vel_mot2 = 0;
  this->calibrar_sensores();
  Serial.begin(baudios);
  Serial1.begin(baudRate_const_bluetooth);

  this->setupCommunication();
}
void robot::nucleo::run(){
  comunicacion_principal();
  if(activo){
    digitalWrite(pin_led,HIGH);
    /*
    if (this->encontro_obstaculo()) {
      this->evadir_obstaculo();
    }else {
      this->obtener_posicion_linea();
      this->automatizar_velocidades();
      //this.corregir_velocidades(); /* encoders
      this->actualizar_velocidades();
      */

      if(distancia_activo){
        if(digitalRead(pinUltrasonido) == HIGH){
          sensor_distancia = 1;
          this->evadir_obstaculo();
        }else
          sensor_distancia = 0;
      }else
        sensor_distancia = 0;

      if(infrarrojos_activos){
        this->obtener_posicion_linea();
      }else{
        pos_linea = centro;
      }

      if(tiempo_actual - tiempo_encoders >= 100){
        this->calcular_v_angulares();
        tiempo_encoders = tiempo_actual;
      }

      this->automatizar_velocidades();
      //this.corregir_velocidades(); /* encoders
      this->actualizar_velocidades();
    }
  }else{
    digitalWrite(pin_led,LOW);
  }

  tiempo_actual = millis();
  tiempo_ciclo = tiempo_actual - tiempo_antes;
  tiempo_antes = tiempo_actual;
};
void robot::nucleo::calibrar_sensores(){
  qtra.calibrate();
}
void robot::nucleo::obtener_posicion_linea(){
  unsigned int position = qtra.readLine(valores_sensor);
  pos_linea = position;
}
void robot::nucleo::automatizar_velocidades(){
    error     = pos_linea - centro;

    /*Los separé para control*/
    proportional = k_pro * error;
    derivative = k_der * (error - err_ant);

    sumaPID = proportional + derivative;
    err_ant   = error;
    vel_mot2  = vel_base + sumaPID;
    vel_mot1  = vel_base - sumaPID;
}
void robot::nucleo::corregir_velocidades(){
  /* En este metodo se utilizara la informacion que dan los encoders
    y se corregira la velocidad real de los motores.
  */
}
void robot::nucleo::actualizar_velocidades(){
  /* Limite de velocidad maxima
      if (vel_mot1 > vel_max) {
        vel_mot1 = vel_max;
      }
      if (vel_mot2 > vel_max) {
        vel_mot2 = vel_max;
      }
      /* Limite de velocidad minima
      if (vel_mot1 < vel_min) {
        vel_mot1 = vel_min;
      }
      if (vel_mot2 < vel_min) {
        vel_mot2 = vel_min;
      }
  */
  constrain(vel_mot1,vel_min,vel_max);
  constrain(vel_mot2,vel_min,vel_max);//mas fácil con esta func()

  /* Velocidad actualizada en pwm */
  analogWrite(pin_pwm_m1,vel_mot1);
  analogWrite(pin_pwm_m2,vel_mot2);
}
int robot::nucleo::encontro_obstaculo(){
  int Obstaculo = 0;
  Obstaculo = digitalRead(pin_dig_obs);
  return Obstaculo;
}
void robot::nucleo::evadir_obstaculo(){


}

void robot::nucleo::calcular_v_angulares(){
  double revoluciones_M1 = (posicionM1 - posicionM1_antes)/120.0;
  double revoluciones_M2 = (posicionM2 - posicionM2_antes)/120.0;

  if(rev < 0)
    rev *=-1;

  frecuenciaM1 = revoluciones_M1/ double(tiempo_encoders/1000.0)
  errorFrecuenciaM1 = abs(PWM1*50/255.0 - frecuenciaM1);

  frecuenciaM2 = revoluciones_M2/ double(tiempo_encoders/1000.0)
  errorFrecuenciaM2 = abs(PWM2*50/255.0 - frecuenciaM2);

  v_angularM1 = 6.28*frecuenciaM1;
  a_angularM1 = v_angularM1 - v_angularM1_anterior;

  v_angularM2 = 6.28*frecuenciaM2;
  a_angularM2 = v_angularM2 - v_angularM2_anterior;

}

void robot::nucleo::cambiar_sentido_motores(int M1,int M2){
  switch (M1) {
    case 1:
      digitalWrite(direccion_forward_M1,HIGH);
      digitalWrite(direccion_backward_M1,LOW);
      break;
    case 0:
      digitalWrite(direccion_forward_M1,LOW);
      digitalWrite(direccion_backward_M1,LOW);
      break;
    case -1:
      digitalWrite(direccion_forward_M1,LOW);
      digitalWrite(direccion_backward_M1,HIGH);
      break;
  }

  switch (M2) {
    case 1:
      digitalWrite(direccion_forward_M2,HIGH);
      digitalWrite(direccion_backward_M2,LOW);
      break;
    case 0:
      digitalWrite(direccion_forward_M2,LOW);
      digitalWrite(direccion_backward_M2,LOW);
      break;
    case -1:
      digitalWrite(direccion_forward_M2,LOW);
      digitalWrite(direccion_backward_M2,HIGH);
      break;
  }
}

//------------------------------------------------------------------------------------------------//
/*METODOS PARA LA COMUNICACION*/

void robot::nucleo::setupCommunication(){
  Serial1.begin(this->baudRate);
}

void robot::nucleo::comunicacion_principal(){
  communication_read();
  if(activo)
    writeComunicacion();
}

void robot::nucleo::readComunicacion(){
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
        k_pro = Serial1.parseFloat();
        k_int = Serial1.parseFloat();
        k_der = Serial1.parseFloat();

        Serial1.print("message/Constantes cambiadas -> P=");Serial1.print(k_pro);Serial1.print("/I=");Serial1.print(k_int);Serial1.print("/D=");Serial1.println(k_der);
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
    //Serial1.flush();OJO PROBAR FUNCIONALIDAD
  }
}

void robot::nucleo::writeComunicacion(){
      Serial1.print("data/");
      Serial1.print(proportional);
      Serial1.print("/");
      Serial1.print(integral);
      Serial1.print("/");
      Serial1.print(derivative);
      Serial1.print("/");
      Serial1.print(sumaPID);
      Serial1.print("/");
      Serial1.print(vel_mot1);//Serial1.print(PWMI);
      Serial1.print("/");
      Serial1.print(vel_mot2);//Serial1.print(PWMD);
      Serial1.print("/");
      Serial1.print(tiempo_ciclo;
      Serial1.print("/");
      Serial1.print(pos_linea);//posicion de la linea
      Serial1.print("/");
      Serial1.print(sensor_distancia);//(1) si obstaculo, (0) si no
      Serial1.print("/");
      Serial1.print(v_angularM1);
      Serial1.print("/");
      Serial1.print(v_angularM2);
      Serial1.print("/");
      Serial1.print(a_angularM1);
      Serial1.print("/");
      Serial1.println(a_angularM2);
}

void robot::nucleo::onOffSensors(bool estado){
  int n_sensores = Serial1.parseInt(), i = 0, temp = 0;

  for(i = 0; i < n_sensores; i++){
    temp = Serial1.parseInt();

    if(temp == 1){
      infrarrojos_activos = estado;
      Serial1.print("message/Sensores infrarrojos ");
      Serial1.println((estado)?"activados":"desactivados");

      /*Serial.print("message/Sensores infrarrojos ");
      Serial.println((estado)?"activados":"desactivados");*/
    }

    if(temp == 2){
      distancia_activo = estado;
      Serial1.print("message/Sensor de distancia ");
      Serial1.println((estado)?"activado":"desactivado");

      /*Serial.print("message/Sensor de distancia ");
      Serial.println((estado)?"activado":"desactivado");*/
    }
  }
}

void robot::nucleo::status(){
  Serial1.print("status/")

  if(infrarrojos_activos)
    Serial1.print(1);
  else
    Serial1.print(0);

    Serial1.print("/");

  if(distancia_activo)
    Serial1.print(1);
  else
    Serial1.print(0;

  Serial1.println();
}
