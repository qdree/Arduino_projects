// #include <SPI.h>
// #include <RF24.h>
 
// // CE, CSN pins
// RF24 radio(7, 8);
 
// void setup(void)
// {
// 	while(!Serial);
// 	Serial.begin(9600);
 
// 	radio.begin();
// 	radio.setPALevel(RF24_PA_MAX);
// 	radio.setChannel(0x76);
// 	radio.openWritingPipe(0xF0F0F0F0E1LL);
// 	const uint64_t pipe = (0xE8E8F0F0E1LL);
// 	radio.openReadingPipe(1, pipe);
 
// 	radio.enableDynamicPayloads();
// 	radio.powerUp();
	
// }
 
// void loop(void){
// 	radio.startListening();
// 	Serial.println("Starting loop. Radio on.");
// 	char receivedMessage[32] = {0};
// 	if(radio.available()){
// 		radio.read(receivedMessage, sizeof(receivedMessage));
// 		Serial.println(receivedMessage);
// 		Serial.println("Turning off the radio.");
// 		radio.stopListening();
 
// 		String stringMessage(receivedMessage);
 
// 		if(stringMessage == "GETSTRING"){
// 			Serial.println("Looks like they want a string!");
// 			const char text[] = "Yo wassup, haha";
// 			radio.write(text, sizeof(text));
// 			Serial.println("We sent our message.");
// 		}
// 	}
// 	delay(100);
 
// }

// #include <SPI.h>
// #include <RF24.h>
// #include "printf.h"
 
// // ce, csn pins
// RF24 radio(7, 8);
 
// void setup(void)
// {
// 	Serial.begin(115200);
// 	printf_begin();
// 	radio.begin();
// 	radio.setAutoAck(1);
// 	radio.enableAckPayload();
// 	radio.setPALevel(RF24_PA_MAX);
// 	radio.setChannel(0x76);
// 	radio.setDataRate(RF24_1MBPS);
// 	radio.openWritingPipe(0xF0F0F0F0E1LL);
// 	// radio.openReadingPipe(1, 0xABCDABCD71LL);
// 	radio.enableDynamicPayloads();
// 	radio.powerUp();
// 	radio.printDetails();
 	
// }
 
// void loop(void)
// {
//     // byte gotByte;  
//     const char text[] = "Hello World is awesome";
//     printf("Now sending '%s' as payload.\n",&text);
// 	radio.write(&text, sizeof(text));
// 	// radio.startListening();
// 	// radio.read( &gotByte, sizeof(gotByte));
// 	// if(radio.available())
// 	// {
// 	// 	printf("Got response %d\n",gotByte);
// 	// 	radio.stopListening();
// 	// }
// 	delay(1000);
// }

// void loop()
// {
// 	radio.startListening();
// 	Serial.println("Starting loop. Radio on.");
// 	char receivedMessage[32] = {0};
// 	if(radio.available())
// 	{
// 		radio.read(receivedMessage, sizeof(receivedMessage));
// 		Serial.println(receivedMessage);
// 		Serial.println("Turning off the radio.");
// 		radio.stopListening();
 
// 		String stringMessage(receivedMessage);
 
// 		if(stringMessage == "GETSTRING")
// 		{
// 			Serial.println("Looks like they want a string!");
// 			const char text[] = "Yo wassup, haha";
// 			radio.write(text, sizeof(text));
// 			Serial.println("We sent our message.");
// 		}
// 	}
// 	delay(100);
// }