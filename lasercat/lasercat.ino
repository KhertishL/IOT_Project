#include <Servo.h>

Servo myservo;
Servo myservo2;
Servo myservo3;


int servoPinLaserA = 5;
int servoPinLaserB = 9;
int servoPinFoodC = 6;

int IRsensorPin = 11;

int LaserPin = 4;

long randomNumber1; //variable for storing random angle of servo
long randomNumber2;

bool state = false;

unsigned long time;
unsigned long period = 10000; 

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
  for(int i = 0; i < 10; i++){
    digitalWrite(LaserPin, HIGH);
    randomNumber1 = random(0, 180);
    randomNumber2 = random(0, 180);
    delay(1000);
    myservo.write(randomNumber1);
    myservo2.write(randomNumber2);

    if(i == 9){
      food_motor();
    }
  }
}

//Turn off laser and reset servo position
void turn_off_laser(){
  digitalWrite(LaserPin, LOW);
  myservo.write(0);
  myservo2.write(0);
}

//Main function for laser positioning with servo
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

//Function to control food dispenser motor
void food_motor(){
  for (int pos = 0; pos <= 60; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (int pos = 60; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}


  
  
void setup(){
    pinMode(IRsensorPin, INPUT); 
    pinMode(LaserPin, OUTPUT);
    myservo.attach(servoPinLaserA);
    myservo2.attach(servoPinLaserB);
    myservo3.attach(servoPinFoodC);
    randomSeed(analogRead(0)); //random number generator on analog pin A0
    Serial.begin(9600);
  }
    
void loop(){
  main_laser_function();
  Serial.println(time);
  
 
}
   
