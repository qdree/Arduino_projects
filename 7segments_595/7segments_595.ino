/*
Using a 7-segment display with the 74HC595 shift register
*/

int latchPin = 8;// connect to pin 12 on the '595
int clockPin = 12; // connect to pin 11 on the '595
int dataPin = 11; // connect to pin 14 on the '595
// the array contains the binary value to make digits 0-9
// for the number '11'  use code '31' for CC and '224' for CA
//int segment[10] = {63,6,91,79,102,109,125,7,127,111 }; // for common cathode
//int segment[10] = {192,249,164,176,153,146,130,248,128,144 }; // for common anode
//int segment[10] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246};
int numbers[10] = 	{
					0b0000001000000000,
                    0b1001111000000000,
                    0b1101101000000000,
                    0b0000110000000000,
                    0b0001100000000000,
                    0b0100100000000000,
                    0b0100000000000000,
                    0b0001111000000000,
                    0b0000000000000000,
                    0b0000100000000000
					};

void setup()
{
pinMode(latchPin, OUTPUT);
pinMode(clockPin, OUTPUT);
pinMode(dataPin, OUTPUT);
}
void loop()
{

// digitalWrite(latchpin, LOW);
// shiftOut(datapin, clockpin, MSBFIRST, 0); // clears the display
// digitalWrite(latchpin, HIGH);
// delay(1000);

// for (int lus=0; lus<10; lus++)
// // counts from 0 to 9, using the values in the array
// // whose values correspond to the binary outputs 0~9
// // add 128 for digital point
// {
// digitalWrite(latchpin, LOW);
// shiftOut(datapin, clockpin, MSBFIRST, segment[lus]+128);
// digitalWrite(latchpin, HIGH);
// delay(500);
// }

// digitalWrite(latchpin, LOW);
// shiftOut(datapin, clockpin, MSBFIRST, 0); // clear the display
// digitalWrite(latchpin, HIGH);
// delay(1000);

// digitalWrite(latchpin, LOW);
// shiftOut(datapin, clockpin, MSBFIRST, 128); // light the decimal point
// digitalWrite(latchpin, HIGH);
// delay(1000);

  // for (int j = 0; j < 512; j++) 
  // {
  //   //ground latchPin and hold low for as long as you are transmitting
  //   digitalWrite(latchpin, LOW);
  //   shiftOut(datapin, clockpin, MSBFIRST, numbers[j]);   
  //   //return the latch pin high to signal chip that it 
  //   //no longer needs to listen for information
  //   digitalWrite(latchpin, HIGH);
  //   delay(1000);
  // }

  digitalWrite (latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000);
  digitalWrite (latchPin, HIGH);
}
