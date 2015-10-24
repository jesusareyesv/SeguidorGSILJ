#include "Seguidor.h"

Seguidor::Seguidor(double kp,double ki,double kd){
  this->k_P = kp;
  this->k_I = ki;
  this->k_D = kd;

  this->proportional = this->derivative = this->integral = 0;
  this->init();
}

void Seguidor::init(){
  //Serial.begin(baud_rate_Serial);
  Serial1.begin(baud_rate_Bluetooth);
  pinMode(direction_forward_M1_pin,OUTPUT);
  pinMode(direction_forward_M2_pin,OUTPUT);
  pinMode(direction_backward_M1_pin,OUTPUT);
  pinMode(direction_backward_M2_pin,OUTPUT);

  pinMode(stby_pin,OUTPUT);
  pinMode(distance_sensor_pin,INPUT);

  /*pinMode(encoderA1_pin,INPUT);
  pinMode(encoderA2_pin,INPUT);
  pinMode(encoderB1_pin,INPUT);
  pinMode(encoderB2_pin,INPUT);*/

  PWM_MIN = pwm_min;
  PWM_MAX = pwm_max;
  PWM_ABS = pwm_ABS;
  PWM_BASE = pwm_base;
  FRENO_CURVA = freno_Curva;

  infrarred_active = distance_active = true;
  robot_active = false;
  digitalWrite(stby_pin,HIGH);
//  t_inicio = millis();
//  t_anterior = t_actual = millis();
}//like python

void Seguidor::runing_Seguidor(){

  communication_principal();
  if(robot_active){
    Serial.println("Activo");
    if(!infrarred_active)
      line_position = desired_position;

    distance_sensor = 0;
    if(distance_active)
      if(digitalRead(distance_sensor_pin) == HIGH)
        distance_sensor = 1;

    difference_time = actual_time - encoders_time;
    if(difference_time >= bypass_time_encoders){
      this->calculate_angular_values();
      encoders_time = actual_time;
    }

    PID_processing();
    adjust_velocities();
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
}

void Seguidor::PID_processing(){
  Serial.print("Desired");Serial.println();
  error = double(line_position) - double(desired_position);

  /*Los separé para control*/
  proportional = k_P * error;
  derivative = k_D * (error - error_antes);
  suma_integral += error;

  suma_integral = constrain(suma_integral,-255,255);

  integral = k_I * suma_integral;

  sumaPID = proportional + derivative + integral;
  //Serial.print("P:");Serial.print(proportional);Serial.print("D: ");Serial.println(derivative);
  error_antes   = error;
  pwmM1  = PWM_BASE + sumaPID;
  pwmM2  = PWM_BASE - sumaPID;
  //Serial.print("pwm1: ");Serial.print(pwmM1);Serial.print(" pwm2: ");Serial.println(pwmM2);
}

void Seguidor::adjust_velocities(){
  //pwmM1 = pwmM2 = pwm_max;

  float porc_error = abs((float)(error)/(float)(desired_position));
  /*Serial.print("Desired:");Serial.println(desired_position);
  Serial.print("Position:");Serial.println(line_position);
  Serial.print("Error Pos:");Serial.println(error);
  Serial.print("Porcentaje error:");Serial.println(porc_error);*/

  /*if(porc_error)
    frenoABS(FRENO_CURVA);*/
  if(porc_error > 0.7){
    pwmM2 = pwmM1;
    change_Velocity(pwmM1,pwmM2);
    change_Direction(1,-1);
  }else{
    if(porc_error < -0.7){
      pwmM1 = pwmM2;
      change_Velocity(pwmM1,pwmM2);
      change_Direction(-1,1);
    }else{
      change_Velocity(pwmM1,pwmM2);
      change_Direction(1,1);
    }
  }
}

void Seguidor::set_SensorsValues_LinePosition(unsigned int* values, unsigned int lineP){
  this->sensors_values = values;
  line_position = lineP;
  Serial.println(lineP);
}

void Seguidor::set_Positions_Encoders(long pem1, long pem2){
  position_encoder_M1 = pem1;
  position_encoder_M2 = pem2;
}

void Seguidor::calculate_angular_values(){
  double revoluciones_M1 = (position_encoder_M1 - position_encoder_antes_M1)/120.0;
  double revoluciones_M2 = (position_encoder_M2 - position_encoder_antes_M2)/120.0;

/*  if(rev < 0)
    rev *=-1;*/

  v_angular_M1_antes = v_angular_M1;
  v_angular_M2_antes = v_angular_M2;

  frequency_M1 = revoluciones_M1/ double(difference_time/1000.0);
  frequency_error_M1 = abs(pwmM1*50/255.0 - frequency_M1);

  frequency_M2 = revoluciones_M2/ double(difference_time/1000.0);
  frequency_error_M2 = abs(pwmM2*50/255.0 - frequency_M2);
  /*Añadido*/
  position_encoder_antes_M1 = position_encoder_M1;
  position_encoder_antes_M2 = position_encoder_M2;
  /*Añadido*/
  v_angular_M1 = 6.28*frequency_M1;
  a_angular_M1 = v_angular_M1 - v_angular_M1_antes;

  v_angular_M2 = 6.28*frequency_M2;
  a_angular_M2 = v_angular_M2 - v_angular_M2_antes;
}

void Seguidor::emergency_stop(){
  digitalWrite(stby_pin,LOW);
}

void Seguidor::frenoABS(int times){
  for(int i = 0; i < times; i++){
    change_Velocity(pwm_ABS,PWM_ABS);
    delay(20);
    change_Direction(-1,-1);
		delay(30);
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
//---------------------------COMMUNICATION

void Seguidor::communication_principal(){
  communication_Read();
  if(robot_active)
    communication_Write();
}

void Seguidor::communication_Read(){
  if(Serial1.available()){
    char ordenActual = Serial1.read();

    switch(ordenActual){
      case 'p':robot_active = false; Serial1.println("message/Detenido");break;//correr

      case 'r':robot_active = true ; Serial1.println("message/Activo");break;//parar

      case 's': status(); break;//comprobar estado

      case 'v'://cambia los valores de las constantes PID
        k_P = Serial1.parseFloat();
        k_I = Serial1.parseFloat();
        k_D = Serial1.parseFloat();

        Serial1.print("message/Constantes cambiadas -> P=");Serial1.print(k_P);Serial1.print("/I=");Serial1.print(k_I);Serial1.print("/D=");Serial1.println(k_D);
        //Serial.print("message/Constantes cambiadas -> P=");Serial.print(P_const);Serial.print("/I=");Serial.print(I_const);Serial.print("/D=");Serial.println(D_const);
        break;

      case 'a'://activa sensores
        onOffSensors(true);
        break;

      case 'd': //desactiva sensores
          onOffSensors(false);
        break;

        case 'k':
            //clave = Serial1.parseInt();
            //Serial1.print("message/Clave cambiada a:");Serial1.println(clave);
            //Serial.print("message/Clave cambiada a:");Serial.println(clave);
          break;

        case 'C':
          PWM_MIN = Serial1.parseInt();
          PWM_MAX = Serial1.parseInt();
          PWM_ABS = Serial1.parseInt();
          PWM_BASE = Serial1.parseInt();

          Serial1.print("message/PWM Cambiado -> Min=");Serial1.print(PWM_MIN);Serial1.print("/Max=");Serial1.print(PWM_MAX);Serial1.print("/ABS=");Serial1.print(PWM_ABS);Serial.print("Base");Serial.println(PWM_BASE);
          break;
        case 'f':
          FRENO_CURVA = Serial1.parseInt();
          Serial1.print("message/Freno cambiado a (veces):");Serial.println(FRENO_CURVA);
          break;

        case 'e':
          String sssss = Serial1.readString();
          Serial1.print("message/ECHO=");Serial1.println(sssss);
          //Serial.print("message/ECHO=");Serial.println(sssss);
          break;

    }
    //Serial1.flush();OJO PROBAR FUNCIONALIDAD
  }
}

void Seguidor::communication_Write(){
  /*Serial.println(error);
  Serial.print("data/");
  Serial.print(proportional);Serial.print("   ");
  Serial.print("/");
  Serial.print(integral);Serial.print("   ");
  Serial.print("/");
  Serial.print(derivative);Serial.print("   ");
  Serial.print("/");
  Serial.print(sumaPID);Serial.println();
  Serial.print("/");
  Serial.print(pwmM1);Serial.print("   ");//Serial1.print(PWMI);
  Serial.print("/");
  Serial.print(pwmM2);Serial.print("   ");//Serial1.print(PWMD);
  Serial.print("/");
  Serial.print(loop_time);Serial.println();
  Serial.print("/");
  Serial.print(line_position);Serial.println();//posicion de la linea
  Serial.print("/");
  Serial.print(distance_sensor);//(1) si obstaculo, (0) si no
  Serial.print("/");
  Serial.print(v_angular_M1);
  Serial.print("/");
  Serial.print(v_angular_M2);
  Serial.print("/");
  Serial.print(a_angular_M1);
  Serial.print("/");
  Serial.println(a_angular_M2);
  Serial.println();Serial.println();Serial.println();*/

  Serial1.print("data/");
      Serial1.print(proportional);
      Serial1.print("/");
      Serial1.print(integral);
      Serial1.print("/");
      Serial1.print(derivative);
      Serial1.print("/");
      Serial1.print(sumaPID);
      Serial1.print("/");
      Serial1.print(pwmM1);//Serial1.print(PWMI);
      Serial1.print("/");
      Serial1.print(pwmM2);//Serial1.print(PWMD);
      Serial1.print("/");
      Serial1.print(loop_time);
      Serial1.print("/");
      Serial1.print(line_position);//posicion de la linea
      Serial1.print("/");
      Serial1.print(distance_sensor);//(1) si obstaculo, (0) si no
      Serial1.print("/");
      Serial1.print(v_angular_M1);
      Serial1.print("/");
      Serial1.print(v_angular_M2);
      Serial1.print("/");
      Serial1.print(a_angular_M1);
      Serial1.print("/");
      Serial1.println(a_angular_M2);
}

void Seguidor::onOffSensors(bool estado){
  int n_sensores = Serial1.parseInt(), i = 0, temp = 0;

  for(i = 0; i < n_sensores; i++){
    temp = Serial1.parseInt();

    if(temp == 1){
      infrarred_active = estado;
      Serial1.print("message/Sensores infrarrojos ");
      Serial1.println((estado)?"activados":"desactivados");

      /*Serial.print("message/Sensores infrarrojos ");
      Serial.println((estado)?"activados":"desactivados");*/
    }

    if(temp == 2){
      distance_active = estado;
      Serial1.print("message/Sensor de distancia ");
      Serial1.println((estado)?"activado":"desactivado");

      /*Serial.print("message/Sensor de distancia ");
      Serial.println((estado)?"activado":"desactivado");*/
    }
  }
}

void Seguidor::status(){
  Serial1.print("status/");

  if(infrarred_active)
    Serial1.print(1);
  else
    Serial1.print(0);

    Serial1.print("/");

  if(distance_active)
    Serial1.print(1);
  else
    Serial1.print(0);

  Serial1.println();
}