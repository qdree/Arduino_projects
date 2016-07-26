#define RELE 7
#define HALL 2

int timer_counter = 0;
int output_counter = 0;

boolean cought = false;

void setup() 
{
  Serial.begin(9600);
  pinMode(RELE, OUTPUT);
  pinMode(HALL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(HALL),timer,FALLING);
}

void loop() 
{
  if (timer_counter > 0)
  {
    digitalWrite(RELE, LOW);
    timer_counter--;
    Serial.print(timer_counter);
    Serial.println(" sec");
  }
  else 
    digitalWrite(RELE, HIGH);

  delay(1000);
}



void timer()
{
  output_counter++;

  timer_counter += 3;

  if(timer_counter > 6)
    timer_counter = 6;
  
  Serial.print(output_counter);
  Serial.println(" times magnet found");

}


