#include "Seguidor.h"

Seguidor::Seguidor(double kp,double ki,double kd, Encoder *e1, Encoder *e2){
  this->k_P = kp;
  this->k_I = ki;
  this->k_D = kd;

  this->encoder_M1 = e1;
  this->encoder_M2 = e2;

  this->proportional = this->derivative = this->integral = 0;
  this->init();
}

void Seguidor::init(){
  //Serial.begin(baud_rate_Serial);
  //Serial1.begin(baud_rate_Bluetooth);//----------------------------------------------------------------OJO
  pinMode(direction_forward_M1_pin,OUTPUT);
  pinMode(direction_forward_M2_pin,OUTPUT);
  pinMode(direction_backward_M1_pin,OUTPUT);
  pinMode(direction_backward_M2_pin,OUTPUT);

  pinMode(stby_pin,OUTPUT);
  pinMode(distance_sensor_pin,INPUT);

  PWM_MIN = pwm_min;
  PWM_MAX = pwm_max;
  PWM_ABS = pwm_ABS;
  PWM_BASE = pwm_base;
  PWM_ANY_CURVA = PWM_MAX*0.5;
  FRENO_CURVA = freno_Curva;
  in_obstaculo = false;
  infrarred_active = distance_active = true;
  robot_active = true;//----------------------------------------------------------------OJO
  //robot_active = true;
  digitalWrite(stby_pin,HIGH);
  tolerancia_dinamica = 0.9;
  delay1 = 20;
  delay2 = 30;
  delay_o1 = delay_o4 = 230;//100;
  delay_o2 = 100;
  delay_o3 = 950;
  giro_loco_porc = giro_loco_porc2 = giro_loco;
//  t_inicio = millis();
//  t_anterior = t_actual = millis();
}//like python

void Seguidor::runing_Seguidor(){
  //avoid();
  //communication_principal();//----------------------------------------------------------------OJO
  //this->leerEncoders();
  //this->calcularDiferenciaAngulo(0,0);
  /*if(comprobar_Sensores_obstaculo())
    Serial.println("Linea encontrada!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  else
    Serial.println("NADAAAAAAAAAAAAAAAAAAAAAAAAA!");

  delay(200);*/
  if(robot_active){
    //Serial.println("Activo");
    if(!infrarred_active)
      line_position = desired_position;

    if(!in_obstaculo){
      
      distance_sensor = 0;
      if(distance_active)
        if(digitalRead(distance_sensor_pin) == HIGH){
          distance_sensor = 1;
        }else{
          avoid();
        }

      PID_processing();
      adjust_velocities();

      if(actual_time - summatory_time >= 500){
        if(summatory_PWMM1 > summatory_PWMM2)
          ultima_curva = 0;//Serial1.println("message/--------------------------------------------------Curva derecha");
        else
          if(summatory_PWMM1 < summatory_PWMM2)
            ultima_curva = 1;

        summatory_PWMM1 = summatory_PWMM2 = 0;
        summatory_time = actual_time;
      }else{
        summatory_PWMM1 += pwmM1;
        summatory_PWMM2 += pwmM2;
      }

    }else{
      if(comprobar_Sensores_obstaculo()){
        in_obstaculo = false;
        summatory_time = millis();
        Serial.println("Linea");
      }else{
        change_Direction(1,1);
        Serial.println("NADA");
      }
    }
  }else{
    change_Velocity(0,0);
    change_Direction(0,0);
  }

  actual_time = millis();

  loop_time = actual_time - before_time;
  before_time = actual_time;
}

void Seguidor::change_Direction(int M1,int M2){
  switch(M1){
    case 1:
      digitalWrite(direction_forward_M1_pin,HIGH);
      digitalWrite(direction_backward_M1_pin,LOW);
      break;
    case 0:
      digitalWrite(direction_forward_M1_pin,LOW);
      digitalWrite(direction_backward_M1_pin,LOW);
      break;
    case -1:
      digitalWrite(direction_forward_M1_pin,LOW);
      digitalWrite(direction_backward_M1_pin,HIGH);
      break;
  }

  switch(M2){
    case 1:
      digitalWrite(direction_forward_M2_pin,HIGH);
      digitalWrite(direction_backward_M2_pin,LOW);
      break;
    case 0:
      digitalWrite(direction_forward_M2_pin,LOW);
      digitalWrite(direction_backward_M2_pin,LOW);
      break;
    case -1:
      digitalWrite(direction_forward_M2_pin,LOW);
      digitalWrite(direction_backward_M2_pin,HIGH);
      break;
  }

  direccion_M1 = M1;
  direccion_M2 = M2;
}

void Seguidor::PID_processing(){
  error = double(line_position) - double(desired_position);
  proportional = k_P * error;
  derivative = k_D * (error - error_antes);
  suma_integral += error;

  suma_integral = constrain(suma_integral,-255,255);

  integral = k_I * suma_integral;

  sumaPID = proportional + derivative + integral;

  error_antes   = error;
  pwmM1  = PWM_BASE + sumaPID;
  pwmM2  = PWM_BASE - sumaPID;

}

void Seguidor::adjust_velocities(){

  float porc_error = (float)(error)/(float)(desired_position);

    int dM1, dM2;

    if(pwmM1 < 0){
      dM1 = -1;
      pwmM1 *= -1;

    }else{
      dM1 = 1;
    }


    if(pwmM2 < 0){
      dM2 = -1;
      pwmM2 *= -1;

    }else{
      dM2 = 1;
    }



  if(porc_error > tolerancia_dinamica || porc_error < -tolerancia_dinamica){

    frenoABS(FRENO_CURVA);
    change_Velocity(pwmM1,pwmM2);
    change_Direction(dM1,dM2);

    }else{
      change_Velocity(pwmM1,pwmM2);
      change_Direction(1,1);
    }

}

void Seguidor::set_SensorsValues_LinePosition(unsigned int* values, unsigned int lineP){
  this->sensors_values = values;
  line_position = lineP;
  Serial.println(lineP);
}

void Seguidor::emergency_stop(){
  digitalWrite(stby_pin,LOW);
}

void Seguidor::frenoABS(int times){
  for(int i = 0; i < times; i++){
    change_Velocity(pwm_ABS,PWM_ABS);
    delay(delay1);
    change_Direction(-1,-1);
		delay(delay2);
	}
  change_Direction(0,0);
  //activo = false;
}

void Seguidor::change_Velocity(int vm1, int vm2){
  change_Direction(0,0);

  pwmM1 = constrain(vm1,PWM_MIN,PWM_MAX);
  pwmM2 = constrain(vm2,PWM_MIN,PWM_MAX);

  analogWrite(pwmM1_pin,pwmM1);
  analogWrite(pwmM2_pin,pwmM2);
}

bool Seguidor::isRobot_active(){
  return this->robot_active;
}

void Seguidor::avoid(){
  frenoABS(1);

  delay(1000);
  if(ultima_curva == 1){
    rotarAngulo(-45);
    delay(50);
    rotarAngulo(-45);
    delay(50);
    avanzar_Encoders(35);
    delay(50);
    rotarAngulo(95);
    delay(50);
    //avanzar_Encoders(35);
    change_Velocity(70,70);
  }else{
    rotarAngulo(45);
    delay(50);
    rotarAngulo(45);
    delay(50);
    avanzar_Encoders(35);
    delay(50);
    rotarAngulo(-95);
    delay(50);
    //avanzar_Encoders(35);
    change_Velocity(70,70);
  }

  in_obstaculo = true;
  //robot_active = false;
  change_Direction(1,1);
}

bool Seguidor::comprobar_Sensores_obstaculo(){
  for(int i = 0; i < nSensors; i++){
    if(sensors_values[i] > 600)
      return true;
  }
  return false;
}

void Seguidor::leerEncoders(){
  this->position_encoder_M1 = encoder_M1->read();
  this->position_encoder_M2 = encoder_M2->read();

  Serial.print("Encoder1: "); Serial.print(position_encoder_M1);Serial.print("     Encoder2: ");Serial.println(position_encoder_M2);
}

float Seguidor::calcularDiferenciaAngulo(long posicion_original_M1, long posicion_original_M2){
  leerEncoders();
  long dif_p_e1 = abs(position_encoder_M1 - posicion_original_M1), dif_p_e2 = abs(position_encoder_M2 - posicion_original_M2);

  long dif_position_ambos_encoders = dif_p_e1 + dif_p_e2;

  float angulo = dif_position_ambos_encoders * 0.375;

  Serial.print("Angulo: ");Serial.println(angulo);

  return angulo;
}

void Seguidor::rotarAngulo(float angulo){
  long base_m1 = position_encoder_M1, base_m2 = position_encoder_M2;

  change_Velocity(pwm_giro_recta,pwm_giro_recta);
  if(angulo < 0)
    change_Direction(1,-1);
  else
    if(angulo > 0)
      change_Direction(-1,1);
    else
      change_Direction(0,0);

  while(calcularDiferenciaAngulo(base_m1,base_m2) < abs(angulo));

  change_Direction(0,0);
}

void Seguidor::avanzar_Encoders(float distancia){
  long partida_m1 = position_encoder_M1, partida_m2 = position_encoder_M2;
  change_Velocity(pwm_giro_recta,pwm_giro_recta);

  if(distancia > 0)
    change_Direction(1,1);
  else
    if(distancia < 0)
      change_Direction(-1,-1);

  while(calcularDiferenciaDistancia(partida_m1,partida_m2) < distancia);


  change_Direction(0,0);
  frenoABS(1);
}

float Seguidor::calcularDiferenciaDistancia(long posicion_original_M1, long posicion_original_M2){
  leerEncoders();
  long dif_p_e1 = abs(position_encoder_M1 - posicion_original_M1), dif_p_e2 = abs(position_encoder_M2 - posicion_original_M2);



  float diferencia_entre_motores = (dif_p_e1 + dif_p_e2)/2.0;
  float distancia_recorrida = diferencia_entre_motores*0.08635;
  return distancia_recorrida;


}
