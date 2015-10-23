long vez;

void setup() {
  Serial.begin(115200);
}

void loop() {
  vez++;
  Serial.print(vez);Serial.println(" vez");

}
