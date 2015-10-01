

#define proportional_c 0.2
#define integral_c 0.2
#define derivative_c 0.2
#define pinUltrasonido 2

bool activo = false;
int led = 13;
float P_const = proportional_c;
float I_const = integral_c;
float D_const = derivative_c;
double proportional, derivative, integral, suma;
int PWMI,PWMD, DUTY_CYCLE,line_position,sensor_distancia;
double v_angular1,v_angular2,a_angular1,a_angular2;

int clave = 1234;

bool distancia_activo, infrarrojos_activos;

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(led,OUTPUT);
  iniciarValores();
}

void loop(){
  comunicacion();

  if(activo){
    /*if(infrarrojos_activos){

    }*/

    if(distancia_activo){
      if(digitalRead(pinUltrasonido) == HIGH)
        sensor_distancia = 1;
      else
        sensor_distancia = 0;
    }

    digitalWrite(led,HIGH);
    proportional = random(0,30);integral = random(0,30);derivative = random(0,30);
    suma = proportional + integral + derivative;
    PWMI = random(0,256);PWMD = random(0,256);DUTY_CYCLE = random(0,56);
    line_position=random(0,1000);sensor_distancia=(random(0,100) >=50)?1:0;
    v_angular1=random(0,256);v_angular2=random(0,256);
    a_angular1=random(0,256);a_angular2=random(0,256);
    //poner las interrupciones
  }else{
    //desactivar las interrupciones
    digitalWrite(led,LOW);
  }
}

void iniciarValores(){
  distancia_activo = infrarrojos_activos = true;
}

void comunicacion(){
  //desactivar interrupciones
  communication_read();
  if(activo)
    communication_write();
  //activar interrupciones
}

void communication_read(){
  if(Serial1.available()){
    char ordenActual = Serial1.read();

    /*if(ordenActual != )
      Serial.read();
      */

    switch(ordenActual){
      case 'p':activo = false; Serial1.println("message/Detenido");Serial1.println("message/Detenido");break;//correr

      case 'r':activo = true ; Serial1.println("message/Activo");Serial1.println("message/Activo");break;//parar

      case 's': status(); break;//comprobar estado

      case 'v'://cambia los valores de las constantes PID
        P_const = Serial1.parseFloat();
        I_const = Serial1.parseFloat();
        D_const = Serial1.parseFloat();

        Serial1.print("message/Constantes cambiadas -> P=");Serial1.print(P_const);Serial1.print("/I=");Serial1.print(I_const);Serial1.print("/D=");Serial1.println(D_const);
        Serial.print("message/Constantes cambiadas -> P=");Serial.print(P_const);Serial.print("/I=");Serial.print(I_const);Serial.print("/D=");Serial.println(D_const);
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
            Serial.print("message/Clave cambiada a:");Serial.println(clave);
          break;
        case 'e':
          String s = Serial1.readString();
          Serial1.print("message/ECHO=");Serial1.println(s);
          Serial.print("message/ECHO=");Serial.println(s);
          break;

    }
    Serial1.flush();
  }
}

void communication_write(){
  Serial.print("data/");
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
  Serial.print(PWMD);
  Serial.print("/");
  Serial.print(DUTY_CYCLE);
  Serial.print("/");
  Serial.print(line_position);
  Serial.print("/");
  Serial.print(sensor_distancia);
  Serial.print("/");
  Serial.print(v_angular1);
  Serial.print("/");
  Serial.print(v_angular2);
  Serial.print("/");
  Serial.print(a_angular1);
  Serial.print("/");
  Serial.println(a_angular2);

    Serial1.print("data/");
    Serial1.print(proportional);
    Serial1.print("/");
    Serial1.print(integral);
    Serial1.print("/");
    Serial1.print(derivative);
    Serial1.print("/");
    Serial1.print(suma);
    Serial1.print("/");
    Serial1.print(PWMI);
    Serial1.print("/");
    Serial1.print(PWMD);
    Serial1.print("/");
    Serial1.print(DUTY_CYCLE);
    Serial1.print("/");
    Serial1.print(line_position);
    Serial1.print("/");
    Serial1.print(sensor_distancia);
    Serial1.print("/");
    Serial1.print(v_angular1);
    Serial1.print("/");
    Serial1.print(v_angular2);
    Serial1.print("/");
    Serial1.print(a_angular1);
    Serial1.print("/");
    Serial1.println(a_angular2);
}

void onOffSensors(bool estado){
  int n_sensores = Serial1.parseInt(), i = 0, temp = 0;

  for(i = 0; i < n_sensores; i++){
    temp = Serial1.parseInt();

    if(temp == 1){
      infrarrojos_activos = estado;
      Serial1.print("message/Sensores infrarrojos ");
      Serial1.println((estado)?"activados":"desactivados");

      Serial.print("message/Sensores infrarrojos ");
      Serial.println((estado)?"activados":"desactivados");
    }

    if(temp == 2){
      distancia_activo = estado;
      Serial1.print("message/Sensor de distancia ");
      Serial1.println((estado)?"activado":"desactivado");

      Serial.print("message/Sensor de distancia ");
      Serial.println((estado)?"activado":"desactivado");
    }
  }
}

void status(){//funcion para comprobar el robot| Se llama desde la consola de la telemetría
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
