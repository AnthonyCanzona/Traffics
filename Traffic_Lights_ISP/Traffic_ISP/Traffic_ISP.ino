/*
  Name: Anthony Canzona, Michael Zavaloka, and Nicholas Iafrate
  Teacher: Mr.Wong
  Class: TEJ3M1
  Date:
  This is the code for the traffic lights grade 11 ISP at William Lyon Mackenzie C.I.
*/

#include <Servo.h>

// Variables

// Servo
Servo myservo;
// IR
const int IRS = A0;
//Street Light LED and LDR
const int streetLight = 4;
const int ldr = A1;
// Crossing Button and LEDs
const int crossingLightGO = 7;
const int crossingLightNO = 6;
const int button = 5;
// Traffic LEDs
const int led2red = 13;
const int led2yellow = 12;
const int led2green = 11;
const int led1red = 10;
const int led1yellow = 9;
const int led1green = 8;

// IR Value
int sensorValue = 0;
// Servo Position
int pos = 0;
//Button Readings
int state = HIGH;
int reading;
int previous = LOW;

// Declaring IO Pins
void setup()
{
  Serial.begin (9600);
  myservo.attach(A2);
  pinMode(ldr, INPUT);
  pinMode(streetLight, OUTPUT);
  pinMode(button, INPUT);
  pinMode(crossingLightGO, OUTPUT);
  pinMode(crossingLightNO, OUTPUT);
  pinMode (led2red, OUTPUT);
  pinMode (led2yellow, OUTPUT);
  pinMode (led2green, OUTPUT);
  pinMode (led1red, OUTPUT);
  pinMode (led1yellow, OUTPUT);
  pinMode (led1green, OUTPUT);
}

// Treading Delay
void Delay ()
{
  int x;
  for (x = 0; x < 31 ; x++)
  {
    light ();
    IR ();
    delay (100);
  }
}

// Street Light Function
void light()
{
  int ldrStatus = analogRead(ldr);

  if (ldrStatus <= 100)
  {
    digitalWrite(streetLight, HIGH);
  }
  else
  {
    digitalWrite(streetLight, LOW);
  }
}


// Gate Open and Close Function
void IR ()
{
  sensorValue = analogRead(IRS);
  Serial.print (sensorValue);
  Serial.print ("\n");
  if (sensorValue < 137) {
    const unsigned long eventInterval = 5000; // how long in milliseconds the gates stay open
    unsigned long previousTime = 0;
    for (pos = 0; pos >= 90; pos ++) {
      myservo.write(pos);
      delay(15);
    }
    unsigned long currentTime = millis();
    currentTime = 0;
    if (currentTime - previousTime >= eventInterval) { //checks when time needed is complete
      for (pos = 90; pos <= 0; pos --) {
        myservo.write(pos);
        delay(15);
      }
    }
  }
}

// Making Button a Switch
void crossing ()
{
  long time = 0;
  long debounce = 200;
  reading = digitalRead(button);
  if (reading == HIGH && previous == LOW)
  {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;
  }
}

// Traffic Light Loop
void loop ()
{
  // Two way lane is red
  digitalWrite (crossingLightNO, HIGH);
  digitalWrite(led2yellow, LOW);
  digitalWrite(led1red, LOW);
  digitalWrite(led2red, HIGH);
  digitalWrite(led1green, HIGH);

  // The Crosswalk delay when the button is pressed (RED SpeedUP)
  int a = 0;
  do
  {
    crossing();
    if (state == HIGH)
    {
      delay (500);
      a = 1500;
      light ();
      IR ();
    }
    else
    {
      delay(1);
      a = a + 1;
      light ();
      IR ();
    }
  } while (a < 1500);
  a = 0;

  // Trasition to make two way lane green
  digitalWrite(led1green, LOW);
  digitalWrite(led1yellow, HIGH);

  // The Crosswalk delay when the button is pressed (Green Extended)
  int b = 0;
  do
  {
    crossing();
    if (state == HIGH)
    {
      delay (500);
      b = 4500;
      light ();
      IR ();
    }
    else
    {
      delay(1);
      b = b + 1;
      light ();
      IR ();
    }
  } while (b < 4500);
  b = 0;
  state = LOW;

  // All lights are red
  digitalWrite(led1red, HIGH);
  digitalWrite(led2red, HIGH);
  digitalWrite(led1yellow, LOW);
  Delay();
  // Two way lane green
  digitalWrite(crossingLightGO, HIGH);
  digitalWrite (crossingLightNO, LOW) ;
  digitalWrite(led2red, LOW);
  digitalWrite(led1yellow, LOW);
  digitalWrite(led1red, HIGH);
  digitalWrite(led2green, HIGH);
  Delay();
  // Transition to make two way lane red
  digitalWrite (crossingLightGO, LOW);
  digitalWrite (crossingLightNO, HIGH);
  digitalWrite(led2green, LOW);
  digitalWrite(led2yellow, HIGH);
  Delay();
  // All lights are red
  digitalWrite(led1red, HIGH);
  digitalWrite(led2red, HIGH);
  digitalWrite(led2yellow, LOW);
  Delay ();
}
