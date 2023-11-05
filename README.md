
# Hi there. we are black fingers team
Here is the Youtube video link for the Robot → [https://youtu.be/Kr0BLmSGszo](https://youtu.be/Sl1KqG20jyE?si=mnz6BM_O7H6PnRAk)
# let us explain to you the strategy for our robot in the game play:
When the game starts, the robot uses the balance sensor (Gyro) to reset the balance (Reset) to maintain the robot’s balance while walking forward and turning right or left.  Using the three (ultrasonic) sensors installed in the front of the robot.
These sensors prevent the robot from colliding with the right and left walls or columns.
When the ultrasonic sensors read that the robot is moving away from the wall, the sensors send a command to the Arduino to approach the wall, or vice versa, in the event of getting too close, the sensors send a command to the Arduino to move away a sufficient distance from the wall.  In short, the three ultrasonic sensors on the front of the robot should keep the robot stable and keep it far enough away from walls.

When the robot sees the blue line, huskylens will send a command to the Arduino to go forward and then turn 90 degrees to the left and then go forward and complete the loop by repeating this way and at the same time that huskylens sees the blue line the pixy installed on the servo will turn left 90 degrees to see the color  The column on the left side.

 If pixy encounters a column (green), it will send a command to the Arduino to turn directly to the left side to complete the path on the (left) side of the green column. If pixy encounters a column (red), pixy will also send a command to the Arduino to move forward a sufficient distance and then turn. 
 
 Turn left to complete the path on the (right) side of the red column, and this method is repeated continuously. Thus, the robot will complete three rounds, reading all the blue lines three times, then stop where it started
# How to use arduino mega 2560:
We can program the Arduino Mega using the Arduino IDE. We need to install the Arduino IDE software to get started with the process.

 We can also use Arduino Web Editor, which allows us to upload sketches and write the code from our web browser (Google Chrome recommended) to any Arduino Board. It is an online platform.
The USB cable is crucial for the connection between the board and the computer. The green LED will light, which indicates the successful connection between the computer and the board.

The steps to get started with Arduino Mega are listed below:

Open the code or sketch written in the Arduino software.
Select the type of board.
The ATmega2560 microcontroller is used in the Arduino Mega. So, we will select the Processor as ATmega2560.
As we select the board, the processor is automatically selected by default.

For more details on how to use the Arduino, visit the website
https://www.arduino.cc/en/Guide/ArduinoMega2560/

# The program
all of our source codes are in the src directory

# The components of the robot
The robot's components are:
### 1-The Arduino mega 2560:
<img src="https://github.com/BlackFingerTeam/BlackFingersTeam/assets/115355293/1f86272f-cac4-4f5a-8270-d59a7e4507ee" width="200" height="200">


Arduino Mega 2560 is a development electronic board based on the Atmega2560 microcontroller.

This board is a good match for projects that require more GPIO pins and memory space because it carries 16 analog pins and 54 digital I/O pins out of which 15 pins are used for PWM output.

The board comes with a DC power jack to power up this unit and you can also turn on the board using VIN pin on the board. The unit also supports a USB interface where a USB cable is used to connect the board with the computer.
### 2-Huskylens
<img src="https://github.com/BlackFingerTeam/BlackFingersTeam/assets/115355293/9b102649-4147-4e67-b892-f9c447208df1" width="200" height="200">

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

<img src="https://github.com/BlackFingerTeam/BlackFingersTeam/assets/115355293/a71edad8-dc59-48dd-a8d5-0bcfe5dc5174" width="250" height="200">

is a sensor that can measure distance. It emits an ultrasound at 40 000 Hz (40kHz) which travels through the air and if there is an object or obstacle on its path It will bounce back to the module. Considering the travel time and the speed of the sound you can calculate the distance. It makes sure that the robot does not bump into anything around it, So it should keep distance between the robot and anything around it, We actually used three ultra sonics in our robot so it can allow the robot to see any obstacle to it right, front and left.
###4- 
DC Motors, Obviously so the robot can move, We used two motor and we placed them under the robot next to the tires and it rotates in the same direction they go forward together and go back together.
### 5- Servo

<img src="https://github.com/BlackFingerTeam/BlackFingersTeam/assets/115355293/7ccae9d6-95fd-4b17-8b9c-f1bdf5028fc8" width="200" height="200">
<img src="https://github.com/BlackFingerTeam/BlackFingersTeam/assets/115355293/3f4a3449-7941-4453-891b-39c6bac1c16e" width="200" height="200">

is a rotary actuator that allows for precise control of angular position, velocity and acceleration. it controls the robot's movement horizontally.
We used two types of servo: two MG90s work to move the wheels and move the camera up and down, and one MG995 works to move the camera left and right.


### 6- The L298N Motor Driver
<img src="https://github.com/BlackFingerTeam/BlackFingersTeam/assets/115355293/12d1ff83-3559-43fc-9a00-99279ced2230" width="250" height="200">

is a controller that uses an H-Bridge to easily control the direction and speed of up to 2 DC motors. it is the mediator between the Arduino and the motors, So any command from the Arduino the motor drive should delivers it to the motors.
How Motor Driver Module Works:
This module uses two techniques for the control speed and rotation direction of the DC motors. These are H-Bridge – For controlling rotation direction and PWM – For controlling the speed.
### 7- A pixy camera 
<img src="https://github.com/BlackFingerTeam/BlackFingersTeam/assets/115355293/33cb5bc7-e2bc-4943-9d10-cb43eaeb7398" width="200" height="200">

The Pixy camera is a complete vision system with an image sensor and a microprocessor. It includes learning algorithms and detection of colour, line, intersection and small barcode. It includes all the technology necessary for visual recognition.

Technical specifications

Processor: NXP LPC4330, 204 MHz, dual core
Image Sensor: Aptina MT9M114, 1296×976 resolution with integrated image stream processor
Power consumption: 140 mA typical
Power consumption: USB input (5V) or unregulated input (6V to 10V)
Available data: UART serial, SPI, I2C, USB, digital, analog

### 8- Gyro Sensor ( MPU6050)
The MPU6050 IMU has both 3-Axis accelerometer and 3-Axis gyroscope integrated on a single chip.

The gyroscope measures rotational velocity or rate of change of the angular position over time, along the X, Y and Z axis. It uses MEMS technology and the Coriolis Effect for measuring, but for more details on it you can check my particular How MEMS Sensors Work tutorial. The outputs of the gyroscope are in degrees per second, so in order to get the angular position we just need to integrate the angular velocity.
### 9- CNC machine
sing a laser machine to cut acrylic to produce several parts, the most important of which are engine gears ( We will put a pdf for the piece in our profile ).
### 10- RPLIDAR 

RPLIDAR A1 is a low cost 360 degree 2D laser scanner (LIDAR) solution developed by SLAMTEC. The system can perform 360degree scan within 6meter range. The produced 2D point cloud data can be used in mapping, localization and object/environment modeling.
 
RPLIDAR A1’s scanning frequency reached 5.5 hz when sampling 360 points each round. And it can be configured up to 10 hz maximum. 
 
RPLIDAR A1 is basically a laser triangulation measurement system. It can work excellent in all kinds of indoor environment and outdoor environment without sunlight.

### 11- DC MOTOR
DC motor or direct current motor is an electrical machine that transforms electrical energy into mechanical energy by creating a magnetic field that is powered by direct current. When a DC motor is powered, a magnetic field is created in its stator. The field attracts and repels magnets on the rotor; this causes the rotor to 
rotate. To keep the rotor continually rotating, the commutator that is attached to brushes connected to the power source supply current to the motors wire windings.

### 12- 3D PRINTER 
We used AutoDesk Inventor to design the robot and then used a 3D printer to print the parts, in addition to its cover, camera holder, ultrasonic sensor box, and other pieces.

<img src="https://github.com/BlackFingerTeam/BlackFingersTeam/assets/115355293/41f31f25-3ee4-48a8-ba89-fbfb3fcbb8c6" width="300" height="200">

### 13- Batteries
We used 4 batteries that gives us 12 volts in total.

### 14- voltage regulator
voltage regulator is a circuit that creates and maintains a fixed output voltage, irrespective of changes to the input voltage or load conditions. Voltage regulators (VRs) keep the voltages from a power supply within a range that is compatible with the other electrical components. While voltage regulators are most commonly used for DC/DC power conversion, some can perform AC/AC or AC/DC power conversion as well

### 15- the switches
there are two switches in the robot one to turn the robot on and off, and the other one is to let the robot start the game.
