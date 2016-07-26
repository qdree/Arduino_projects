

//////////////////// Message to Customize  ///////////////////
#define msgLength 4                                       ///
String msgBody = "SPOON";                            ///
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////




#define delayInChar 3
#define delayBetweenChar 5
#define LED1 9
#define LED2 8
#define LED3 7
#define LED4 6
#define LED5 5
#define LED6 4
#define LED7 3

byte msgCode[(5 * msgLength) + 10];
boolean pintState;
int columnNum = -1;
String charToWrite;
int lastvalue;
int treshold = 30;

void setup() {
  pinMode(A5, INPUT);
  pinMode(A7, INPUT);
  pinMode(A4, INPUT);
  Serial.begin(9600);
  msgBody.toUpperCase();
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(A5);
  //int sensorValue2 = analogRead(A7);
  //int sensorValue3 = analogRead(A4);
  // print out the value you read:
  /*
    Serial.print("1st ");
    Serial.print(sensorValue);
    Serial.println("\t");
    /*
    Serial.print("2nd ");
    Serial.print(sensorValue2);
    Serial.print("\t");
    Serial.print("3rd ");
    Serial.print(sensorValue3);
    Serial.println("\t");
     || (lastvalue-sensorValue)<20)
  */
  if ((lastvalue-sensorValue) > treshold)  {
    Serial.print(lastvalue-sensorValue);
    Serial.println("\t");
    dispov();
  }
  lastvalue = sensorValue;
}
void dispov() {
  //// Convert all text to binary array ////////////////////////
  if ( columnNum == -1 ) // This block needs to be done once//
  { //
    for (int c = 0; c < (msgBody.length()); c++)  {         //
      //Separate the following character                    //
      charToWrite = msgBody.substring(c, c + 1);            //
      //Send the separated characted to addChar function    //
      addChar(charToWrite);                                 //
    }                                                       //
    //Add a little space after each character             //
    addChar(" ");                                           //
    addChar(" ");                                           //
  }                                                         //
  //////////////////////////////////////////////////////////////

  //// Display the binary arrays after all characters are coded //
  for (int c = 0; c < (sizeof(msgCode)); c++)  {              //
    pintState = (msgCode[c] / B1000000) % B10;                //
    digitalWrite(LED1, pintState);                            //
    //
    pintState = (msgCode[c] / B100000) % B10;                 //
    digitalWrite(LED2, pintState);                            //
    //
    pintState = (msgCode[c] / B10000) % B10;                  //
    digitalWrite(LED3, pintState);                            //
    //
    pintState = (msgCode[c] / B1000) % B10;                   //
    digitalWrite(LED4, pintState);                            //
    //
    pintState = (msgCode[c] / B100) % B10;                    //
    digitalWrite(LED5, pintState);                            //
    //
    pintState = (msgCode[c] / B10) % B10;                     //
    digitalWrite(LED6, pintState);                            //
    //
    pintState = msgCode[c] % B10;;                            //
    digitalWrite(LED7, pintState);                            //
    //
    delay(delayInChar);                                       //
    // if the character is finished, take a longer off period //
    if ((c + 1) % 5 == 0 ) {                                  //
      digitalWrite(LED1, LOW);                                //
      digitalWrite(LED2, LOW);                                //
      digitalWrite(LED3, LOW);                                //
      digitalWrite(LED4, LOW);                                //
      digitalWrite(LED5, LOW);                                //
      digitalWrite(LED6, LOW);                                //
      digitalWrite(LED7, LOW);                                //
      delay(delayBetweenChar);                                //
    }                                                         //
  }                                                           //
  //
  ////////////////////////////////////////////////////////////////
}


void addChar(String y) {
  if (y == "1") {
    addColumn(B0010001);
    addColumn(B0100001);
    addColumn(B1111111);
    addColumn(B0000001);
    addColumn(B0000001);
  }
  else if (y == "2") {
    addColumn(B0100001);
    addColumn(B1000011);
    addColumn(B1000101);
    addColumn(B1001001);
    addColumn(B0110001);
  }
  else if (y == "3") {
    addColumn(B0100010);
    addColumn(B1000001);
    addColumn(B1001001);
    addColumn(B1001001);
    addColumn(B0110110);
  }
  else if (y == "4") {
    addColumn(B0001100);
    addColumn(B0010100);
    addColumn(B0100100);
    addColumn(B1111111);
    addColumn(B0000100);
  }
  else if (y == "5") {
    addColumn(B1110010);
    addColumn(B1010001);
    addColumn(B1010001);
    addColumn(B1010001);
    addColumn(B1001110);
  }
  else if (y == "6") {
    addColumn(B0111110);
    addColumn(B1001001);
    addColumn(B1001001);
    addColumn(B1001001);
    addColumn(B0100110);
  }
  else if (y == "7") {
    addColumn(B1000000);
    addColumn(B1000111);
    addColumn(B1001000);
    addColumn(B1010000);
    addColumn(B1100000);
  }
  else if (y == "8") {
    addColumn(B0110110);
    addColumn(B1001001);
    addColumn(B1001001);
    addColumn(B1001001);
    addColumn(B0110110);
  }
  else if (y == "9") {
    addColumn(B0110010);
    addColumn(B1001001);
    addColumn(B1001001);
    addColumn(B1001001);
    addColumn(B0111110);
  }
  else if (y == "0") {
    addColumn(B0111110);
    addColumn(B1000101);
    addColumn(B1001001);
    addColumn(B1010001);
    addColumn(B0111110);
  }
  else if (y == "A") {
    addColumn(B0011111);
    addColumn(B0100100);
    addColumn(B1000100);
    addColumn(B1000100);
    addColumn(B1111111);
  }
  else if (y == "B") {
    addColumn(B1111111);
    addColumn(B1001001);
    addColumn(B1001001);
    addColumn(B1001001);
    addColumn(B0110110);
  }
  else if (y == "C") {
    addColumn(B0111110);
    addColumn(B1000001);
    addColumn(B1000001);
    addColumn(B1000001);
    addColumn(B0100010);
  }
  else if (y == "D") {
    addColumn(B1111111);
    addColumn(B1000001);
    addColumn(B1000001);
    addColumn(B1000001);
    addColumn(B0111110);
  }
  else if (y == "E") {
    addColumn(B1111111);
    addColumn(B1001001);
    addColumn(B1001001);
    addColumn(B1001001);
    addColumn(B1000001);
  }
  else if (y == "F") {
    addColumn(B1111111);
    addColumn(B1001000);
    addColumn(B1001000);
    addColumn(B1001000);
    addColumn(B1000000);
  }
  else if (y == "G") {
    addColumn(B0111110);
    addColumn(B1000001);
    addColumn(B1000001);
    addColumn(B1000101);
    addColumn(B0100110);
  }
  else if (y == "H") {
    addColumn(B1111111);
    addColumn(B0001000);
    addColumn(B0001000);
    addColumn(B0001000);
    addColumn(B1111111);
  }
  else if (y == "I") {
    addColumn(B0000000);
    addColumn(B1000001);
    addColumn(B1111111);
    addColumn(B1000001);
    addColumn(B0000000);
  }
  else if (y == "J") {
    addColumn(B0000000);
    addColumn(B0000010);
    addColumn(B1000001);
    addColumn(B1000001);
    addColumn(B1111110);
  }
  else if (y == "K") {
    addColumn(B1111111);
    addColumn(B0001000);
    addColumn(B0010100);
    addColumn(B0100010);
    addColumn(B1000001);
  }
  else if (y == "L") {
    addColumn(B1111111);
    addColumn(B0000001);
    addColumn(B0000001);
    addColumn(B0000001);
    addColumn(B0000001);
  }
  else if (y == "M") {
    addColumn(B1111111);
    addColumn(B0100000);
    addColumn(B0011000);
    addColumn(B0100000);
    addColumn(B1111111);
  }
  else if (y == "N") {
    addColumn(B1111111);
    addColumn(B0010000);
    addColumn(B0001000);
    addColumn(B0000100);
    addColumn(B1111111);
  }
  else if (y == "O") {
    addColumn(B0111110);
    addColumn(B1000001);
    addColumn(B1000001);
    addColumn(B1000001);
    addColumn(B0111110);
  }
  else if (y == "P") {
    addColumn(B1111111);
    addColumn(B1001000);
    addColumn(B1001000);
    addColumn(B1001000);
    addColumn(B0110000);
  }
  else if (y == "Q") {
    addColumn(B0111100);
    addColumn(B1000010);
    addColumn(B1000010);
    addColumn(B1000010);
    addColumn(B0111101);
  }
  else if (y == "R") {
    addColumn(B1111111);
    addColumn(B1001000);
    addColumn(B1001100);
    addColumn(B1001010);
    addColumn(B0110001);
  }
  else if (y == "S") {
    addColumn(B0110010);
    addColumn(B1001001);
    addColumn(B1001001);
    addColumn(B1001001);
    addColumn(B0100110);
  }
  else if (y == "T") {
    addColumn(B1000000);
    addColumn(B1000000);
    addColumn(B1111111);
    addColumn(B1000000);
    addColumn(B1000000);
  }
  else if (y == "U") {
    addColumn(B1111110);
    addColumn(B0000001);
    addColumn(B0000001);
    addColumn(B0000001);
    addColumn(B1111110);
  }
  else if (y == "V") {
    addColumn(B1111100);
    addColumn(B0000010);
    addColumn(B0000001);
    addColumn(B0000010);
    addColumn(B1111100);
  }
  else if (y == "W") {
    addColumn(B1111110);
    addColumn(B0000001);
    addColumn(B0000110);
    addColumn(B0000001);
    addColumn(B1111110);
  }
  else if (y == "X") {
    addColumn(B1100011);
    addColumn(B0010100);
    addColumn(B0001000);
    addColumn(B0010100);
    addColumn(B1100011);
  }
  else if (y == "Y") {
    addColumn(B1110000);
    addColumn(B0001000);
    addColumn(B0001111);
    addColumn(B0001000);
    addColumn(B1110000);
  }
  else if (y == "Z") {
    addColumn(B1000011);
    addColumn(B1000101);
    addColumn(B1001001);
    addColumn(B1010001);
    addColumn(B1000011);
  }
  else if (y == "Z") {
    addColumn(B1000011);
    addColumn(B1000101);
    addColumn(B1001001);
    addColumn(B1010001);
    addColumn(B1000011);
  }
  else if (y == " ") {
    addColumn(B0000000);
    addColumn(B0000000);
    addColumn(B0000000);
    addColumn(B0000000);
    addColumn(B0000000);
  }
  else if (y == ".") {
    addColumn(B0000000);
    addColumn(B0000011);
    addColumn(B0000011);
    addColumn(B0000000);
    addColumn(B0000000);
  }
  else if (y == "_") {
    addColumn(B0000001);
    addColumn(B0000001);
    addColumn(B0000001);
    addColumn(B0000001);
    addColumn(B0000001);
  }
  else if (y == "-") {
    addColumn(B0000000);
    addColumn(B0001000);
    addColumn(B0001000);
    addColumn(B0001000);
    addColumn(B0000000);
  }
  else if (y == "!") {
    addColumn(B0000000);
    addColumn(B0000000);
    addColumn(B1111101);
    addColumn(B0000000);
    addColumn(B0000000);
  }
  else if (y == "(") {
    addColumn(B0000000);
    addColumn(B0000000);
    addColumn(B0000000);
    addColumn(B0111110);
    addColumn(B1000001);
  }
  else if (y == ")") {
    addColumn(B1000001);
    addColumn(B0111110);
    addColumn(B0000000);
    addColumn(B0000000);
    addColumn(B0000000);
  }
  else if (y == "%") {
    addColumn(B1100010);
    addColumn(B1100100);
    addColumn(B0001000);
    addColumn(B0010011);
    addColumn(B0100011);
  }
  else if (y == ",") {
    addColumn(B0000000);
    addColumn(B0000101);
    addColumn(B0000110);
    addColumn(B0000000);
    addColumn(B0000000);
  }
  else if (y == "?") {
    addColumn(B0100000);
    addColumn(B1000101);
    addColumn(B1001000);
    addColumn(B0110000);
    addColumn(B0000000);
  }
  else if (y == "#") {
    addColumn(B0010100);
    addColumn(B0111110);
    addColumn(B0010100);
    addColumn(B0111110);
    addColumn(B0010100);
  }
  else if (y == "@") {
    addColumn(B0111110);
    addColumn(B1000001);
    addColumn(B1011101);
    addColumn(B1011101);
    addColumn(B0111000);
  }
  else if (y == "$") {
    addColumn(B0110010);
    addColumn(B1001001);
    addColumn(B1111111);
    addColumn(B1001001);
    addColumn(B0100110);
  }
}

void addColumn(byte x) {
  columnNum += 1;
  msgCode[columnNum] = (x);
}
