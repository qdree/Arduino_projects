// #include <EEPROM.h>
// #include <RotaryEncoder.h>

const int rele = 7;
const int glass_hall = 5;
const int plate_hall = 3;
// RotaryEncoder encoder_glass(3, 2);
// RotaryEncoder encoder_plate(4, 5);

uint8_t n_digits = 0;
// const int glass_correct_pos = 14;
// const int plate_correct_pos = 8;

bool plate_correct = false;
bool glass_correct = false;
bool both_correct = false;

// int gp_start;
// int pp_start;

// unsigned long startTimestamp;
// unsigned long timestamp;
// const unsigned long timer_length = 2000; //2 seconds

int glass_timer = 0;
int plate_timer = 0;

void setup()
{
  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);

  attachInterrupt(glass_hall, glass_interrupt, FALLING);
  attachInterrupt(plate_hall, plate_interrupt, FALLING);

  Serial.begin(9600);

  pinMode(plate_hall, INPUT);
  pinMode(glass_hall, INPUT);

  //read position of encoders from EEPROM memory and set it as current after system is restarted
  // gp_start = EEPROM.read(0);
  // pp_start = EEPROM.read(1);
  // encoder_glass.setPosition(gp_start);
  // encoder_plate.setPosition(pp_start);
}

void loop()
{
  rotation_check();
}

void rotation_check()
{
  static int oldplate_state = 0;
  static int oldglass_state = 0;

  //neccessary function to work with encoders
  // encoder_glass.tick();
  // encoder_plate.tick();

  //read positions of each encoder
  // int newPos_glass = encoder_glass.getPosition(); 
  // int newPos_plate = encoder_plate.getPosition();

  // //reset encoders state if they did full circle
  // if(newPos_glass > 23 || newPos_glass < -23) encoder_glass.setPosition(0);
  // if(newPos_plate > 23 || newPos_plate < -23) encoder_plate.setPosition(0);

  int glass_state = digitalRead(glass_hall);
  int plate_state = digitalRead(plate_hall);


  if(oldglass_state != glass_state) //check if position of first encoder changed from previous
  {
    if(glass_state == LOW) glass_correct = true; //if first encoder is in correct position
    else glass_correct = false;

    Serial.print("Glass pos:");
    Serial.print(glass_state);
    Serial.println();

		oldglass_state = glass_state;
    // EEPROM.write(0, pos_glass); //save 1st encoder's position state to EEPROM memory
  }
  else if(oldplate_state != plate_state)  //check if position of second encoder changed from previous
  {
    if(plate_state == LOW) plate_correct = true; //if second encoder is in correct position
    else plate_correct = false;

    Serial.print("Plate pos:");
    Serial.print(plate_state);
    Serial.println();

    oldplate_state = plate_state;
    // EEPROM.write(1, pos_plate); //save 2nd encoder's position state to EEPROM memory
  }

  // startTimestamp = millis();

  // if(/*plate_correct &&*/ glass_correct) 
  // {
  // 	both_correct = true;

  // 	// Serial.print("Plate timer: ");
  // 	// Serial.println(plate_timer);
  	if(glass_timer > 0/* && plate_timer > 0*/)
  	{
  		glass_timer--;
	  	Serial.print("Glass timer: ");
  		Serial.println(glass_timer);
  		//plate_timer--;
  		/*if(glass_timer == 0 /*&& plate_timer == 0) && both_correct)*/ win();
  	}
  	else reset();
  	// }
  // }

  // if(plate_correct && glass_correct) //both encoders are in correct position
  // {
  //   both_correct = true;
  //   timestamp = startTimestamp;

  //   while ( (timestamp - startTimestamp) < timer_length)
  //   {
  //       timestamp = millis();
  //       // Serial.print("Timestamp: ");
  //       // Serial.println(timestamp);

  //       // Serial.print("Start timestamp: ");
  //       // Serial.println(startTimestamp);

  //       // Serial.print("Difference: ");
  //       // Serial.println(timestamp - startTimestamp);
  //       if(((timestamp - startTimestamp) >= timer_length) && both_correct) win();
  //       else reset();

  //   }
  // }
}

void glass_interrupt()
{
	if(both_correct)
		glass_timer += 2;
}

void plate_interrupt()
{
	if(both_correct)
		plate_timer += 2;
}

void win()
{
  Serial.println("Correct!");
  digitalWrite(rele, HIGH);
  // while(true);
  //delay(5000);
  //digitalWrite(rele, HIGH);
}

void reset()
{
  both_correct = false;
  glass_correct = false;
  plate_correct = false;
}