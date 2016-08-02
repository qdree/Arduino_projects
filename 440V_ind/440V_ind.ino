#define V 10 // V - for symbol
#define OFF 11

const int SCLK = 10;  
const int RCLK = 11;     
const int DIO = 12;   
const int switches[6] = { 2, 3, 4, 5, 6, 7 };
const int croc_1 = 14;
const int croc_2 = 15;
const int rele = 16;

const int SUCCESSFUL_RESULT = 440;
const int switches_cnt = 6;

const byte digit[12] = {	0b11000000, // 0
													0b11111001, // 1
													0b10100100, // 2
													0b10110000, // 3
													0b10011001, // 4
													0b10010010, // 5
													0b10000010, // 6
													0b11111000, // 7
													0b10000000, // 8
													0b10010000, // 9
													0b11100011,	// v
													0b11111111	// all segments are turned off
										  	};

const byte chr[4] = {	0b00001000,  
											0b00000100,  
											0b00000010,  
											0b00000001  
										};

int switch_state[switches_cnt] = { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
  
void setup()
{  
  pinMode(RCLK, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(DIO, OUTPUT);  
	for(int pins = 0; pins < switches_cnt; pins++)
		pinMode(switches[pins], INPUT_PULLUP);
	pinMode(rele, OUTPUT);
	pinMode(croc_1, INPUT_PULLUP);
	pinMode(croc_2, INPUT_PULLUP);

	digitalWrite(rele, HIGH);	
	Serial.begin(9600);
}

void loop()
{
	if(digitalRead(croc_1) == LOW && digitalRead(croc_2) == LOW)
	{
		display(calculation());
		check_result(calculation());
	}
	else display_mode(digit[OFF]);
}

void check_result(int res)
{
	if(res == SUCCESSFUL_RESULT) 
	{
		win(res);
	}
}

int calculation()
{
	int result = 0;
  for (int i = 0; i < switches_cnt; i++)
  {
    switch_state[i] = digitalRead(switches[i]);
    if(switch_state[i] == LOW) //automatic switch is on
    {
	    switch (i) //check each automatic switch 
	    {
	    	case 0:
	    		result += 260;
	    		break;
	    	case 1:
	    		result += 50;
	    		break;
	    	case 2:
	    		result += 35;
	    		break;
	    	case 3:
	    		result += 80;
	    		break;
	    	case 4:
	    		result += 220;
	    		break;
	    	case 5:
	    		result += 130;
	    		break;
	    }
	    //Serial.println(result);
		}
	}
return result;	
}

void display(int number) //output off numbers on 7-segment display
{
	int index;
	Serial.println(number);
	if(number <= 0)
	{
		display_mode(digit[0]);
	}
	else
	{
		digitalWrite(RCLK, LOW); // open latch
  	shiftOut(DIO, SCLK, MSBFIRST, digit[V]);  // send byte with symbol V
  	shiftOut(DIO, SCLK, MSBFIRST, chr[3]);   // turn on the 3rd digit
  	digitalWrite(RCLK, HIGH); // close the latch
		for(int i =2; i >= -1; i--)
		{
			index = number % 10;
			number = number / 10;
			digitalWrite(RCLK, LOW); // open latch
    	shiftOut(DIO, SCLK, MSBFIRST, digit[index]);  // send byte with a number
    	shiftOut(DIO, SCLK, MSBFIRST, chr[i]);   // turn on the digit
    	digitalWrite(RCLK, HIGH); // close the latch
		}
		
	}
}

void display_mode(int pattern) //output of character chosen as 'pattern var'
{
  for(byte i = 0; i <= 4; i++)
  { 
    digitalWrite(RCLK, LOW); // open latch
    shiftOut(DIO, SCLK, MSBFIRST, pattern);  // send byte with a element 
    shiftOut(DIO, SCLK, MSBFIRST, chr[i]);   // turn on the digit
    digitalWrite(RCLK, HIGH); // close the latch
  }  
}

void win(int res)
{
	digitalWrite(rele, LOW);	
	while(true)
	{
		display(res);
	}
}
