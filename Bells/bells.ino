#include <CapacitiveSensor.h>

#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_G5 784
#define NOTE_A5 880

const int buzzer_pin = 12;
const int relay_pin = 13;

const int pass_lenght = 5;
const int passcode[pass_lenght] = {2, 1, 4, 3, 2}; // passcode
const int BellsNotes[5] = { NOTE_A5, NOTE_G5, NOTE_E5, NOTE_D5, NOTE_C5};

int bells_touch_cnt = 0;
long threshold = 6000;

CapacitiveSensor  cs_bell_1 = CapacitiveSensor(2, 3); // the smallest bell
CapacitiveSensor  cs_bell_2 = CapacitiveSensor(4, 5); 
CapacitiveSensor  cs_bell_3 = CapacitiveSensor(6, 7); 
CapacitiveSensor  cs_bell_4 = CapacitiveSensor(8, 9); 
CapacitiveSensor  cs_bell_5 = CapacitiveSensor(10, 11); // the biggest bell

CapacitiveSensor* Cap_arr[5] = {&cs_bell_1, &cs_bell_2, &cs_bell_3, &cs_bell_4, &cs_bell_5};


void setup()
{
	Serial.begin(9600);
	
	cs_bell_1.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1
	cs_bell_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 2
	cs_bell_3.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 3
	cs_bell_4.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 4
	cs_bell_5.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 5


	Serial.print("Correct comb is: ");

	for (int el = 0; el < pass_lenght; el++)  
		Serial.print(passcode[el]);

	Serial.println("");

	pinMode(buzzer_pin, OUTPUT);
	pinMode(relay_pin, OUTPUT);  

	digitalWrite(relay_pin, LOW);

}

void loop()
{
	read_vals();
}

/* 
Reads states of each sensor from Cap_arr[]. Compares received sensor with threshold variable.
If check_vals() func. returns true and wait until bells_touch_cnt variable gain pass_lenght equivalence. 
Otherwise checks if sensors index is equal to 0 element from passcode[] and if not resets bells_touch_cnt var. 
*/
void read_vals()
{
	for (int i = 0; i < (sizeof(Cap_arr)/sizeof(Cap_arr[i])); i++)
	{
		long sensor_val = Cap_arr[i]->capacitiveSensor(30);

		if (sensor_val >= threshold)
		{
			playMillis(300, BellsNotes[i]);
			if (check_vals(i))
			{
				Serial.print("sensor triggered touch with value of: ");
				Serial.print(sensor_val);
				Serial.print(" on: ");
				Serial.print(i);
				Serial.println(" sensor");
								
				if (bells_touch_cnt == pass_lenght)
					win();
			}
			else
	        {
	          if (i == passcode[0])
	          {
	            bells_touch_cnt = 1;
	            return;
	          }

	          Serial.println("");
	          Serial.print("wrong bell touched: "); 
	          Serial.println(i);
	          bells_touch_cnt = 0;
	          Serial.println("READY!");
	        }
		}
	}
}

/* Check if amount of touches equales to index of touched bell */
bool check_vals(int index)
{
	if(passcode[bells_touch_cnt++] != index)
		return false;

	Serial.println(" Correct, go on...");
	return true;
}

void win()
{
	Serial.println("WIN!");
	digitalWrite(relay_pin, HIGH);
	bells_touch_cnt = 0;
	while(true);
}


/* Play note which is given as 2nd parameter for period of time which is given as 1st parameter */
void playMillis(long milliseconds, int note)
{
	tone(buzzer_pin, note, milliseconds);
	delay(milliseconds);
	return;
}