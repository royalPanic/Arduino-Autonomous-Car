#define trigPin 12
#define echoPin 13

int n;
int duration, distance;

String readString;

#include <Servo.h>
#include <NewPing.h>
Servo myservo1;  // create servo object to control servo
Servo myservo2;

void setup() {
  Serial.begin(9600);
  myservo1.attach(8); // assigns the servo to a pin
  myservo2.attach(9);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, HIGH);
  _delay_ms(500);
  digitalWrite(trigPin, LOW);
  distance = pulse_in(echoPin, HIGH);

  if (distance < 40) { // this is the distance which the rover has to stop
    digitalWrite(3, HIGH);
    myservo1.write(n); // controls the direction of the motors
    myservo2.write(180-n);
   delay(1000);  // how long the wheels spin
   myservo1.write(n);
   myservo2.write(90-n);
   delay(500);
}
  else { // what the rover will do if it doesn't sense anything
    digitalWrite(3, LOW);
    myservo1.write(180-n);
    myservo2.write(n);
}
}
