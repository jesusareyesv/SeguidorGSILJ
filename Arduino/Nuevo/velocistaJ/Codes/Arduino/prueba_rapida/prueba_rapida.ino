void setup()
{
  //M1
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  //M1
  //M2
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  //M2
  pinMode(4,OUTPUT);
  //pinMode(13,OUTPUT);
  Serial.begin(9600);
  //digitalWrite(13,LOW);
}

void loop()
{
  /*if(Serial.available()){
    char resp = Serial.read();
    if(resp == 'r'){
      digitalWrite(13,HIGH);
      digitalWrite(4,HIGH);
       runM(120);
    }
    else if(resp == 's'){
      digitalWrite(13,LOW);
      runM(0);
    }
  }*/delay(3000);
     //digitalWrite(13,HIGH);
     digitalWrite(4,HIGH);
     runM(120);
     delay(3000);  
     //digitalWrite(13,LOW);
     runM(0);             
}

void runM(int PWM){
  //M1
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  analogWrite(11, PWM);
  //M2
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  analogWrite(10, PWM);
}
