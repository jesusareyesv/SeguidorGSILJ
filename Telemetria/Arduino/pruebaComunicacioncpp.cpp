int led = 13;
int incomingByte = 0;

void setup(){
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}

void loop(){
  if(Serial.available()){
      incomingByte = Serial.read();

      Serial.print("He recibido: ");
      Serial.println(incomingByte, DEC);
  }else{
    Serial.println("No se ha recibido nada");
  }
}
