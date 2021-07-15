const int analogInPin = A0; 
int sensorValue = 0;       

void setup() {

  Serial.begin(9600);

  pinMode(13, OUTPUT);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);

  // print the results to the serial monitor:
  Serial.print("\nsensor = ");
  Serial.print(sensorValue);

  if(sensorValue < 100){ //checks if object is there or not
    digitalWrite(13, HIGH);
    Serial.print("\nObject Detected");
    }
  else{
    digitalWrite(13, LOW);
    Serial.print("\nNo object in Front");
    }
  delay(500);
}
