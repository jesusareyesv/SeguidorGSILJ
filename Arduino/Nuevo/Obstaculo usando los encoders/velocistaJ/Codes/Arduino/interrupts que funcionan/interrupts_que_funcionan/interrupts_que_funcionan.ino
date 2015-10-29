/* Encoder Library - NoInterrupts Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

// If you define ENCODER_DO_NOT_USE_INTERRUPTS *before* including
// Encoder, the library will never use interrupts.  This is mainly
// useful to reduce the size of the library when you are using it
// with pins that do not support interrupts.  Without interrupts,
// your program must call the read() function rapidly, or risk
// missing changes in position.
/*
///////////////#define ENCODER_DO_NOT_USE_INTERRUPTS
*/
#include <Encoder.h>

// Beware of Serial.print() speed.  Without interrupts, if you
// transmit too much data with Serial.print() it can slow your
// reading from Encoder.  Arduino 1.0 has improved transmit code.
// Using the fastest baud rate also helps.  Teensy has USB packet
// buffering.  But all boards can experience problems if you print
// too much and fill up buffers.

// Change these two numbers to the pins connected to your encoder.
//   With ENCODER_DO_NOT_USE_INTERRUPTS, no interrupts are ever
//   used, even if the pin has interrupt capability
Encoder myEnc(2, 3);
//   avoid using pins with LEDs attached
int tinicio;
bool flag =false;
long rev=0;
double frecuencia;
float v_angular;
long t_anterior;
long t_actual;
long dif_tiempo;


void setup() {
  Serial.begin(9600);
  Serial.println("Basic NoInterrupts Test:");
  pinMode(4,OUTPUT);
  //pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  tinicio = millis();
  flag =false;
  t_anterior = t_actual = millis();
}

long position  = -999;

void loop() {
  
  
  long newPos = myEnc.read();
  if (newPos != position) {
    position = newPos;
    Serial.println(position);
  }
  rev = position/120;
  t_actual = millis();
  dif_tiempo = t_actual - t_anterior;

  if(dif_tiempo >= 80){
    frecuencia = rev / dif_tiempo;
    t_anterior = t_actual;
    v_angular = 6.28*frecuencia;
    Serial.print("dif t: ");Serial.println(dif_tiempo);
    Serial.print("Frecuencia: ");Serial.println(frecuencia);
    Serial.print("V_angular: ");Serial.println(v_angular);
  }
  
  Serial.print("*****Tiempo:");Serial.print(millis() - tinicio);Serial.print("  *****");Serial.println(rev);
  
  
  if(Serial.available()){
    char temp = Serial.read();

    switch(temp){
      case 'r':flag = true;break;
      case 's':flag = false;break;
      case 'b': break;
    }
    t_anterior = t_actual = tinicio = millis();
    
  }
  runMotor();
  // With any substantial delay added, Encoder can only track
  // very slow motion.  You may uncomment this line to see
  // how badly a delay affects your encoder.
  //delay(50);
}

void runMotor()
{
  if(flag){
    digitalWrite(4,HIGH);
    digitalWrite(7,LOW);
    analogWrite(6,80);
  }
  else{
    digitalWrite(4,LOW);
    digitalWrite(7,LOW);
    analogWrite(6,0);
  }
}
