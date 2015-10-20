#include <Encoder.h>

Encoder myEnc(2, 3);

int tinicio;
bool flag =false;
double rev=0;
double frecuencia;
int PWM;
float v_angular;
long t_anterior;
long t_actual;
long dif_tiempo;
long position_a, position_actual;
long position = -999;
bool serialA;
double errorFrecuencia;


void setup() {
  Serial.begin(19200);
  Serial.println("Basic NoInterrupts Test:");
  pinMode(4,OUTPUT);
  
  pinMode(7,OUTPUT);
  tinicio = millis();
  flag =false;
  t_anterior = t_actual = millis();
  position = position_a = -999;
  PWM = 0;serialA = false;
}

void loop() {
  long newPos = myEnc.read();
  if (newPos != position) {
    position = newPos;
    //Serial.println(position);
  }
  
  t_actual = millis();
  dif_tiempo = t_actual - t_anterior;

  if(dif_tiempo >= 100){
    rev = (position - position_a)/120.0 ;
    if(rev < 0)
      rev*=-1;
    frecuencia = rev / double(dif_tiempo / 1000.0);
    errorFrecuencia = abs(PWM*50/255.0 - frecuencia);
    t_anterior = t_actual;
    position_a = position;
    v_angular = 6.28*frecuencia;

    
    
    if(serialA){
                Serial.print("*****************dif t: ");Serial.println(dif_tiempo);
      Serial.print("Frecuencia: ");Serial.println(frecuencia);
      Serial.print("V_angular: ");Serial.println(v_angular);
      Serial.print("*****Tiempo:");Serial.print(millis() - tinicio);Serial.print("  *****");Serial.println(rev);
      Serial.print("***********Error Frecuencia:");Serial.println(errorFrecuencia);
      }
  }
    
  if(Serial.available()){
    char temp = Serial.read();

    switch(temp){
      case 'r':flag = true;break;
      case 's':flag = false;break;
      case 'b': break;
      case 'n':PWM = Serial.parseInt();Serial.print("PWM CAMBIADO A=");Serial.println(PWM);break;
      case 'x':serialA = true;break;
      case 'y':serialA = false;break;
    }
    t_anterior = t_actual = tinicio = millis();
    
  }
  runMotor();
}

void runMotor()
{
  if(flag){
    digitalWrite(4,HIGH);
    digitalWrite(7,LOW);
    analogWrite(6,PWM);
  }
  else{
    digitalWrite(4,LOW);
    digitalWrite(7,LOW);
    analogWrite(6,0);
  }
}
