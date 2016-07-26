//Automatic_sw.ino

int led = 13;
int a_sw = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(a_sw, INPUT_PULLUP);
}

void loop() 
{
  // put your main code here, to run repeatedly:
    if(digitalRead(a_sw) == LOW)
    	digitalWrite(led, HIGH);
    else
		digitalWrite(led, LOW);
    	  // turn the LED on (HIGH is the voltage level)
//     delay(100);               // wait for a second
//     digitalWrite(led, LOW);   // turn the LED off by making the voltage LOW
//     delay(100);               // wait for a second
}
