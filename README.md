
# Hi there. we are black fingers team
Here is the Youtube video link for the Robot → https://youtu.be/Kr0BLmSGszo

# let us explain to you the strategy for our robot in the game play:
when the game begins, the robot relies on its Gyro balance sensor to maintain stability. It resets its balance when needed, allowing it to move forward and execute right or left turns smoothly. Positioned at the robot's front, three ultrasonic sensors serve as its eyes, preventing collisions with walls and columns. If these sensors detect the robot moving away from a wall, they promptly transmit a command to the Arduino, instructing it to approach the wall. Conversely, if the robot approaches too closely, the sensors signal the Arduino to retreat to a safe distance.

In essence, these front-facing ultrasonic sensors play a crucial role in ensuring the robot's stability and keeping it at a safe distance from obstacles. When the robot identifies a blue line via Huskylens, it constructs the Arduino to move forward, make a precise 90-degree left turn, and continue this pattern, effectively completing a loop. Simultaneously, as Huskylens detects the blue line, the Pixy camera, mounted on a servo, turns left by 90 degrees to focus on the column located on the left-hand side.

If Pixy encounters a green column, it commands the Arduino to execute an immediate left turn to navigate around the green obstacle. Similarly, when facing a red column, Pixy instructs the Arduino to move forward, creating an ample distance, and then initiating a left turn to navigate the right-hand side of the red column. This process repeats continuously, allowing the robot to complete three rounds, scanning all blue lines thrice before coming to a stop at its initial position.
# How to use arduino mega 2560:

arduino Mega 2560 is a development electronic board based on the Atmega2560 microcontroller.

This board is a good match for projects that require more GPIO pins and memory space because it carries 16 analog pins and 54 digital I/O pins out of which 15 pins are used for PWM output.

The board comes with a DC power jack to power up this unit and you can also turn on the board using VIN pin on the board. The unit also supports a USB interface where a USB cable is used to connect the board with the computer.
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
