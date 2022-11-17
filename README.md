
# Hi there. we are ibn roshd falcons team
Here is the Youtube video link for the Robot → https://youtu.be/Kr0BLmSGszo

# let us explain to you the strategy for our robot in the game play:
 As the game starts the robot start using the ultrasonicthe besides the wall ( if it is the right or left ultrasonic ) to track the wall with no friction with the wall. So he moves away to the right or left side the ultrasonic reads that the robot is getting away from the wall so the ultrasonic sends an order to the Arduino to get closer to the wall. Briefly the three Ultrasonics in the front of the robot should keep the robot steady and keep the robot in the middle. When the robot sees the blue line the huskylens will send an order to the Arduino to go forward and then turn 90° digree to the left and then go back for a second and complete the loop repeating this method and if the robot faced a green pillar the huskylens will also send an order to the Arduino to complete it way on the left side of the pillar. And if the robot faced a red pillar the robot will complete it way on the right side of the pillar also using the huskylens. Like that the robot will complete it three rounds reading all the blue lines three times and then stop where he started.

# How to use arduino uno:

Once the circuit has been created on the breadboard, you’ll need to upload the program (known as a sketch) to the Arduino.  The sketch is a set of instructions that tells the board what functions it needs to perform. An Arduino board can only hold and perform one sketch at a time.  The software used to create Arduino sketches is called the IDE which stands for Integrated Development Environment.  The software is free to download and can be found at https://www.arduino.cc/en/Main/Software

Every Arduino sketch has two main parts to the program:

void setup() – Sets things up that have to be done once and then don’t happen again.

void loop()  – Contains the instructions that get repeated over and over until the board is turned off.


# The program
all of our source codes are in the src directory

# The components of the robot
The robot's components are:
### 1-The Arduino uno:
Arduino UNO is a microcontroller board based on the ATmega328P. It has 14 digital input/output pins (of which 6 can be used as PWM outputs), 6 analog inputs, a 16 MHz ceramic resonator, a USB connection, a power jack, an ICSP header and a reset button. It contains everything needed to support the microcontroller; simply connect it to a computer with a USB cable or power it with a AC-to-DC adapter or battery to get started. You can tinker with your UNO without worrying too much about doing something wrong, worst case scenario you can replace the chip for a few dollars and start over again.
### 2-Huskylens
the robot's vision sensor with 7 built-in functions: face recognition, object tracking, object recognition, line tracking, color recognition, tag recognition and object classification.
Through the UART / I2C port, HuskyLens can connect to Arduino and micro:bit to help you make very creative projects without playing with complex algorithms. It allows the robot to see the pillars on the game board. if it's red the robot should turn to the right side of the pillar. and if it's a green pillar the robot should turn to the left side of the pillar.
Specification:
Processor: Kendryte K210
#### Image Sensor:
SEN0305 HuskyLens: OV2640 (2.0Megapixel Camera)
SEN0336 HuskyLens PRO: OV5640 (5.0MegaPixel Camera)
Supply Voltage: 3.3~5.0V
Communication Port: UART; I2C
Built-in Algorithms: Face Recognition, Object Tracking, Object Recognition, Line Tracking, Color Recognition, Tag Recognition, Object Classification
Connectors:
USB Connector: power supply for Huskylens; connect to the computer to upgrade the firmware
4pin Connector in UART Mode
4pin Connector in I2C Mode
There are two buttons on the HuskyLens, the function button and the learning button. The basic operations of these two buttons are shown as follows:
Dial the "function button" to left or right to switch different functions.

### 3- Ultrasonic Sensor HC-SR04
is a sensor that can measure distance. It emits an ultrasound at 40 000 Hz (40kHz) which travels through the air and if there is an object or obstacle on its path It will bounce back to the module. Considering the travel time and the speed of the sound you can calculate the distance. It makes sure that the robot does not bump into anything around it, So it should keep distance between the robot and anything around it, We actually used three ultra sonics in our robot so it can allow the robot to see any obstacle to it right, front and left.
###4- 
DC Motors, Obviously so the robot can move, We used two motor and we placed them under the robot next to the tires and it rotates in the same direction they go forward together and go back together.
### 5- Servo
is a rotary actuator that allows for precise control of angular position, velocity and acceleration. it controls the robot's movement horizontally.
### 6- The L298N Motor Driver
is a controller that uses an H-Bridge to easily control the direction and speed of up to 2 DC motors. it is the mediator between the Arduino and the motors, So any command from the Arduino the motor drive should delivers it to the motors.
How Motor Driver Module Works:
This module uses two techniques for the control speed and rotation direction of the DC motors. These are H-Bridge – For controlling rotation direction and PWM – For controlling the speed.
### 7- A breadboard 
is a rectangular plastic board with a bunch of tiny holes in it. These holes let you easily insert electronic components to prototype (meaning to build and test an early version of an electronic circuit). it allows us to make our electrical circuits that transmit movement through the robot.
### 8- Batteries
We used two batteries that gives us seven volts in total.
### 9- Laser cutter
We used the laser cutter to make one of the important pieces of the robot and we put it under the robot to hold the tires ( We will put a pdf for the piece in our profile ).
### 10- the switches 
there are two switches in the robot one to turn the robot on and off, and the other one is to let the robot start the game.
