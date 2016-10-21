#include <SPI.h>
#include <RF24.h>
#include "printf.h"
 
// CE, CSN pins
RF24 radio(7, 8);
int msg[1];
String theMessage = "";
int lastmsg = 1;

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

    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1, pipes[1]);
    radio.printDetails(); 
    radio.startListening();
}

// void loop()
// {
//     byte ackPL[] = {1};
//     while(!radio.available(0))
//         delay(10);

//     int recv_message[32]; 
//     radio.read(&recv_message, radio.getDynamicPayloadSize());
//     printf("Received: %d\n");
//     printf("Translating the received message...\n");
//     char *string;    
//     for(int n = 0; n < sizeof(recv_message); n++)
//     {
//         //Decode into standart unicode set
//         if (n >= 32 && n <= 126)
//             string += (n - 32);
//     }
//     Serial.println(string);
//     radio.writeAckPayload(1, ackPL, sizeof(ackPL));
//     printf("Loaded payload reply of %d",ackPL);
// }

void loop(void)
{
    byte ackPL[] = {2,1};
	if (radio.available())
	{
		radio.read(msg, 1);
		char theChar = msg[0];
		if (msg[0] != 2)
		{
			theMessage.concat(theChar);
		}
		else
      	{
       		Serial.println(theMessage);
       		theMessage= ""; 
   		    radio.writeAckPayload(1, &ackPL, sizeof(ackPL));
			printf("Loaded payload reply of %d, %d\n",ackPL[0], ackPL[1]);
      	}

   	}
}