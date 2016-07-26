#include <SPI.h>
#include <MFRC522.h>
#include <LedControl.h>
#include <binary.h>

#define RST_PIN    9   // RFID
#define SS_PIN    10    // RFID

int BUTTON = 2;
int BZZ = 4;
int RELE = 3;
int DIN = 7;
int CS =  6;
int CLK = 5;
int DELTIME = 50; //delay time scanning
bool FINGER; //RFID result
long TIME = 0;

byte x[8] = {0xc3, 0x66, 0x3c, 0x18, 0x18, 0x3c, 0x66, 0xc3};
byte w[8] = {0x01, 0x03, 0x03, 0x87, 0xce, 0x7c, 0x38, 0x10};

LedControl lc = LedControl(DIN, CLK, CS, 0);
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
  Serial.begin(9600);
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  //  ShowReaderDetails();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, type, and data blocks..."));
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, HIGH);


  lc.shutdown(0, false);      //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0, 15);     // Set the brightness to maximum value
  lc.clearDisplay(0);         // and clear the display
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BZZ, OUTPUT); //let's the music play
}

void loop() {
  // scan();

  int BUTSTATE = digitalRead(BUTTON);
  if (!BUTSTATE) {
    checkcard();
    checkcard();
    scan();
    if (FINGER) win();
    else lose();
  }
  timer();

}

void checkcard() {

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( mfrc522.PICC_ReadCardSerial()) {
    TIME = millis();
    FINGER = true;

  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}

void scan() {
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, B11111111);
    delay(DELTIME);
    lc.setRow(0, i, B00000000);
  }
  for (int i = 6; i > 0; i--) {
    lc.setRow(0, i, B11111111);
    delay(DELTIME);
    lc.setRow(0, i, B00000000);
  }
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, B11111111);
    delay(DELTIME);
    lc.setRow(0, i, B00000000);
  }
  for (int i = 6; i > 0; i--) {
    lc.setRow(0, i, B11111111);
    delay(DELTIME);
    lc.setRow(0, i, B00000000);
  }

}



void lose() {
  printByte(x);
  beep(50);
  beep(50);
  beep(50);
  beep(50);
  beep(50);
  beep(50);
}

void win() {
  printByte(w);
  analogWrite(BZZ, 150);      // Almost any value can be used except 0 and 255
  // experiment to get the best tone
  delay(700);          // wait for a delayms ms
  analogWrite(BZZ, 0);       // 0 turns it off

}


void printByte(byte character [])
{
  int i = 0;
  for (i = 0; i < 8; i++)
  {
    lc.setRow(0, i, character[i]);
  }
}

void beep(unsigned char delayms) {
  analogWrite(BZZ, 500);      // Almost any value can be used except 0 and 255
  // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(BZZ, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms
}

void timer() {
  if (millis() - TIME > 600)FINGER = false;
}

