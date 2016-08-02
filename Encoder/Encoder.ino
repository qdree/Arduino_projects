#include <EEPROM.h>
#include <RotaryEncoder.h>

const int rele = 7;
RotaryEncoder encoder_glass(3, 2);
RotaryEncoder encoder_plate(4, 5);

uint8_t n_digits = 0;
const int glass_correct_pos = 14;
const int plate_correct_pos = 8;

bool plate_correct = false;
bool glass_correct = false;
bool both_correct = false;

int gp_start;
int pp_start;

unsigned long startTimestamp;
unsigned long timestamp;
const unsigned long timer_length = 2000; //2 seconds

void setup()
{
  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);

  Serial.begin(9600);

  //read position of encoders from EEPROM memory and set it as current after system is restarted
  gp_start = EEPROM.read(0);
  pp_start = EEPROM.read(1);
  encoder_glass.setPosition(gp_start);
  encoder_plate.setPosition(pp_start);
}

void loop()
{
  rotation_check();
}

void rotation_check()
{
  static int pos_plate = 0;
  static int pos_glass = 0;

  //neccessary function to work with encoders
  encoder_glass.tick();
  encoder_plate.tick();

  //read positions of each encoder
  int newPos_glass = encoder_glass.getPosition(); 
  int newPos_plate = encoder_plate.getPosition();

  //reset encoders state if they did full circle
  if(newPos_glass > 23 || newPos_glass < -23) encoder_glass.setPosition(0);
  if(newPos_plate > 23 || newPos_plate < -23) encoder_plate.setPosition(0);

  if(pos_glass != newPos_glass) //check if position of first encoder changed from previous
  {
    if(newPos_glass == glass_correct_pos) glass_correct = true; //if first encoder is in correct position
    else glass_correct = false;

    Serial.print("Glass pos:");
    Serial.print(newPos_glass);
    Serial.println();

    pos_glass = newPos_glass;
    EEPROM.write(0, pos_glass); //save 1st encoder's position state to EEPROM memory
  }
  else if(pos_plate != newPos_plate)  //check if position of second encoder changed from previous
  {
    if(newPos_plate == plate_correct_pos) plate_correct = true; //if second encoder is in correct position
    else plate_correct = false;

    Serial.print("Plate pos:");
    Serial.print(newPos_plate);
    Serial.println();

    pos_plate = newPos_plate;
    EEPROM.write(1, pos_plate); //save 2nd encoder's position state to EEPROM memory
  }

  if(plate_correct && glass_correct) //both encoders are in correct position
  {
    both_correct = true;
    startTimestamp = millis();
    timestamp = startTimestamp;


    while ( (timestamp - startTimestamp) <= timer_length)
    {
        timestamp = millis();
        // Serial.print("Timestamp: ");
        // Serial.println(timestamp);

        // Serial.print("Start timestamp: ");
        // Serial.println(startTimestamp);

        // Serial.print("Difference: ");
        // Serial.println(timestamp - startTimestamp);
        if(both_correct && timestamp == timer_length) win();

    }
  }


}

void win()
{
  Serial.println("Correct!");
  digitalWrite(rele, HIGH);
  // while(true);
  //delay(5000);
  //digitalWrite(rele, HIGH);
}
