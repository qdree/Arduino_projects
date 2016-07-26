

#include <RotaryEncoder.h>
#define passlen 4
#define bzz 4
#define rele 6

RotaryEncoder encoder(A2, A3);

const int pass[passlen] = { -6, 8, -9, 1};
uint8_t n_digits = 0;


void setup()
{
  pinMode(bzz, OUTPUT);
  pinMode(rele, OUTPUT);
  digitalWrite(rele, HIGH);
  digitalWrite(bzz, HIGH);

  Serial.begin(9600);
  Serial.println("QuestSystems.com.ua Rotary Safe");

}



void loop()
{
  rotor();
}

void rotor()
{
  static int pos = 0;
  encoder.tick();
  int newPos = encoder.getPosition();

  if (newPos > 30 | newPos < -30) encoder.setPosition(0);

  if (pos != newPos)
  {
    if (newPos == pass[n_digits])
    {
      if (n_digits == 0 && pos < newPos) return;
      beep();
      n_digits++;
      if (n_digits == 4) win();
    }
    else if (newPos > pos && newPos > pass[n_digits])
    {
      codereset();
    }
    else if (newPos < pos && newPos < pass[n_digits])
    {
      codereset();
    }

    Serial.print(newPos);
    Serial.println();
    pos = newPos;
  }
}

void beep()
{
  //tone(bzz,90,10);
  digitalWrite(bzz, LOW);
  delay(100);
  digitalWrite(bzz, HIGH);

}

void codereset()
{
  n_digits = 0;
  Serial.println("Code Reset!");
}

void win()
{
  Serial.println("Winner");
  digitalWrite(rele, LOW);
  delay(5000);
  digitalWrite(rele, HIGH);
  codereset();
}


