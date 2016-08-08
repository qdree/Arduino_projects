// #include <EEPROM.h>
// #include <RotaryEncoder.h>

// const int hall_cnt = 2;

const int rele = 7;
const int glass_hall = 2;
const int plate_hall = 3;
const int led = 13;

// const int hall_sensors[hall_cnt] = {2,3};
// int hall_state[hall_cnt] = {HIGH, HIGH};
// int oldhall_state[hall_cnt] = {HIGH, HIGH};
// int catches_cnt = 0;

bool plate_correct = false;
bool glass_correct = false;
bool both_correct = false;

unsigned long startTimestamp;
unsigned long timestamp;
unsigned long difference;
const unsigned long timer_length = 2000; //2 seconds

int glass_timer = 0;
int plate_timer = 0;

void setup()
{
  pinMode(rele, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(rele, LOW);

  // attachInterrupt(digitalPinToInterrupt(glass_hall), glass_interrupt, FALLING);
  // attachInterrupt(plate_hall, plate_interrupt, FALLING);

  Serial.begin(9600);

  pinMode(plate_hall, INPUT);
  pinMode(glass_hall, INPUT);
}

void loop()
{
  rotation_check();
  //pos_check();
}

// void pos_check()
// {
//   static int oldplate_state = 0;
//   static int oldglass_state = 0;

//   int glass_state = digitalRead(glass_hall);
//   int plate_state = digitalRead(plate_hall);

//   if(oldglass_state != glass_state /*&& oldplate_state != plate_state*/)
//   {
// 		if(glass_correct /*&& plate_correct*/)
// 		{
// 			both_correct= true;

// 			if(glass_timer >= 0 /*&& plate_timer >= 0*/)
// 			{
// 				glass_timer--;
// 				// plate_timer--;


// 		    // Serial.print("Plate timer:");
// 	    	// Serial.print(plate_timer);
// 	    	// Serial.println();
// 			}
// 		}
// 		Serial.print("Glass state:");
// 		Serial.println(glass_state);

// 		// Serial.print("Plate state:");
// 		// Serial.print(plate_state);
// 		// Serial.println();

// 		oldglass_state = glass_state;
//     // oldplate_state = plate_state;
// 	}
//   Serial.print("Glass timer:");
// 	Serial.print(glass_timer);
// 	Serial.println();
// 	if(both_correct && glass_timer == 0 /*&& plate_timer == 0*/) win();
// }

void rotation_check()
{
  static int oldplate_state = 0;
  static int oldglass_state = 0;

  int glass_state = digitalRead(glass_hall);
  int plate_state = digitalRead(plate_hall);


  if(oldglass_state != glass_state) //check if position of first encoder changed from previous
  {
    if(glass_state == LOW) glass_correct = true; //if first encoder is in correct position
    else reset();

    Serial.print("Glass pos:");
    Serial.print(glass_state);
    Serial.println();

		oldglass_state = glass_state;
  }
  else if(oldplate_state != plate_state)  //check if position of second encoder changed from previous
  {
    if(plate_state == LOW) plate_correct = true; //if second encoder is in correct position
    else reset();

    Serial.print("Plate pos:");
    Serial.print(plate_state);
    Serial.println();

    oldplate_state = plate_state;
  }

 	if(plate_correct && glass_correct) 
	{
  	both_correct = true;
		startTimestamp = millis();
		timestamp = startTimestamp;

	  while(difference < timer_length/* && both_correct*/)
  	{
			difference = timestamp - startTimestamp;

      timestamp = millis();
			Serial.print("Difference: ");
			Serial.println(difference);

      if(difference >= timer_length)
      {
      	if((digitalRead(glass_hall) == LOW) && (digitalRead(plate_hall) == LOW))
      	//if(both_correct)
      	{
	      	// Serial.println("more");
      		win();
      		reset();
      	}
      	else 
      	{
      		reset();
      		return;
      	}
      }
		}
	}

	// if(oldhall_state != hall_state)
	// {
	// 	for(int i = 0; i < hall_cnt; i++)
	// 	{
	// 		hall_state[i] = digitalRead(hall_sensors[i]);
	//    	//Iterate by each sensor 													 
	// 		for(int j = 0; j < hall_cnt; j++)
	// 		{
	// 			if(hall_state[j] == LOW)
	// 			{
	// 				catches_cnt++;
	// 				oldhall_state[j] = hall_state[j];
	// 			}
	// 			//if one sensor from array is inactive - reset
	// 			else
	// 			{
	// 				reset();
	// 				catches_cnt = 0;
	// 				break;
	// 			}
	// 		}

	// 		if(hall_state[i] == LOW) 
	// 		{
	// 			Serial.print("Sensor:");
	// 			Serial.println(i);
	// 		}

	// 		//all sensors active
	// 		if(catches_cnt == hall_cnt) 
	// 		{
	// 			startTimestamp = millis();
	// 			timestamp = startTimestamp;

	// 		  while(difference < timer_length)
	// 			{
	// 				difference = timestamp - startTimestamp;

	// 	      timestamp = millis();
	// 				Serial.print("Difference: ");
	// 				Serial.println(difference);

	// 	      if(difference >= timer_length)
	// 	      {
	// 	      	if(catches_cnt = hall_cnt)
	// 	      	{
	// 	      		win();
	// 	      	}
	// 	      	else reset();
	// 	      }
	// 			}
	// 		}
	// 		else reset();	 
	// 	}
	// }

}


// void glass_interrupt()
// {
// 	glass_correct = true;
// 	glass_timer = 5;
// }

// void plate_interrupt()
// {
// 	plate_correct = true;
// 	plate_timer = 2;
// }

void win()
{
  Serial.println("Correct!");
  digitalWrite(rele, HIGH);
  digitalWrite(led, HIGH);
  while(true);
  delay(2000);
  digitalWrite(led, LOW);
}

void reset()
{
	difference = 0;
	// catches_cnt = 0;
  both_correct = false;
  glass_correct = false;
  plate_correct = false;
}