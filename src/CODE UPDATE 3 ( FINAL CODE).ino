#include "HUSKYLENS.h"
#include <Servo.h>
#include "Wire.h"
#include <MPU6050_light.h>
#include <Pixy2.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//#define RXp2 17
//#define TXp2 16

int bnm = 140;
int fir = 4;
int em = 255;

Pixy2 pixy;  // instantiate a Pixy object
int ddd2 = 50;

boolean r1 = 1;
boolean g1 = 0;

boolean r2 = 0;
boolean g2 = 1;

boolean r3 = 1;
boolean g3 = 0;

boolean r4 = 0;
boolean g4 = 1;

int min = 70;  //cm
int max = 70;  //cm100

int wg = 18;  // hard 60.  // easy 45
int wr = 18;  //didtance between roobot and wall after line when red cube


boolean z1 = 1;

int emam = 0;

//int ledred = 53;
//int ledgreen = A8;

int sigRed = 1;    // signature 1 is red objects
int siggreen = 2;  //signature 2 is blue

int mpx = 0;
int angel = 0;

MPU6050 mpu(Wire);
unsigned long timer = 0;

int angelleft = 90;
int angelright = -90;

int az = 70;  //distance betwwen front sensor and wall before turn

int l = 250;    //distance after see the line
int s = 100;    // finish distance
int dist = 18;  // distance between robot and wall


int newl = 0;
int newr = 0;

Servo myservo;       // create servo object to control a servo
Servo myservopixy1;  // create servo object to control a servo
Servo myservopixy2;  // create servo object to control a servo

// variable for the distance measurement
//Ultrasonic ultrasonicl(A0);
//long distancel;

const int trigPin = 12;
const int echoPin = 13;
long duration;
int distancer;

//Ultrasonic ultrasonicf(A2);
//long distancef;

const int trigPinf = 10;
const int echoPinf = 11;
long durationf;
int distancef;

const int trigPinl = A4;
const int echoPinl = A5;
long durationl;
int distancel;


const int trigPinll = 14;
const int echoPinll = 15;
long durationll;
int distancell;

const int trigPinrr = 16;
const int echoPinrr = 17;
long durationrr;
int distancerr;

boolean on8 = 0;
boolean onn = 0;

boolean onnz = 0;
boolean on8z = 0;
boolean on82 = 0;
boolean on2n = 0;
boolean on83 = 0;
boolean on3n = 0;
boolean on84 = 0;
boolean on4n = 0;
boolean onem = 0;

int bcw = A3;
// H BRIDGE
int fm = 2;  // MOVE FORWARD
int bm = 3;  // MOVE BACKWARD
int pwm = 5;


boolean on3 = 1;
int c = 0;
int rc = 0;
int lc = 0;
int lmbu = 0;
int rmbu = 0;

int ff = A7;
int bb = A9;
int ll = A10;
int rr = A11;
int ss = A12;

int rcpin = A13;
int rcvalue;

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 1000;  //the value is a number of milliseconds


HUSKYLENS huskylens;  // START HUSKEY LENS
//HUSKYLENS green line >> SDA; blue line >> SCL
void printResult(HUSKYLENSResult result);  // PRINR RESULT OF HUSKEYLENS

int buz = A1;

int llidar = A14;
void setup() {  // بنحدد المداخل والمخارج للاردوينو

  Wire.begin();
  Serial.begin(115200);
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) {}  // stop everything if could not connect to MPU6050

  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets();  // gyro and accelero
  Serial.println("Done!\n");
  //Serial2.begin(115200);

  pixy.init();  // initialize the pixy
  pixy.setLamp(1, 1);
  lcd.init();  // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("FUTURE ENGINEERS");
  lcd.setCursor(6, 1);
  lcd.print("2023");
  delay(500);

  myservo.attach(6);        // attaches the servo on pin 9 to the servo object
  myservopixy1.attach(7);   // attaches the servo on pin 9 to the servo object
  myservopixy2.attach(A2);  // attaches the servo on pin 9 to the servo object

  myservopixy1.write(97);
  myservopixy2.write(40);

  myservo.write(89);

  pinMode(bcw, INPUT_PULLUP);

  pinMode(ff, INPUT_PULLUP);
  pinMode(bb, INPUT_PULLUP);
  pinMode(ll, INPUT_PULLUP);
  pinMode(rr, INPUT_PULLUP);
  pinMode(ss, INPUT_PULLUP);
  pinMode(rcpin, INPUT);

  pinMode(llidar, INPUT_PULLUP);



  pinMode(fm, OUTPUT);
  pinMode(bm, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(buz, OUTPUT);
  
  pinMode(trigPin, OUTPUT);    // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);     // Sets the echoPin as an Input

  pinMode(trigPinf, OUTPUT);   // Sets the trigPin as an Output
  pinMode(echoPinf, INPUT);    // Sets the echoPin as an Input

  pinMode(trigPinl, OUTPUT);   // Sets the trigPin as an Output
  pinMode(echoPinl, INPUT);    // Sets the echoPin as an Input

  pinMode(trigPinll, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPinll, INPUT);   // Sets the echoPin as an Input

  pinMode(trigPinrr, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPinrr, INPUT);   // Sets the echoPin as an Input

  pinMode(fir, INPUT_PULLUP);

  delay(100);
  Wire.begin();
  while (!huskylens.begin(Wire)) {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }




  delay(500);
  digitalWrite(fm, 1);  //right front
  digitalWrite(bm, 1);

  digitalWrite(buz, 1);
  delay(50);
  digitalWrite(buz, 0);
  delay(300);
  digitalWrite(buz, 1);
  delay(50);
  digitalWrite(buz, 0);
  //digitalWrite(ledred, 0);
  //digitalWrite(ledgreen, 0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PRESS BUTTON TO");
  lcd.setCursor(0, 1);
  lcd.print("START the robot");
  delay(500);

  lcd.clear();
}




void front() {
  rc++;
  lc++;

  myservo.write(89);
  analogWrite(5, em);
  digitalWrite(fm, 1);  //right front
  digitalWrite(bm, 0);
}




void measure() {

  mpu.update();

  digitalWrite(trigPinf, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinf, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinf, LOW);
  durationf = pulseIn(echoPinf, HIGH);
  distancef = durationf * 0.034 / 2;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distancer = duration * 0.034 / 2;

  digitalWrite(trigPinl, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinl, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinl, LOW);
  durationl = pulseIn(echoPinl, HIGH);
  distancel = durationl * 0.034 / 2;

  digitalWrite(trigPinll, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinll, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinll, LOW);
  durationll = pulseIn(echoPinll, HIGH);
  distancell = durationll * 0.034 / 2;  //Serial.print(rmbu);

 digitalWrite(trigPinrr, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinrr, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinrr, LOW);
  durationrr = pulseIn(echoPinrr, HIGH);
  distancerr = durationrr * 0.034 / 2;  //Serial.print(rmbu);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("L=");
  lcd.setCursor(2, 0);
  lcd.print(distancel);

  lcd.setCursor(6, 0);
  lcd.print("F=");
  lcd.setCursor(8, 0);
  lcd.print(distancef);

  lcd.setCursor(11, 0);
  lcd.print("R=");
  lcd.setCursor(13, 0);
  lcd.print(distancer);

  lcd.setCursor(0, 1);
  lcd.print("mbu=");
  lcd.setCursor(4, 1);
  lcd.print(mpu.getAngleZ());

  lcd.setCursor(10, 1);
  lcd.print("A=");
  lcd.setCursor(12, 1);
  lcd.print(angelright);
  // distancel = ultrasonicl.MeasureInCentimeters();
}





void frontdistl(int ddd) {
  measure();
  myservo.write(89);
  stop();

  while (distancel < 150 || distancel > 270 ) {  //digitalRead(llidar) == 0
      measure();

  if(distancef< 25)
  {
        em = 90;
  myservo.write(89);

    back();
    delay(600);
  //stop();

  }
    else{

    em = 110;
    frontlmbu();
    // front();
    }
  }
  em = bnm;

  myservo.write(40);
}

void frontdistr(int ddd) {
  measure();

  myservo.write(89);

  stop();

  while (distancer < 150 || distancel > 300) {
    measure();
    if(distancef< 25)
  {
        em = 90;
  myservo.write(89);

    back();
    delay(600);
  stop();

  }
  else{
    em = 110;
    frontrmbu();
  }}
  myservo.write(140);
  em = bnm;
}

void finish() {

  while (distancef >= 160) {
    measure();
    myservo.write(90);
    analogWrite(5, 140);
    digitalWrite(fm, 1);  //right front
    digitalWrite(bm, 0);
  }
  analogWrite(5, 255);
  digitalWrite(fm, 1);  //right front
  digitalWrite(bm, 1);
  delay(100000);
  c++;
}

void finish2() {

  while (distancef >= 160) {
    measure();

    myservo.write(90);
    analogWrite(5, 140);
    digitalWrite(fm, 1);  //right front
    digitalWrite(bm, 0);
  }
  analogWrite(5, 255);
  digitalWrite(fm, 1);  //right front
  digitalWrite(bm, 1);
  delay(100000);
  c++;
}

void frontem() {
  measure();

  while (distancef > 150) {
    measure();
    frontlmbu();
  }
  analogWrite(5, 255);
  digitalWrite(fm, 1);  //right front
  digitalWrite(bm, 1);
}


/*void frontlmbu2()

{
  mpu.update();
  uint16_t blocks;
  blocks = pixy.ccc.getBlocks();
  if (blocks) {
    for (int i = 0; i < blocks; i++) {
      // pixy.ccc.blocks[i].print();
      Serial.println(pixy.ccc.blocks[i].m_y);
      if (pixy.ccc.blocks[i].m_signature == sigRed && pixy.ccc.blocks[i].m_x >= 90 && pixy.ccc.blocks[i].m_y >= 90) {
        mpx = pixy.ccc.blocks[i].m_x;
        if (pixy.ccc.blocks[i].m_x < 50) {
          mpx = 50;
        }

        if (pixy.ccc.blocks[i].m_x > 300) {
          mpx = 300;
        }

        angel = map(mpx, 50, 300, 90, 210);
        myservo.write(angel);
        analogWrite(5, em);
        digitalWrite(fm, 1);  //right front
        digitalWrite(bm, 0);
        digitalWrite(ledred, HIGH);
        digitalWrite(ledgreen, 0);

        Serial.println("red");
        delay(420);
      }

      else if (pixy.ccc.blocks[i].m_signature == siggreen && pixy.ccc.blocks[i].m_x <= 260 && pixy.ccc.blocks[i].m_y >= 90) {

        digitalWrite(ledgreen, HIGH);
        digitalWrite(ledred, 0);
        mpx = pixy.ccc.blocks[i].m_x;
        if (pixy.ccc.blocks[i].m_x < 0) {
          mpx = 0;
        }

        if (pixy.ccc.blocks[i].m_x > 260) {
          mpx = 260;
        }

        angel = map(mpx, 0, 260, 20, 91);
        myservo.write(angel);
        analogWrite(5, em);
        digitalWrite(fm, 1);  //right front
        digitalWrite(bm, 0);
        Serial.println("green");
        delay(420);
      }
      analogWrite(5, em);
      digitalWrite(fm, 1);  //right front
      digitalWrite(bm, 0);
    }


  } else if (distancef > 5 && mpu.getAngleZ() > lmbu + 1 && distancer >= 8 && distancel >= 20 && !blocks) {  ///////////
    frontlright();

    digitalWrite(ledgreen, 0);
    digitalWrite(ledred, 0);

  } else if (distancef > 5 && mpu.getAngleZ() < lmbu - 1 && distancer >= 8 && distancel >= 20 && !blocks) {
    frontlleft();
    digitalWrite(ledgreen, 0);
    digitalWrite(ledred, 0);
  }




  else if (distancef > 5 && mpu.getAngleZ() > lmbu + 1 && mpu.getAngleZ() < lmbu - 1 && distancer >= 8 && distancel >= 20 && !blocks) {
    front();
    digitalWrite(ledgreen, 0);
    digitalWrite(ledred, 0);
  } else if (distancef > 5 && distancer < 8 && !blocks) {
    fronth2left();

    digitalWrite(ledgreen, 0);
    digitalWrite(ledred, 0);
  } else if (distancef > 5 && distancel < 20 && !blocks) {
    fronth2right();
    digitalWrite(ledgreen, 0);
    digitalWrite(ledred, 0);
  } else if (distancef < 5 && !blocks) {
    back();
    delay(600);
    fronth2left();
    delay(700);
    digitalWrite(ledgreen, 0);
    digitalWrite(ledred, 0);
  }
}


*/
void frontlmbu()

{
  mpu.update();

  if (mpu.getAngleZ() > lmbu + 1 && distancerr >= 20 && distancell >= 20) {
    frontlright();
  }
  if (mpu.getAngleZ() < lmbu - 1 && distancerr >= 20 && distancell >= 20) {

    frontlleft();
  }
  if (mpu.getAngleZ() > lmbu + 1 && mpu.getAngleZ() < lmbu - 1 && distancerr >= 20 && distancell >= 20) {  //&& distancel <= 100 && distancer <= 100

    front();
  }
  if (distancerr < 20) {

    frontlleft();
  }
  if (distancell < 20) {

    frontlright();
  }
}

void frontlmbu2()

{
  // mpu.update();
  if (distancer < 15) {
    frontlleft();
  } else if (distancel < 15) {
    frontlright();
  }
}




void frontrmbu()

{
  mpu.update();

  if (mpu.getAngleZ() > rmbu - 1 && distancell >= 20 && distancerr >= 20) {  //.    -91

    frontlright();
  }

  if (mpu.getAngleZ() < rmbu + 1 && distancell >= 20 && distancerr >= 20) {  //-89

    frontlleft();
  }
  if (mpu.getAngleZ() > rmbu - 1 && mpu.getAngleZ() < rmbu + 1 && distancell >= 20 && distancerr >= 20) {  //. -91.   -89

    front();
  }

  if (distancell < 20) {

    frontlright();
  }
  if (distancerr < 20) {

    frontlleft();
  }
}


void frontrmbu2()

{
  //mpu.update();



  if (distancel < 14) {
    frontlright();
  } else if (distancer < 17) {
    frontlleft();
  }
}






void back() {

  rc++;
  lc++;
  analogWrite(5, em);
  digitalWrite(fm, 0);  //right front
  digitalWrite(bm, 1);
}


void frontlright() {
  rc++;
  lc++;
  myservo.write(105);
  analogWrite(5, em);

  digitalWrite(fm, 1);  //right front
  digitalWrite(bm, 0);
}


void frontmright() {
  rc++;
  lc++;
  myservo.write(120);
  analogWrite(5, em);

  digitalWrite(fm, 1);  //right front
  digitalWrite(bm, 0);
}

void fronthright(int angelright) {

  while (mpu.getAngleZ() > angelright + 35) {
    myservo.write(140);

    mpu.update();
    analogWrite(5, 180);
    digitalWrite(fm, 1);  //right front
    digitalWrite(bm, 0);
  }
  analogWrite(5, 255);
  digitalWrite(fm, 0);  //right front
  digitalWrite(bm, 0);
}

void fronth2right() {
  rc++;
  lc++;
  myservo.write(140);
  analogWrite(5, em);

  digitalWrite(fm, 1);  //right front
  digitalWrite(bm, 0);
}





void frontlleft() {
  rc++;
  lc++;
  myservo.write(75);
  analogWrite(5, em);

  digitalWrite(fm, 1);  //right front
  digitalWrite(bm, 0);
}

void frontmleft() {
  rc++;
  lc++;
  myservo.write(65);
  analogWrite(5, em);

  digitalWrite(fm, 1);  //right front
  digitalWrite(bm, 0);
}

void fronthleft(int angelleft) {
  rc++;
  lc++;
  myservo.write(40);
  while (mpu.getAngleZ() < angelleft - 35) {
    analogWrite(5, 180);

    mpu.update();
    digitalWrite(fm, 1);  //right front
    digitalWrite(bm, 0);
  }
  analogWrite(5, em);
  digitalWrite(fm, 0);  //right front
  digitalWrite(bm, 0);
}



void fronth2left() {
  rc++;
  lc++;
  myservo.write(40);
  analogWrite(5, em);
  digitalWrite(fm, 1);  //right front
  digitalWrite(bm, 0);
}



void stop() {
  rc++;
  lc++;
  back();
  delay(100);
  myservo.write(88);
  analogWrite(5, em);
  digitalWrite(fm, 0);  //right front
  digitalWrite(bm, 0);
}


void wall(int wa) {

  rc++;
  lc++;
  if (distancer > wa - 1 && distancer < wa + 1) {
    front();
    rc = 0;
  }


  if (distancer < wa - 1) {  //
    rc++;
    lc++;
    frontlleft();
    on3 = 1;
  }
  if (distancer > wa + 1 && distancer < wa + 5) {  //
    frontlright();

    rc++;
    lc++;
  }


  if (distancer > wa + 6) {  //
    frontmright();

    rc++;
    lc++;
  }


  if (distancef <= 15) {
    myservo.write(88);

    back();
    delay(60);
    fronth2left();
    delay(900);
    front();
    delay(0);
  }



  if (distancel <= 9 && distancef <= 13) {
    myservo.write(88);

    back();
    delay(600);
    fronth2right();
    delay(900);
    front();
    delay(250);
  }
}










void wall2(int wa) {
  if (distancel > wa - 2 && distancel < wa + 2) {
    front();
    rc = 0;
  }


  if (distancel < wa - 2) {
    frontlright();
    rc++;
    lc++;
    on3 = 1;
  }

  if (distancel > wa + 2 && distancel < wa + 3) {
    frontlleft();
    rc++;
    lc++;
  }

  if (distancel > wa + 5) {  //
    fronth2left();

    rc++;
    lc++;
  }

  if (distancef <= 15) {
    myservo.write(88);

    back();
    delay(800);
    fronth2right();
    delay(1300);
    front();
    delay(0);
  }
  if (distancer <= 9 && distancef <= 13) {
    myservo.write(88);

    back();
    delay(600);
    fronth2left();
    delay(900);
    front();
    delay(250);
  }
}




void loop() {

measure();



  if (digitalRead(bcw) == 0) {

    onem = 1;
  }


  if (onem == 1) {

    if (r1 == 1 && g1 == 0 && z1 == 1) {
      az = min;
      z1 = 0;
    }
    if (r1 == 0 && g1 == 1 && z1 == 1) {
      az = max;
      z1 = 0;
    }

    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if (!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if (!huskylens.available()) {
      Serial.println(F("No block or arrow appears on the screen!"));
      on3 = 1;
      // front();
      //frontlmbu2();
      myservo.write(89);
      digitalWrite(fm, 1);  //right front
      digitalWrite(bm, 0);
      analogWrite(5, 110);
    }

    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      printResult(result);
      if (result.ID >= 1 && result.ID <= 1 && on3 == 1) {

        digitalWrite(buz, 1);
        delay(80);
        digitalWrite(buz, 0);

        frontdistr(az);
        myservo.write(140);

        fronthright(angelright - 19);
        myservo.write(89);
        front();
        delay(350);

        mpu.update();
        rmbu = mpu.getAngleZ() - 7 ;

        angelright = angelright - 90;
        newl = distancel - 10;
        newr = distancer - 10;
        c++;
        onn = 1;
        onnz = 1;
        z1 = 1;
        onem = 0;
        on3 = 0;
      }



      if (result.ID >= 2 && result.ID <= 2 && on3 == 1) {

        digitalWrite(buz, 1);
        delay(80);
        digitalWrite(buz, 0);
        frontdistl(az);

        fronthleft(angelleft + 10);
        myservo.write(89);
        front();
        delay(300);
        //frontem();
        mpu.update();
        lmbu = mpu.getAngleZ() + 7;
        angelleft = angelleft + 90;
        newl = distancel - 10;
        newr = distancer - 10;
        c++;
        on8 = 1;
        on8z = 1;
        z1 = 1;
        onem = 0;
        on3 = 0;
      }
    }
  }





  //orange// //orange////orange////orange////orange////orange////orange////orange//
  if (onn == 1) {
    if (emam == 0) {

      if (r2 == 1 && g2 == 0) {
        az = min;
        orange(wg);
      }
      if (r2 == 0 && g2 == 1) {
        az = max;
        orange(wr);
      }
    }


    if (emam == 1) {
      if (r3 == 1 && g3 == 0) {
        az = min;
        orange(wg);
      }
      if (r3 == 0 && g3 == 1) {
        az = max;
        orange(wr);
      }
    }

    if (emam == 2) {
      if (r4 == 1 && g4 == 0) {
        az = min;
        orange(wg);
      }
      if (r4 == 0 && g4 == 1) {
        az = max;
        orange(wr);
      }
    }

    if (emam == 3) {
      if (r1 == 1 && g1 == 0) {
        az = min;
        orange(wg);
      }
      if (r1 == 0 && g1 == 1) {
        az = max;
        orange(wr);
      }
    }
  }
  //blue////blue////blue////blue////blue////blue////blue////blue////blue////blue////blue////blue////blue//
  if (on8 == 1) {


    if (emam == 0) {

      if (r2 == 1 && g2 == 0) {
        az = min;
        blue(wg);
      }
      if (r2 == 0 && g2 == 1) {
        az = max;
        blue(wr);
      }
    }

    if (emam == 1) {

      if (r3 == 1 && g3 == 0) {
        az = min;
        blue(wg);
      }
      if (r3 == 0 && g3 == 1) {
        az = max;
        blue(wr);
      }
    }
    if (emam == 2) {

      if (r4 == 1 && g4 == 0) {
        az = min;
        blue(wg);
      }
      if (r4 == 0 && g4 == 1) {
        az = max;
        blue(wr);
      }
    }
    if (emam == 3) {

      if (r1 == 1 && g1 == 0) {
        az = min;
        blue(wg);
      }
      if (r1 == 0 && g1 == 1) {
        az = max;
        blue(wr);
      }
    }

    //blue////blue////blue////blue////blue////blue////blue////blue////blue////blue////blue//
  }
}





void printResult(HUSKYLENSResult result) {
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
  } else if (result.command == COMMAND_RETURN_ARROW) {
    Serial.println(String() + F("Arrow:xOrigin=") + result.xOrigin + F(",yOrigin=") + result.yOrigin + F(",xTarget=") + result.xTarget + F(",yTarget=") + result.yTarget + F(",ID=") + result.ID);
  } else {
    Serial.println("Object unknown!");
  }
}







void orange(int wl) {

  measure();
  if (distancef >= 100) {

    on3 = 1;
    //measure();

    //wall2(wg);
    //front();
    frontrmbu();

  }

  else {

    if (c < 11) {
      digitalWrite(buz, 1);
      delay(80);
      digitalWrite(buz, 0);

      frontdistr(az);
      myservo.write(140);

      fronthright(angelright);
      //   stop();
      mpu.update();
      rmbu = mpu.getAngleZ();


      myservo.write(89);
      front();
      delay(400);  //delay(1000);
                   // stop();         //  measure();



       int bmm = 1;
       if (c > 0 && c <= 2 && bmm == 1) {

          angelright = angelright - 90 + 13   ;
          bmm = 0;
        }
        if (c >= 3 && c <= 8 && bmm == 1) {

          angelright = angelright - 90 +18 ;
          bmm = 0;
        }
        if (c >= 9  && c <= 11 && bmm == 1) {

          angelright = angelright - 90 + 22 ;
          bmm = 1;
        }
      //angelright = angelright - 90 + 13;

      c++;
      emam++;

      if (emam == 4) {
        emam = 0;
      }
      on8z = 1;
      on84 = 0;

      on3 = 0;
    }







    else {
      digitalWrite(buz, 1);
      delay(50);
      digitalWrite(buz, 0);
      frontdistr(az);
      // front();
      // delay(100);
      fronthright(angelright);

      myservo.write(89);
      front();
      delay(200);  //delay(1000);
      measure();
      //stop();

      angelright = angelright - 90 + 17;
      rmbu = mpu.getAngleZ() - 15;

      newl = distancel - 5;
      newr = distancer - 5;

      c++;
      emam++;
      if (emam == 4) {
        emam = 0;
      }
      on8z = 1;
      on84 = 0;

      on3 = 0;
    }

    if (c == 12) {
      //fronthright(angelright);

      // front();
      // delay(s );
      delay(100);
      measure();
      finish();
    }

    if (c == 13) {
      analogWrite(5, 255);
      digitalWrite(fm, 1);  //right front
      digitalWrite(bm, 1);
      delay(1000000);
      c++;
    }
  }
}












void blue(int wl) {


  measure();
  if (distancef >= 100) {


    on3 = 1;
    measure();

    //wall2(wg);
    //front();
    frontlmbu();
  }

  else {

    if (c < 11) {

      digitalWrite(buz, 1);
      delay(80);  //delay(1000);
      digitalWrite(buz, 0);

      frontdistl(az);
      fronthleft(angelleft);

   myservo.write(89);
      mpu.update();
      lmbu = mpu.getAngleZ()+4;
      front();
      delay(200);  


   

     // angelleft = angelleft + 90 - 18;


       int bmm = 1;
        if (c > 0 && c <= 4 && bmm == 1) {
          angelleft = angelleft + 90 - 21  ;
          bmm = 0;
        }
        if (c > 4 && c <= 9 && bmm == 1) {
          angelleft = angelleft + 90 -18;
          bmm = 0;
        }
        if (c > 9  && c <= 11 && bmm == 1) {
          angelleft = angelleft + 90 -16;
          bmm = 1;
        }

     //delay(1000);

      c++;
      emam++;
      if (emam == 4) {
        emam = 0;
      }
      on8z = 1;
      on84 = 0;

      on3 = 0;
    }



    else {
      digitalWrite(buz, 1);
      delay(80);
      digitalWrite(buz, 0);
      //front();
      frontdistl(az);
      front();
      //delay(100);
      // delay(l);
      fronthleft(angelleft);

      myservo.write(89);
      front();
      measure();
      delay(250);  //delay(1000);
      measure();
      stop();
      angelleft = angelleft + 90;
      mpu.update();
      lmbu = mpu.getAngleZ();
      delay(10);
      newl = distancel - 5;
      newr = distancer - 5;
      c++;
      emam++;
      if (emam == 4) {
        emam = 0;
      }
      on8z = 1;
      on84 = 0;

      on3 = 0;
    }

    if (c == 12) {
      // front();
      // delay(s );
      delay(100);
      measure();
      finish2();
    }

    if (c == 13) {

      digitalWrite(fm, 0);  //right front
      digitalWrite(bm, 0);
      delay(1000000);
      c++;
    }
  }
}
