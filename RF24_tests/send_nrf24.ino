#include <SPI.h>
#include <RF24.h>
#include "printf.h"
 
// CE, CSN pins
RF24 radio(7, 8);

const uint64_t pipes[2] = {0xF0F0F0F0E1LL, 0xABCDABCD71LL};

void setup()
{
	Serial.begin(9600);
	printf_begin();

	radio.begin();
	radio.setRetries(0,15);
	radio.setPayloadSize(25);
	radio.setChannel(0x76);

	radio.setDataRate(RF24_1MBPS);
	radio.setPALevel(RF24_PA_MAX);
	radio.setAutoAck(1);
	radio.enableDynamicPayloads();
	radio.enableAckPayload();


	radio.openWritingPipe(pipes[1]);
	radio.openReadingPipe(1, pipes[0]);
	radio.printDetails();
	
}

void loop()
{
	const char message[] = "Hello!";
	radio.write(message, sizeof(message));
	printf("Sent: %s\n", message);

	if (radio.isAckPayloadAvailable())
	{
		byte returnedPL;
		radio.read(&returnedPL, sizeof(returnedPL));
		printf("Recieved back: %d\n", returnedPL);
	}
	else
	{
		printf("No payload received\n");	
	}

	delay(1000);
}
