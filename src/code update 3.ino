#include "HUSKYLENS.h"
#include <Servo.h>
#include "Ultrasonic.h"
#include "Wire.h"
#include <MPU6050_light.h>
#include <Pixy2.h>
boolean z2 = 1;

int ledred = 53;
int ledgreen = A8;
int sigRed = 1;    // signature 1 is red objects
int siggreen = 2;  //signature 2 is blue
int mpx = 0;
int angel = 0;
Pixy2 pixy;  // instantiate a Pixy object
int ddd2 = 50;
MPU6050 mpu(Wire);
unsigned long timer = 0;

int em = 100;
int angelleft = 90;
int angelright = -90;

int az = 50;  //distance betwwen front sensor and wall before turn

int l = 250;    //distance after see the line
int s = 1500;   // finish distance
int dist = 18;  // distance between robot and wall

int newl = 0;
int newr = 0;

Servo myservo;       // create servo object to control a servo
Servo myservo_pixy;  // create servo object to control a servo

// variable for the distance measurement
Ultrasonic ultrasonicl(A0);
long distancel;

const int trigPin = 4;
const int echoPin = 6;
long duration;
int distancer;

Ultrasonic ultrasonicf(A2);
long distancef;





boolean on8 = 0;
boolean onn = 0;
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

HUSKYLENS huskylens;  // START HUSKEY LENS
//HUSKYLENS green line >> SDA; blue line >> SCL
void printResult(HUSKYLENSResult result);  // PRINR RESULT OF HUSKEYLENS

int buz = A1;


void setup() {  // بنحدد المداخل والمخارج للاردوينو
  Serial.begin(115200);
  Wire.begin();

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) {}  // stop everything if could not connect to MPU6050

  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets();  // gyro and accelero
  Serial.println("Done!\n");
  myservo.attach(9);       // attaches the servo on pin 9 to the servo object
  myservo_pixy.attach(7);  // attaches the servo on pin 9 to the servo object

  myservo.write(91);
  myservo_pixy.write(97);

  pinMode(bcw, INPUT_PULLUP);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  pinMode(A8, OUTPUT);
  pinMode(53, OUTPUT);
  delay(100);
  Wire.begin();
  while (!huskylens.begin(Wire)) {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  delay(500);
  digitalWrite(2, 0);  //right front
  digitalWrite(3, 0);

  digitalWrite(buz, 1);
  delay(50);
  digitalWrite(buz, 0);
  delay(300);
  digitalWrite(buz, 1);
  delay(50);
  digitalWrite(buz, 0);
  pixy.init();  // initialize the pixy
  digitalWrite(ledred, 0);
  digitalWrite(ledgreen, 0);
  pixy.setLamp(1, 1);
}



void front_red() {
  rc++;
  lc++;
  while (distancel > 20) {
    myservo.write(91);
    analogWrite(5, em);
    digitalWrite(2, 1);  //right front
    digitalWrite(3, 0);
  }
}
void front_green() {
  rc++;
  lc++;
  while (distancer > 20) {
    myservo.write(91);
    analogWrite(5, em);
    digitalWrite(2, 1);  //right front
    digitalWrite(3, 0);
  }
}



void front() {
  rc++;
  lc++;

  myservo.write(91);
  analogWrite(5, em);
  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}










void frontdist(int ddd) {

  stop();
  delay(1000);
  ////////////////
  uint16_t blocks;
  blocks = pixy.ccc.getBlocks();
  if (blocks) {
    for (int i = 0; i < blocks; i++) {
      // pixy.ccc.blocks[i].print();
      Serial.println(pixy.ccc.blocks[i].m_y);
      if (pixy.ccc.blocks[i].m_signature == sigRed) {

        digitalWrite(ledred, HIGH);
        digitalWrite(ledgreen, 0);
        ddd2 = 30;
        digitalWrite(buz, 1);
        delay(50);
        digitalWrite(buz, 0);
        delay(300);
        digitalWrite(buz, 1);
        delay(50);
        digitalWrite(buz, 0);
      } else if (pixy.ccc.blocks[i].m_signature == siggreen) {

        digitalWrite(ledgreen, HIGH);
        digitalWrite(ledred, 0);
        ddd2 = 150;
        digitalWrite(buz, 1);
        delay(50);
        digitalWrite(buz, 0);
      }
    }

    if (ddd2 < 5) {
      ddd2 = 50;
    }

    while (distancef > ddd2) {
      mpu.update();
      distancef = ultrasonicf.MeasureInCentimeters();

      myservo.write(90);
      analogWrite(5, em);
      digitalWrite(2, 1);  //right front
      digitalWrite(3, 0);
    }

    digitalWrite(2, 0);  //right front
    digitalWrite(3, 0);
    ddd2 = 50;
  }

  myservo_pixy.write(97);
  delay(100);
  /////////////////////////
}

void frontlmbu2()

{
  mpu.update();
  uint16_t blocks;
  blocks = pixy.ccc.getBlocks();
  if (blocks) {
    for (int i = 0; i < blocks; i++) {
      // pixy.ccc.blocks[i].print();
      Serial.println(pixy.ccc.blocks[i].m_y);
      if (pixy.ccc.blocks[i].m_signature == sigRed && pixy.ccc.blocks[i].m_x >= 90 && pixy.ccc.blocks[i].m_y >= 100) {
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
        digitalWrite(2, 1);  //right front
        digitalWrite(3, 0);
        digitalWrite(ledred, HIGH);
        digitalWrite(ledgreen, 0);

        Serial.println("red");
        delay(420);
      }

      else if (pixy.ccc.blocks[i].m_signature == siggreen && pixy.ccc.blocks[i].m_x <= 260 && pixy.ccc.blocks[i].m_y >= 100) {

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
        digitalWrite(2, 1);  //right front
        digitalWrite(3, 0);
        Serial.println("green");
        delay(420);
      }
      analogWrite(5, em);
      digitalWrite(2, 1);  //right front
      digitalWrite(3, 0);
    }


  } else if (distancef > 5 && mpu.getAngleZ() > lmbu + 1 && distancer >= 20 && distancel >= 20 && !blocks) {  ///////////
    frontlright();

    digitalWrite(ledgreen, 0);
    digitalWrite(ledred, 0);

  } else if (distancef > 5 && mpu.getAngleZ() < lmbu - 1 && distancer >= 20 && distancel >= 20 && !blocks) {
    frontlleft();
    digitalWrite(ledgreen, 0);
    digitalWrite(ledred, 0);
  }




  else if (distancef > 5 && mpu.getAngleZ() > lmbu + 1 && mpu.getAngleZ() < lmbu - 1 && distancer >= 20 && distancel >= 20 && !blocks) {
    front();
    digitalWrite(ledgreen, 0);
    digitalWrite(ledred, 0);
  } else if (distancef > 5 && distancer < 20 && !blocks) {
    frontmleft();

    digitalWrite(ledgreen, 0);
    digitalWrite(ledred, 0);
  } else if (distancef > 5 && distancel < 30 && !blocks) {
    frontmright();
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




void frontlmbu()

{
  mpu.update();

  if (mpu.getAngleZ() > lmbu + 1 && distancer >= 20) {
    frontlright();
  } else if (mpu.getAngleZ() < lmbu - 1 && distancer >= 20) {
    frontlleft();
  } else if (mpu.getAngleZ() > lmbu + 1 && mpu.getAngleZ() < lmbu - 1 && distancer >= 20) {
    front();
  } else if (distancer < 20) {
    frontlleft();
  }
}

void frontrmbu()

{
  mpu.update();

  if (mpu.getAngleZ() > rmbu - 1 && distancel >= 20) {  //.    -91
    frontlright();
    Serial.println("right");
  }

  else if (mpu.getAngleZ() < rmbu + 1 && distancel >= 20) {  //-89
    frontlleft();
    Serial.println("left");


  } else if (mpu.getAngleZ() > rmbu - 1 && mpu.getAngleZ() < rmbu + 1 && distancel >= 20) {  //. -91.   -89
    front();
    Serial.println("front");
  }

  else if (distancel < 20) {
    frontlright();
  }
}






void back() {

  rc++;
  lc++;
  myservo.write(91);

  analogWrite(5, em);
  digitalWrite(2, 0);  //right front
  digitalWrite(3, 1);
}


void frontlright() {
  rc++;
  lc++;
  myservo.write(105);
  analogWrite(5, em);

  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}


void frontmright() {
  rc++;
  lc++;
  myservo.write(120);
  analogWrite(5, em);

  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}

void fronthright(int angelright) {

  while (mpu.getAngleZ() > angelright + 27) {
    mpu.update();
    myservo.write(140);
    analogWrite(5, em);
    digitalWrite(2, 1);  //right front
    digitalWrite(3, 0);
  }
  analogWrite(5, 255);
  digitalWrite(2, 0);  //right front
  digitalWrite(3, 0);
}

void fronth2right() {
  rc++;
  lc++;
  myservo.write(150);
  analogWrite(5, em);

  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}





void frontlleft() {
  rc++;
  lc++;
  myservo.write(75);
  analogWrite(5, em);

  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}

void frontmleft() {
  rc++;
  lc++;
  myservo.write(65);
  analogWrite(5, em);

  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}

void fronthleft(int angelleft) {
  rc++;
  lc++;
  myservo.write(40);
  while (mpu.getAngleZ() < angelleft - 25) {
    mpu.update();

    analogWrite(5, em);
    digitalWrite(2, 1);  //right front
    digitalWrite(3, 0);
  }
  analogWrite(5, em);
  digitalWrite(2, 0);  //right front
  digitalWrite(3, 0);
}



void fronth2left() {
  rc++;
  lc++;
  myservo.write(40);
  analogWrite(5, em);
  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}



void stop() {
  rc++;
  lc++;
  back();
  delay(100);
  myservo.write(88);
  analogWrite(5, em);
  digitalWrite(2, 0);  //right front
  digitalWrite(3, 0);
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
  if (distancer > wa + 1) {  //
    frontlright();

    rc++;
    lc++;
  }


  if (distancef <= 15) {
    myservo.write(88);

    back();
    delay(800);
    fronth2left();
    delay(1300);
    front();
    delay(0);
  }


  /*
  if (distancel <= 9 && distancef <= 13) {
    myservo.write(88);

    back();
    delay(750);
    fronth2right();
    delay(1000);
    front();
    delay(250);
  }*/
}










void wall2(int wa) {
  if (distancel > wa - 1 && distancel < wa + 1) {
    front();
    rc = 0;
  }


  if (distancel < wa - 2) {
    frontlright();
    rc++;
    lc++;
    on3 = 1;
  }

  if (distancel > wa + 2) {
    frontlleft();
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
}




void loop() {

delay(20);
  mpu.update();





  // dont poll thge pixy too fast










  if ((millis() - timer) > 10) {  // print data every 10ms
    Serial.print("X : ");
    Serial.print(mpu.getAngleX());
    Serial.print("\tY : ");
    Serial.print(mpu.getAngleY());
    Serial.print("\tZ : ");
    Serial.println(mpu.getAngleZ());
    timer = millis();
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distancer = duration * 0.034 / 2;

  distancel = ultrasonicl.MeasureInCentimeters();
  distancef = ultrasonicf.MeasureInCentimeters();
  //Serial.print(rmbu);
  //Serial.print("and");

  Serial.println(distancel);




  if (digitalRead(bcw) == 0) {
    onem = 1;
  }


  if (onem == 1) {



    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if (!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if (!huskylens.available()) {
      Serial.println(F("No block or arrow appears on the screen!"));
      on3 = 1;
      front();
      //frontlmbu2();
    }

    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      printResult(result);
      if (result.ID >= 1 && result.ID <= 1 && on3 == 1) {

        digitalWrite(buz, 1);
        delay(50);
        digitalWrite(buz, 0);
        frontdist(az);
        fronthright(angelright - 7);
        myservo.write(90);
        front();
        delay(260);

        mpu.update();
        rmbu = mpu.getAngleZ();

        angelright = angelright - 90 + 7;
        newl = distancel - 10;
        newr = distancer - 10;
        c++;
        onn = 1;
        onem = 0;
        on3 = 0;
      }



      if (result.ID >= 2 && result.ID <= 2 && on3 == 1) {

        digitalWrite(buz, 1);
        delay(50);
        digitalWrite(buz, 0);
        myservo_pixy.write(160);
        frontdist(az);

        myservo_pixy.write(97);

        fronthleft(angelleft);



        myservo.write(90);
        front();
        delay(400);
        mpu.update();
        lmbu = mpu.getAngleZ();
        angelleft = angelleft + 90;
        newl = distancel - 10;
        newr = distancer - 10;
        c++;
        on8 = 1;
        onem = 0;
        on3 = 0;
      }
    }
  }









  if (onn == 1) {

    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if (!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if (!huskylens.available()) {
      Serial.println(F("No block or arrow appears on the screen!"));
      on3 = 1;

      // wall2(newl);
      //front();
      frontrmbu();

    }

    else {
      Serial.println(F("###########"));
      while (huskylens.available()) {
        HUSKYLENSResult result = huskylens.read();
        printResult(result);


        if (result.ID >= 1 && result.ID <= 1 && on3 == 1) {

          digitalWrite(buz, 1);
          delay(50);
          digitalWrite(buz, 0);
          frontdist(az);
          fronthright(angelright);
          myservo.write(89);
          front();
          delay(100);
          angelright = angelright - 90 + 10;

          mpu.update();
          rmbu = mpu.getAngleZ() - 5;

          newl = distancel - 5;
          newr = distancer - 5;

          c++;
          on3 = 0;
        }
        if (c == 12) {
          //fronthright(angelright);
          fronth2right();

          delay(150);
          front();
          delay(s);
          c++;
        }

        if (c == 13) {
          digitalWrite(2, 0);  //right front
          digitalWrite(3, 0);
          delay(1000000);
          c++;
        }
      }
    }
  }


















  if (on8 == 1) {

    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if (!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if (!huskylens.available()) {
      Serial.println(F("No block or arrow appears on the screen!"));
      on3 = 1;

      //wall(30);
      //front();
      //frontlmbu();
      frontlmbu2();
    }

    else {

      Serial.println(F("###########"));
      while (huskylens.available()) {
        delay(10);
        HUSKYLENSResult result = huskylens.read();
        printResult(result);

        if (result.ID >= 2 && result.ID <= 2 && on3 == 1) {

          digitalWrite(buz, 1);
          delay(50);
          digitalWrite(buz, 0);
          myservo_pixy.write(160);

          frontdist(az);
          fronthleft(angelleft);



          myservo.write(89);
          front();
          delay(400);
          angelleft = angelleft + 90 - 12;
          mpu.update();
          lmbu = mpu.getAngleZ() + 5;
          newl = distancel - 5;
          newr = distancer - 5;
          c++;
          z2 = 1;
          on3 = 0;
        }

        if (c == 12) {
          front();
          delay(s);


          c++;
        }

        if (c == 13) {

          digitalWrite(2, 0);  //right front
          digitalWrite(3, 0);
          delay(1000000);
          c++;
        }
      }
    }
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