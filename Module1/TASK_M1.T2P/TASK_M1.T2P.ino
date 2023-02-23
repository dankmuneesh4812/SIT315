
const uint8_t DATA_PIN = 2; //define button pin number
const uint8_t LED_PIN = 10; //define LED pin number

uint8_t sensorState = LOW; //set the state of data pin to LOW
uint8_t ledState = LOW;//set the state of led pin to LOW

void setup()
{
  pinMode(LED_PIN, OUTPUT); //declares LED Pin as Digital pin10
  pinMode(DATA_PIN,INPUT_PULLUP);    //declares Data Pin as Digital pin10
  attachInterrupt(0, task, CHANGE); //attach interrupts to the code 
  Serial.begin(9600);  //begins serial communication
}

void loop()
{
 //
}

void task()
{
  sensorState = digitalRead(2);
  if(sensorState == HIGH)
  {
   ledState = HIGH;    
   Serial.println("Motion detected !!");
   digitalWrite(10, sensorState);
  }
  else
  {   
   Serial.println("Motion not detected !!");
   digitalWrite(10, sensorState);
  }
  
}
