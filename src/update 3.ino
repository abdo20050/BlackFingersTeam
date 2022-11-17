#include "HUSKYLENS.h"
#include <Servo.h>
#include "Ultrasonic.h"


byte servoPin = 9; // signal pin for the ESC.

int a = 1585;  // robot speed
int q = 1585;
int n = 1585;  // robot speed whem tuurn after accident
int l = 50;   //distance after see the line

int s = 300;  // finish distance

int dist = 40;  // distance between robot and wall

Servo pwm;

Servo myservo;  // create servo object to control a servo
int angel = 0;
// variable for the distance measurement
Ultrasonic ultrasonicl(A0);
    long distancel;

Ultrasonic ultrasonicr(A1);
    long distancer;

Ultrasonic ultrasonicf(A2);
    long distancef;



boolean on8 = 0;
boolean onn = 0;
boolean onem = 0;

int bcw = A3;

int fm = 2;
int bm = 3;



boolean on3 = 1;
int c = 0;
int rc = 0;
int lc = 0;
HUSKYLENS huskylens;
//HUSKYLENS green line >> SDA; blue line >> SCL
void printResult(HUSKYLENSResult result);




void setup() {
  Serial.begin(115200);


  pinMode(2, OUTPUT);  // Sets the trigPin as an OUTPUT
  pinMode(3, OUTPUT);  // Sets the trigPin as an OUTPUT

  pinMode(bcw, INPUT_PULLUP);

pwm.attach(servoPin,1000,2000);
pwm.writeMicroseconds(1500); // send "stop" signal to ESC. Also necessary to arm the ESC.



  delay(100);


  myservo.attach(5);  // attaches the servo on pin 9 to the servo object

  //myservo.write(96);              // mid
  // myservo.write(140);              // right
  //myservo.write(65);              // left

  Wire.begin();
  while (!huskylens.begin(Wire)) {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  myservo.write(90);
  //fronthleft();
  delay(500);
  digitalWrite(2, 0);  //right front
  digitalWrite(3, 0);

}

void front() {
  rc++;
  lc++;
  myservo.write(90);
  pwm.writeMicroseconds(a); // 1500 t0 2000 
  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);

}


void back() {
  rc++;
  lc++;
  pwm.writeMicroseconds(a); // 1500 t0 2000 
  digitalWrite(2, 0);  //right front
  digitalWrite(3, 1);
}

void frontlleft() {
  rc++;
  lc++;
  myservo.write(109);
   pwm.writeMicroseconds(a); // 1500 t0 2000 
  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}

void frontmleft() {
  rc++;
  lc++;
  myservo.write(120);
 pwm.writeMicroseconds(a); // 1500 t0 2000 
  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}

void fronthleft() {
  rc++;
  lc++;
  myservo.write(140);
pwm.writeMicroseconds(a); // 1500 t0 2000 
  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}

void fronth2left() {
  rc++;
  lc++;
  myservo.write(140);
pwm.writeMicroseconds(a); // 1500 t0 2000 
  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}





void frontlright() {
  int b = a;
  rc++;
  lc++;
  myservo.write(77);
 pwm.writeMicroseconds(a); // 1500 t0 2000 
  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}

void frontmright() {
  int b = a;
  rc++;
  lc++;
  myservo.write(72);
  pwm.writeMicroseconds(a); // 1500 t0 2000 
  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}

void fronthright() {
  int b = a;
  rc++;
  lc++;
  myservo.write(60);
pwm.writeMicroseconds(a); // 1500 t0 2000 
  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}

void fronth2right() {
  rc++;
  lc++;
  myservo.write(60);
  pwm.writeMicroseconds(a); // 1500 t0 2000 
  digitalWrite(2, 1);  //right front
  digitalWrite(3, 0);
}



void stop() {
  int b = a;
  rc++;
  lc++;
  back();
  delay(100);
  myservo.write(98);
pwm.writeMicroseconds(a); // 1500 t0 2000 
  digitalWrite(2, 0);  //right front
  digitalWrite(3, 0);
}


void wall() {

  rc++;
  lc++;
  if (distancer >= dist - 3 && distancer <= dist + 3 && distancef >= 13) {
    front();
    rc = 0;
  }


  if (distancer <= dist - 4 && lc <= 25 ) { //
    rc++;
    lc++;
    frontmleft();
    on3 = 1;
    rc = 0;
  } 
  else if (lc >= 26) {
    fronthright();
    delay(35);

    lc = 0;
  }
  if (distancer >= dist + 4 && rc <= 120 ) {//
    frontmright();
        lc = 0;

    rc++;
    lc++;
  }

  if (rc >= 121) {
    fronthleft();
    delay(10);
    rc = 0;
  }
  if (distancef <= 18 && distancel >= 9) {
    back();
    delay(800);
    fronthleft();
    delay(1300);
    front();
    delay(0);
  }

  if (distancel <= 8 && distancef <= 18) {
    back();
    delay(600);
    fronthright();
    delay(1000);
    front();
    delay(250);
  }


  if (c == 12) {
    fronthleft();
    delay(200);
    front();
    delay(500);


    c++;
  }

  if (c == 13) {

    digitalWrite(2, 1);  //right front
    digitalWrite(3, 0);
    analogWrite(4, 0);

    digitalWrite(5, 0);  //left front
    digitalWrite(6, 1);
    analogWrite(7, 0);
    delay(1000000);
    c++;
  }
  if (distancef <= 130 && distancef > 90) {
    a = q;
  } else {
    a = q;
  }
}










void wall2() {
  if (distancel >= dist - 3 && distancel <= dist + 3 && distancef >= 13) {
    front();
    rc = 0;
  }


  if (distancel <= dist - 4 && lc <= 80) {
    frontlright();
    rc++;
    lc++;
    on3 = 1;

  } else if (lc >= 81) {
    fronthleft();
    delay(10);
    lc = 0;
  }

  if (distancel >= dist + 4 && rc <= 80) {
    frontlleft();
    rc++;
    lc++;
  }

  if (rc >= 81) {
    frontlright();
    delay(10);
    rc = 0;
  }

  if (distancef <= 12 && distancel <= distancer) {
    myservo.write(98);

    back();
    delay(800);
    fronth2right();
    delay(1400);
    front();
    delay(0);
  }

  if (distancef <= 12 && distancer <= distancel) {
    myservo.write(98);

    back();
    delay(800);
    fronth2right();
    delay(1400);
    front();
    delay(0);
  }



  if (c == 12) {
    fronthright();
    delay(200);
    front();
    delay(500);


    c++;
  }

  if (c == 13) {

    digitalWrite(2, 0);  //right front
    digitalWrite(3, 0);
   
    delay(1000000);
    c++;
  }
  if (distancef <= 130 && distancef > 90) {
    a = q;
  } else {
    a = q;
  }
}




void loop() {
  rc++;
  lc++;



  
  distancer = ultrasonicr.MeasureInCentimeters();


  
  distancel = ultrasonicl.MeasureInCentimeters();

  
  distancef = ultrasonicf.MeasureInCentimeters();

  Serial.println(distancef);

  // if (digitalRead(bccw) == 0) {
  //  on8 = 1;
  //}

  if (digitalRead(bcw) == 0) {
    onem = 1;
  }

  if (onem == 1) {

    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if (!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if (!huskylens.available()) {
      Serial.println(F("No block or arrow appears on the screen!"));
      // myservo.write(98);
      on3 = 1;
    front();


    }

    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      printResult(result);
      if (result.ID >= 1 && result.ID <= 12 && on3 == 1) {
        a = q;

        digitalWrite(10, 1);
        delay(50);
        digitalWrite(10, 0);

        front();
        delay(l - 50);

        fronthright();
        delay(600);
        myservo.write(98);
        front();
        delay(200);


        //delay(1000);

        c++;
        onn = 1;
        onem = 0;
        on3 = 0;
      }



      if (result.ID >= 13 && result.ID <= 24 && on3 == 1) {
        a = q;
 // myservo.write(160);

//pwm.writeMicroseconds(3000 ); // 1500 t0 2000 
  //digitalWrite(2, 1);  //right front
  //digitalWrite(3, 0);
 // delay(250);
        digitalWrite(10, 1);
        delay(50);
        digitalWrite(10, 0);

        front();

        delay(l - 50);

       fronthleft();
        delay(450);
        
        myservo.write(90);
        front();
        delay(200);


        //delay(1000);

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
      // myservo.write(98);
      on3 = 1;

      wall2();




    }

    else {
      Serial.println(F("###########"));
      while (huskylens.available()) {
        HUSKYLENSResult result = huskylens.read();
        printResult(result);





















        if (result.ID >= 1 && result.ID <= 12 && on3 == 1) {
          a = q;

          digitalWrite(10, 1);
          delay(50);
          digitalWrite(10, 0);

          front();
          delay(l - 50);

          fronthright();
          delay(800);
          myservo.write(98);
          front();
          delay(200);


          //delay(1000);

          c++;
          on3 = 0;
        }





        if (c == 12) {

          fronthright();
          delay(150);
          front();
          delay(s);


          c++;
        }

        if (c == 13) {

          digitalWrite(2, 1);  //right front
          digitalWrite(3, 0);
          analogWrite(4, 0);

          digitalWrite(5, 0);  //left front
          digitalWrite(6, 1);
          analogWrite(7, 0);
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
      // myservo.write(98);
      on3 = 1;

      wall();

    }

    else {
      Serial.println(F("###########"));
      while (huskylens.available()) {

        delay(10);
        HUSKYLENSResult result = huskylens.read();
        printResult(result);









        if (result.ID >= 13 && result.ID <= 25 && on3 == 1) {
          a = q;

          digitalWrite(10, 1);
          delay(50);
          digitalWrite(10, 0);

          front();
          delay(l);

          fronthleft();
          delay(620);
          myservo.write(90);
          front();
          delay(200);


          //delay(1000);

          c++;
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