# Arduino Atonomous Car Project
###### By royal_Panic
---
## Introduction:
This project was made for the NJSHS STEM class, and is designed to help young people learn about programming with Arduino and how computer components interact. It uses several different components and enough code to help people grasp some of the basics of C/C++.

## Materials You Will Need:
* A computer with the Arduino IDE (v1.8.5+).
* An Arduino UNO board.
* An Arduino "Smart Car" kit, we used [this one](PUT LINK HERE).
* An ultrasonic sensor, a good one is a generic `HC-SR04` sensor.

## Assembly of the Kit:
Now obviously this is going to vary by the type of kit you get, but I'll outline the process of building ours, step by step, as the instructions aren't the best.
1. To
2. Be
3. Determined

## Coding:
The code is actually one of the simpler parts of the project, it's easy to make and update, and leaves some room for customization if you know your way around C.

### The Basic Template:
First, let's start with a simple template that will give basic functionality to the car.
```c++
#define trigPin 12
#define echoPin 13

int n;
int duration, distance;

String readString;

#include <Servo.h>
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
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  if (distance < 40) { // this is the distance which the rover has to stop
    digitalWrite(3, HIGH);
    myservo1.write(n); // controls the direction of the motors
    myservo2.write(180-n);
   delay(1000);  // how long the wheels spin
   myservo1.write(n);
   myservo2.write(90-n);
   delay(500);
}
  else { // what the rover will do if it doen't sense anything
    digitalWrite(3, LOW);
    myservo1.write(180-n);
    myservo2.write(n);
}
}
```
Now, we can look further into how the code works in order to increase its functionality.

### Libraries:
Let's start with *Libraries*:
C Libraries are akin to Python Modules. They're extra sets of commands you can choose to import into your code in order to make other things work. If you've worked with Python at all, you can probably instantly recognize some of the most frequently used libraries, and how they're imported.
```Python
import time
import pygame
import random as r #allows us to use 'r' in place of 'random'. For instance, `random.randint(1,10)` becomes `r.randint(1,10)`.
from colorama import colorama #allows importing of select commands from a large module.
```
C Libraries are remarkably similar, and are imported in a fairly similar fashion, actually. Here's an example of importing 3 libraries I use frequently.
```C++
#import <LiquidCrystal.h>
#import <NewPing.h>
#import <cairo.h>
```
So we can see above in our template code that we're using the `Servo` library in order to control the servos on our car, but no library to control the ultrasonic sensor. This is because the Arduino has basic commands already in it, such as the `pingIn` command used to check distance via the ultrasonic sensor. However, the `pingIn` command is at best, horrendously slow, and at worst, completely unreliable. So what if we replace it with a different library command that is more suited to the task? This is where the `NewPing` library comes into play. Let's first start by importing the library. With the modern Arduino IDE, there's a 50/50 chance the library will be installed by default, and if it isn't, let's install it now.

### Installing the `NewPing` Library:
To do this, you should first head to [this site](https://bitbucket.org/teckel12/arduino-new-ping/downloads/) and grab the `.zip` of the latest version of the library. After, you're going to want to open up the IDE and navigate to the "Sketch" menu. Once there, you're going to want to go to "Include Library". Continue to "Add .zip Library" Then, navigate to the `.zip` file of the library you just downloaded, and finish the prompt. Now if we return to the "Include Library" dropdown, we see that the `NewPing` library is listed at the bottom of the menu, ready to be used.

### Using the `NewPing` Library:
Firstly, we;re going to need to include the library in our code. Doing this is quite simple, all we have to is find the place where the other library is imported, and append `#import <NewPing.h>`.
```c++
...
String readString;

#include <Servo.h>
#include <NewPing.h> //add this library to increase functionality of the ultrasonic sensor
Servo myservo1;  // create servo object to control servo
Servo myservo2;
...
```
Now we're ready to go. The `NewPing` library contains a command that will ping way more efficiently than `pingIn`, and will do so reliably. This command, `ping_in`, will virtually replace all instances of `pingIn` to make our code faster and more efficiently.
