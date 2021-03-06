---

# As a heads-up, royalPanic will no longer be maintaining this repository. Ownership has been transferred to Sam (Jadeflames8061) for her to do as she pleases with it. 

---

# Arduino Autonomous Car Project
###### By [royal_Panic](https://github.com/royalPanic), Samarah DeChane, & [Paige Patz](https://github.com/StardustBot).
---
## Introduction:
This project was made for the NJSHS STEM class, and is designed to help young people learn about programming with Arduino and how computer components interact. It uses several different components and enough code to help people grasp some of the basics of C/C++.

## Materials You Will Need:
* A computer with the Arduino IDE (v1.8.5+).
* An Arduino UNO board.
* An Arduino "Smart Car" kit, we used [this one](https://www.amazon.com/gp/product/B07F6Z38WM).
* A `L298N` stepper-motor controller, we used [this one](https://www.amazon.com/gp/product/B01H6VMEFY).
* An ultrasonic sensor, a good one is a generic `HC-SR04` sensor. You can get one from a trusted seller [here](https://www.adafruit.com/product/3942?gclid=CjwKCAjwiZnnBRBQEiwAcWKfYr9ymVUCjvo7Jid1eiym_gie3zviAb6XuVQ514xVnlMY2H0v86z2gRoCvfwQAvD_BwE).

## Assembly of the Kit:
Now obviously this is going to vary by the type of kit you get, but I'll outline the process of building ours, step by step, as the instructions aren't the best.
1. Remove the protective paper from the chassis and fasteners.
2. Insert 4 of the fasteners through the large slits bottom of the bottom chassis panel, making sure they stick all the way up.
3. Place the motors on the inside of the fasteners (towards the center of the chassis) with the axles facing away from each other and parallel to the chassis make sure the holes are lined up.
4. Add the remaining 4 fasteners to the indentations on the outside and push a screw through each of the holes (from the outside) in the fasteners and motors using nuts to secure them in place.
5. Line the wheels up on the axles and push them on (they will click when they are secured).
6. Using a screwdriver attach the metal spacers to the chassis on the corners and between the wheels, they are attached with a screw on each side.
7. Place the second panel on top of the car and secure using more screws to the spacers.
8. Flip over the entire chassis and secure the battery pack to the panel with screws and nuts.

## Wiring of the Kit:
This part, somewhat unsurprisingly, is going to be one of the more difficult parts of the project, seeing as though there were absolutely no instructions provided regarding this step.

Firstly, let's take a look at the components we're working with:
### The Arduino UNO Board:
The Arduino UNO is a consumer microcontroller board that allows you to deploy code on a small prototyping scale with no risk of permanent change or damage, and is best suited for smaller projects like the ones we're doing.

### The Stepper Motor Controller:
It should be noted that we're not actually using a stepper motor in this project, but we're going to make use of the the system by which this chip controls a bipolar stepper to instead make it control two DC motors. The only problem is that we have four. This is going to need some splicing of wires, but luckily the kit came with 2 2x2 cables, so we don't have to worry too too much about how to splice.

### HC-SR04 Ultrasonic Sensor:
This is a standard ultrasonic sensor module, it uses the time between sending and receiving a pulse of sound to calculate the distance to an object. This sensor has a range of about 4 meters.

### Generic DC Motor (x4):
There's really nothing very special or notable about these, negative to negative, positive to positive, apply power, and it spins. We're going to wire all of them up to run off of a single dual motor controller.

## Wiring Diagram:
![Wiring Diagram](https://github.com/royalPanic/Arduino-Autonomous-Car/blob/master/arduinocarwiring.png)

## Wiring Instructions:
1. First, we're going to need to connect the motors to the motor controller. To do this, we'll need a soldering iron to make some heavier connections. The wires that were shipped with the kit are insulated threaded copper, which means it will be nearly impossible to strip them. We're going to connect a negative and positive wire from each of the ribbon cables to each of the motors on one side, then connect **both** red wires into one of the motor controller ports and **both** black wires into the other on the same side. We'll repeat this for the other set of motors on the other side of the car.
2. Now we'll see how the motor controller itself needs to be wired to the Arduino board. First we're going to give the controller its own power supply. We'll hook a batter pack up to its 5V and Ground terminals. We'll then connect the four motor inputs to the first four digital pins on the arduino.
3. To wire the ultrasonic sensor to the Arduino board, we're going to need to keep track of its four pins. We have the **Trigger Pin**, **Echo Pin**, **Grounding Pin** and **5V Input Pin**. We'll start by connecting the Echo pin to digital pin 6 and the Trigger pin to digital pin 7. We'll then connect the VCC pin to the arduino's 5v output, and the Ground pin to the arduino's ground pin.

## Coding:
The code is actually one of the simpler parts of the project, it's easy to make and update, and leaves some room for customization if you know your way around C.

### The Basic Template:
First, let's start with a simple template that will give basic functionality to the car.
```c++
#define trigPin 7
#define echoPin 6

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
C Libraries are akin to Python Modules. They're extra sets of commands you can choose to import into your code in order to make other things work. If you've worked with Python at all, you can probably instantly recognize some of the most frequently used modules, and how they're imported.

```Python
import time
import pygame
import random as r #allows us to use 'r' in place of 'random'. For instance, `random.randint(1,10)` becomes `r.randint(1,10)`.
from colorama import colorama #allows importing of select methods from a large module.
```

C Libraries are remarkably similar, and are imported in a fairly similar fashion, actually. Here's an example of importing 3 libraries I use frequently.
```c++
#import <LiquidCrystal.h>
#import <NewPing.h>
#import <cairo.h>
```
So we can see above in our template code that we're using the `Servo` library in order to control the servos on our car, but no library to control the ultrasonic sensor. This is because the Arduino has basic commands already in it, such as the `pingIn` command used to check distance via the ultrasonic sensor. However, the `pingIn` command is at best, horrendously slow, and at worst, completely unreliable. So what if we replace it with a different library command that is more suited to the task? This is where the `NewPing` library comes into play. Let's first start by importing the library. With the modern Arduino IDE, there's a 50/50 chance the library will be installed by default, and if it isn't, let's install it now.

### Installing the `NewPing` Library:
To do this, you should first head to [this site](https://bitbucket.org/teckel12/arduino-new-ping/downloads/) and grab the `.zip` of the latest version of the library. After, you're going to want to open up the IDE and navigate to the "Sketch" menu. Once there, you're going to want to go to "Include Library". Continue to "Add .zip Library" Then, navigate to the `.zip` file of the library you just downloaded, and finish the prompt. Now if we return to the "Include Library" dropdown, we see that the `NewPing` library is listed at the bottom of the menu, ready to be used.

### Using the `NewPing` Library:
Firstly, we're going to need to include the library in our code. Doing this is quite simple, all we have to is find the place where the other library is imported, and append `#include <NewPing.h>`.
```c++
...
String readString;

#include <Servo.h>
#include <NewPing.h> // add this library to increase functionality of the ultrasonic sensor
Servo myservo1;  // create servo object to control servo
Servo myservo2;
...
```
Now we're ready to go. The `NewPing` library contains a command that will ping way more efficiently than `pingIn`, and will do so reliably. This command, `ping_in`, will virtually replace all instances of `pingIn` to make our code run faster and more efficiently.

Our new code will look like this:
```c++
#define trigPin 7
#define echoPin 6

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
```
## Contributing:
**Want to contribute?**

We firmly believe that open source software should stay open source forever, and that anyone should be able to contribute to it to make it better. As such, as long as Panic is around, he'll be reviewing any pull requests, and updating the project. As such, if you see something that can be improved in the project, ***do not hesitate to fork this repo, and make a pull request with your changes back to the master***. Changes and upgrades are how innovation happens, so go wild.

---
