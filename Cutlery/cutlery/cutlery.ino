
const int hall_cnt = 6;

const int rele = 12;
const int hall_sensors[hall_cnt] = {2, 3, 4, 5, 6, 7}; 
//const int hall_sensors[hall_cnt] = {5}; 

int hall_state[hall_cnt];
int hall_prev_state[hall_cnt];

int catches_cnt = 0;
int cnt = 0;


void setup()
{
	Serial.begin(9600);
	//reset();
	pinMode(rele, OUTPUT);
 
	for(int pins = 0; pins < hall_cnt; pins++)
		pinMode(hall_sensors[pins], INPUT);

  	digitalWrite(rele, HIGH);
}

void loop()
{
	for(int i = 0; i < hall_cnt; i++)
	{
		hall_state[i] = digitalRead(hall_sensors[i]);
	 	
	 // 	//---Main variant of program, sensors quantity sets in "hall_cnt" variable---//
	 // 	//Iterate by each sensor 													 //
		// for(int j = 0; j < hall_cnt; j++)											 //
		// {																			 //
		// 	if(hall_state[j] == LOW) 												 //
		// 	{																		 //
		// 		Serial.println(catches_cnt);										 //
		// 		catches_cnt++;														 //
		// 	}   																	 //
		// 	//if one sensor from array is inactive - reset                           //
		// 	else 																	 //
		// 	{																		 //
		// 		catches_cnt = 0; 													 //
		// 		break;																 //
		// 	}																		 //
		// }																			 //
		// //all sensors active            											 //
		// if(catches_cnt == hall_cnt)													 //
		// 	win();																	 //
		// //---------------------------------------------------------------------------//

		//--Simplified variant of program, only 6 sensors campatible--//
		//if(hall_state[0] == LOW &&								  //
		//hall_state[1] == LOW &&									  //
	 	//hall_state[2] == LOW &&									  //
	 	//hall_state[3] == LOW &&									  //
		// hall_state[4] == LOW &&								 	  //
		// hall_state[5] == LOW) win();								  //
		//------------------------------------------------------------//

		//----BLOCK TO TEST EACH SENSOR---// 
			if(hall_state[i] == LOW)   		//
			{						   		//		
				win();				   		//
				Serial.println(i);	   		//
			}						   		//
		//--------------------------------//
	}
}

void win()
{
	Serial.println("GOTCHA!!");
	digitalWrite(rele, LOW);

	//while(true);

	delay(1000);
	digitalWrite(rele, HIGH);
	catches_cnt = 0;
	//memset(hall_prev_state, 0x00, hall_cnt);

}

void reset()
{
	memset(hall_prev_state, 0x00, hall_cnt);
	catches_cnt = 0;
}