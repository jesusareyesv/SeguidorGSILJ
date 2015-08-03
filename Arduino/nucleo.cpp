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


}
void robot::nucleo::inicializar(){
  pinMode(pin_dig_obs, INPUT);
  //-----------------------
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
}
void robot::nucleo::run(){
  if (this->encontro_obstaculo()) {
    this->evadir_obstaculo();
  }else {
    this->obtener_posicion_linea();
    this->automatizar_velocidades();
    //this.corregir_velocidades(); /* encoders */
    this->actualizar_velocidades();
  }

};
void robot::nucleo::calibrar_sensores(){
  qtra.calibrate();
}
void robot::nucleo::obtener_posicion_linea(){
  unsigned int position = qtra.readLine(valores_sensor);
  pos_linea = position;
}
void robot::nucleo::automatizar_velocidades(){
    int vel_motor = 0;
    error     = pos_linea - centro;
    vel_motor = k_pro * error + k_der * (error - err_ant);
    err_ant   = error;
    vel_mot2  = vel_base + vel_motor;
    vel_mot1  = vel_base - vel_motor;
}
void robot::nucleo::corregir_velocidades(){
  /* En este metodo se utilizara la informacion que dan los encoders
    y se corregira la velocidad real de los motores.
  */
}
void robot::nucleo::actualizar_velocidades(){
  /* Limite de velocidad maxima */
  if (vel_mot1 > vel_max) {
    vel_mot1 = vel_max;
  }
  if (vel_mot2 > vel_max) {
    vel_mot2 = vel_max;
  }
  /* Limite de velocidad minima */
  if (vel_mot1 < vel_min) {
    vel_mot1 = vel_min;
  }
  if (vel_mot2 < vel_min) {
    vel_mot2 = vel_min;
  }
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
