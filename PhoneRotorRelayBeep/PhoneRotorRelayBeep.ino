//
//
//                                     www.questsystems.com.ua
//▒█▀▀█ █░░█ █▀▀ █▀▀ ▀▀█▀▀ 　 █▀▀ █░░█ █▀▀ ▀▀█▀▀ █▀▀ █▀▄▀█ █▀▀
//▒█░▒█ █░░█ █▀▀ ▀▀█ ░░█░░ 　 ▀▀█ █▄▄█ ▀▀█ ░░█░░ █▀▀ █░▀░█ ▀▀█
//░▀▀█▄ ░▀▀▀ ▀▀▀ ▀▀▀ ░░▀░░ 　 ▀▀▀ ▄▄▄█ ▀▀▀ ░░▀░░ ▀▀▀ ▀░░░▀ ▀▀▀
//
//
//
//


#define PIN_SW_COUNTER 3
#define PIN_SW_REVERSE 4
#define RELAY 2
#define BEEP 5
#define LEN_PASSCODE 4
#define DELAY_DEBOUNCE 20

const uint8_t pass[LEN_PASSCODE] = {8, 2, 9, 1};
uint8_t code[LEN_PASSCODE];
uint8_t n_digits = 0;
int delayms = 50;

void setup()
{
  pinMode(PIN_SW_COUNTER, INPUT_PULLUP);
  pinMode(PIN_SW_REVERSE, INPUT_PULLUP);
  pinMode(RELAY, OUTPUT);
  pinMode(BEEP, OUTPUT);
  Serial.begin(9600);
}

void loop()
{

  if (!digitalRead(PIN_SW_REVERSE))
  {
    delay(DELAY_DEBOUNCE);
    while (!digitalRead(PIN_SW_REVERSE)) {
      if (digitalRead(PIN_SW_COUNTER))
      {
        code[n_digits]++;
        delay(DELAY_DEBOUNCE);
        while (digitalRead(PIN_SW_COUNTER));
        delay(DELAY_DEBOUNCE);
        
      }
    }
    //checkone();
    delay(DELAY_DEBOUNCE);
    
    n_digits++;
    if (n_digits == 1) checkone();
  }
  //if (n_digits == 1) checkone();
  if (n_digits >= LEN_PASSCODE) code_check();
}

void win() {
  beep(200);
  beep(200);
  digitalWrite(RELAY, HIGH);
  delay(11000);
  digitalWrite(RELAY, LOW);
}

void lose() {
  for (int i = 0; i < 5; i++) beep(50);
  Serial.println("Fail");
}

void code_reset() {
  Serial.print("Code reset ");
  n_digits = 0;
  for (uint8_t i = 0; i < LEN_PASSCODE; i++) {
    code[i] = 0;
    Serial.print(code[i]);
  }
  Serial.println();
}

void code_check() {
  Serial.print("Code Check ");
  for (uint8_t i = 0; i < n_digits; i++) Serial.print(code[i]);
  bool match = true;
  Serial.println();
  for (uint8_t i = 0; i < LEN_PASSCODE; i++) if (pass[i] != code[i]) match = false;
  if (match) win();
  else lose();
  code_reset();
}

void beep(unsigned char delayms) {
  analogWrite(BEEP, 150);
  delay(delayms);
  analogWrite(BEEP, 0);
  delay(delayms);
}

void checkone(){
//  Serial.println(pass[0]);
//  Serial.println(code[0]);
  if (pass[0] == code[0]) return;
  else code_reset();
  
}

