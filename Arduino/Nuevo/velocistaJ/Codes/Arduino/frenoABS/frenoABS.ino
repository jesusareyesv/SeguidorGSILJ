#define distance_sensor 13
#define forwardM1 6
#define forwardM2 8
#define backwardM1 5
#define backwardM2 7
#define pwmM1 11
#define pwmM2 10

#define stby_pin 4

#define pwm_run 160
#define pwm_obst 80
//#define pwm_ABS 120

int pwm_ABS = pwm_run + 40;

bool activo = true;

void setup(){
	pinMode(distance_sensor,INPUT);

	pinMode(forwardM1,OUTPUT);
	pinMode(forwardM2,OUTPUT);
	pinMode(backwardM1,OUTPUT);
	pinMode(backwardM2,OUTPUT);
  activo = true;
  delay(3000);
}

void loop(){
  if(activo){
        runMot();
	if(!digitalRead(distance_sensor)){
    frenoABS();
    avoid();
	  }
  }
}

void runMot(){
	
	digitalWrite(forwardM1,HIGH);	
	digitalWrite(backwardM1,LOW);
	analogWrite(pwmM1,pwm_run);

	digitalWrite(forwardM2,HIGH);	
	digitalWrite(backwardM2,LOW);
	analogWrite(pwmM2,pwm_run);

	digitalWrite(stby_pin,HIGH);
	
}

void frenoABS(){
	for(int i = 0; i < 4; i++){
		paradaRapida();
		delay(20);

		runBack();
		delay(30);
	}
  paradaRapida();
  activo = false;
}

void paradaRapida(){
	digitalWrite(forwardM1,LOW);
	digitalWrite(forwardM2,LOW);
	digitalWrite(backwardM1,LOW);
	digitalWrite(backwardM2,LOW);
}

void runBack(){
  digitalWrite(forwardM1,LOW);  
  digitalWrite(backwardM1,HIGH);
  analogWrite(pwmM1,pwm_ABS);

  digitalWrite(forwardM2,LOW);  
  digitalWrite(backwardM2,HIGH);
  analogWrite(pwmM2,pwm_ABS);
}

void avoid(){
  digitalWrite(forwardM1,LOW); 
  digitalWrite(backwardM1,HIGH);
  analogWrite(pwmM1,pwm_obst);

  digitalWrite(forwardM2,HIGH); 
  digitalWrite(backwardM2,LOW);
  analogWrite(pwmM2,pwm_obst);
  delay(260);
  paradaRapida();
  delay(100);
  digitalWrite(forwardM1,HIGH);  
  digitalWrite(backwardM1,LOW);
  analogWrite(pwmM1,pwm_obst);

  digitalWrite(forwardM2,HIGH); 
  digitalWrite(backwardM2,LOW);
  analogWrite(pwmM2,(pwm_obst*0,20));
  delay(1200);
  paradaRapida();
  digitalWrite(forwardM1,LOW); 
  digitalWrite(backwardM1,HIGH);
  analogWrite(pwmM1,pwm_obst);

  digitalWrite(forwardM2,HIGH); 
  digitalWrite(backwardM2,LOW);
  analogWrite(pwmM2,pwm_obst);
  delay(260);
  paradaRapida();
}
