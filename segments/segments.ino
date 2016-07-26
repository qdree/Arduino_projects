/*
********************************************************************
  Name    : shiftOutDisplay, Test code
  Author  : Benjo Charlie
  Date    : 13 Sept, 2013
  Version : 1.0
  Notes   : Shiftbit registers can be a little tricky to setup so I
          : designed this simple Hello World code for doing just that.
          : This example uses a 74HC595 Shift Bit Register in conjunction
          : with a common anode seven segment display.
          : This code sends the following values to a Shift Bit Register: 
          : 1, 2, 4, 8, 16, 32, 64, 128. 
          : Each of the 74HC595 outputs will "switch on" in turn.
********************************************************************

7 Segment (Common Anode) Display Map: (This can be altered to reflect your HW)

    D   E  5V   F   G
 ___|___|___|___|___|____
|                        |
|        F               |
|    E       G           |
|        D               |
|    A       C           |
|        B       H(Dot)  |
|________________________|
    |   |   |   |   |
    A   B  5V   C   H

74HC595 Map:
           _______
   OUT Q1-|1 *  16|-5V
   OUT Q2-|2    15|-OUT Q0
   OUT Q3-|3    14|-ARD PIN 11
   OUT Q4-|4    13|-GND
   OUT Q5-|5    12|-ARD PIN 8 ; 1uF TO GND
   OUT Q6-|6    11|-ARD PIN 12 
   OUT Q7-|7    10|-5V
      GND-|8_____9|-

********************************************************************
*/

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
//Pin connected to DS of 74HC595
int dataPin = 11;

void setup() {

  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600); 
}

void loop() {

// integer to represent the "Q" pin on the Shift Bit Register.
int shiftBitRegPin=0;

  // The following for loop will Shift the "HIGH" value on the Shift Bit Register from Q0-Q7. 
  // This is achieved by sending the values 1,2,4,8,16,32,64,128
  // The Binary equivalent is as follows (Notice the bit movement):
  // 0000 0001, 0000 0010, 0000 0100, 0000 1000, 0001 0000, 0010 0000, 0100 0000, 1000 0000
  // NB. The operator << could be replaced with *2 if that helps with understanding.
  for (int shiftBitRegOut = 1; shiftBitRegOut < 256; shiftBitRegOut = shiftBitRegOut << 1) {
    
    // take the latchPin low so the output 
    // doesn't change while you're sending in bits:
    digitalWrite(latchPin, LOW);

    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, shiftBitRegOut);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);

    // Print out the Shift Bit Register pin with it's corresponding value.
    Serial.print("Q");
    Serial.print(shiftBitRegPin);
    Serial.print(" = ");
    Serial.println(shiftBitRegOut);
    Serial.print("Binary = ");
    Serial.println(shiftBitRegOut, BIN);
    Serial.println("****************");

    // Increment the pin number by 1 but do not exceed 7
    if (shiftBitRegPin>=7) {
      shiftBitRegPin=0;
    } else {
        shiftBitRegPin++;
    }
    delay(4000);
  }
}