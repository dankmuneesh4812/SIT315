
void setup()
{
  pinMode(10, OUTPUT); //declares LED Pin as Digital pin10
  pinMode(2,INPUT);    //declares Data Pin as Digital pin10
  Serial.begin(9600);  //begins serial communication
}

void loop()
{
  if(digitalRead(2))
  {
    digitalWrite(10, HIGH); //led will glow
    Serial.println("Motion detected!");  //prints the message     
  }
  else
  {
    digitalWrite(10, LOW); //led will not glow
    Serial.println("Motion not detected!");       
  }
  delay(1000);
}
