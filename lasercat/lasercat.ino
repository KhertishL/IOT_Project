#include <Servo.h>

Servo myservo;
Servo myservo2;
Servo myservo3;


int servoPinLaserA = 5;
int servoPinLaserB = 9;
int servoPinFoodC = 6;

int IRsensorPin = 11;

int LaserPin = 4;

long randomNumber1;
long randomNumber2;



//Turning servo automatically with laser
// void automatic_laser(){
//   digitalWrite(LaserPin, HIGH);
  
//   for(int pos = 0; pos <= 180; pos +=1)
//   {
//     myservo.write(pos);
//     myservo2.write(pos);
//     delay(15);
//   }
  
//     for(int pos = 0; pos >= 180; pos -=1)
//   {
//     myservo.write(pos);
//     myservo2.write(pos);
//     delay(15);
//   }
// }

//Turning servo in random position 
void random_laser_position(){
  digitalWrite(LaserPin, HIGH);
  randomNumber1 = random(0, 180);
  randomNumber2 = random(0, 180);
  delay(1000);
  myservo.write(randomNumber1);
  myservo2.write(randomNumber2);
}

//Turn off laser and reset servo position
void turn_off_laser(){
  digitalWrite(LaserPin, LOW);
  myservo.write(0);
  myservo2.write(0);
}

void main_laser_function(){
  int IRvalue = digitalRead(IRsensorPin);
      Serial.println(IRvalue);
      
      if(IRvalue == 0){
        random_laser_position();
      }
      else{
        turn_off_laser();
      }
}
  
  
void setup(){
    pinMode(IRsensorPin, INPUT);
    pinMode(LaserPin, OUTPUT);
    myservo.attach(servoPinLaserA);
    myservo2.attach(servoPinLaserB);
    myservo3.attach(servoPinFoodC);
    randomSeed(analogRead(0));
    Serial.begin(9600);
  }
    
void loop(){
  main_laser_function();
}
    

