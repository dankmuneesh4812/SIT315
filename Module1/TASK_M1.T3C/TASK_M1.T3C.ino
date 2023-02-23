const uint8_t DATA_PIN1 = 2; //define DATA pin number for sensor 1
const uint8_t LED_PIN1 = 10; //define LED-1 pin 
const uint8_t DATA_PIN2 = 3; //define DATA pin number for sensor 2
const uint8_t LED_PIN2 = 10; //define LED-2 pin number

uint8_t sensorState1 = LOW; //set the state of data pin to LOW
uint8_t ledState1 = LOW;    //set the state of led pin to LOW
uint8_t sensorState2 = LOW; //set the state of data pin to LOW
uint8_t ledState2 = LOW;    //set the state of data pin to LOW

void setup()
{    
  pinMode(LED_PIN1,OUTPUT); //declares LED Pin as Digital pin10
  pinMode(LED_PIN2,OUTPUT); //declares LED Pin as Digital pin12
  pinMode(DATA_PIN1,INPUT); //declares Data Pin as Digital pin2
  pinMode(DATA_PIN2,INPUT); //declares Data Pin as Digital pin3
    
  attachInterrupt(digitalPinToInterrupt(DATA_PIN1),task1,CHANGE); //attach interrupts to the code 
  attachInterrupt(digitalPinToInterrupt(DATA_PIN2),task2,CHANGE);
  
  Serial.begin(9600);  //begins serial communication
}

void loop()
{
}

void task1()
{
  sensorState1 = digitalRead(2);//read the input value by input digital pin2
  if(sensorState1 == HIGH)
  {
   ledState1 = HIGH;    
   Serial.println("Motion detected !!");
   digitalWrite(10, sensorState1);
  }
  else
  {   
   Serial.println("Motion not detected !!");
   digitalWrite(10, sensorState1);
  }
  
}

void task2()
{
  sensorState2 = digitalRead(3); //read the input value by input digital pin3
  if(sensorState2 == HIGH)
  {
   ledState2 = HIGH;    
   Serial.println("Motion detected !!");
   digitalWrite(12, sensorState2);
  }
  else
  {   
   Serial.println("Motion not detected !!");
   digitalWrite(12, sensorState2);
  }  
}
