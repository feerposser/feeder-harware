// HC-SR04 pins
const int trigPin = 13;
const int echoPin = 12;

// led pins
const int greenLed = 11;
const int yellowLed = 10;
const int redLed = 9;

// Feeder dimentions
const float X = 32;
const float Z = 22;
const float maxY = 12;
float foodHeight;

void setup(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  
  Serial.begin(9600);
}

void loop(){
  foodHeight = getFoodCurrentHeight();
  Serial.print("Height: ");
  Serial.println(foodHeight);
  
  float ml = getMl(foodHeight);
  Serial.print("ml: ");
  Serial.println(ml);
  
  float currentPercent = getCurrentPercent(ml);
  Serial.print("Current percent: ");
  Serial.println(currentPercent);
  
  setLed(currentPercent);
  
  Serial.println("----------------------------");
  
  delay(1000);
}

/* 
get the difference between top of the food and
the y dimension
*/
float getFoodCurrentHeight(){
  return maxY - getDistance();
}

/*
Get distance in cm between the top of the feeder 
and the top of the food
*/
float getDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  return pulseIn(echoPin, HIGH) / 58;
}

/*
Get the food inside feeder in ml3
*/
float getMl(float y){
  return X * y * Z;
}

/*
Get the maximum ml enabled by feeder
*/
float getMaxMl(){
  return X * maxY * Z;
}

/*
get the percent food avaliable by feeder
*/
float getCurrentPercent(float currentMl){
  return (100 * currentMl) / getMaxMl();
}

/*
set leds configuration by the current percent
of food avaliable
*/
void setLed(float currentPercent){
  if(currentPercent >= 70){
    blinkLed(greenLed, 200);
  } else if(currentPercent >= 40){
    blinkLed(yellowLed, 500);
  } else {
    blinkLed(redLed, 800);
  }
}

void blinkLed(int pinLed, int time){
  for(int i=0; i<3; i++){
    digitalWrite(pinLed, HIGH);
    delay(time);
    digitalWrite(pinLed, LOW);
    delay(time);
  }
}
