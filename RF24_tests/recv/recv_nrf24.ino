#include <SPI.h>
#include <RF24.h>
#include "printf.h"
 
// CE, CSN pins
RF24 radio(7, 8);

const uint64_t pipes[2] = {0xABCDABCD71LL, 0xF0F0F0F0E1LL};

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
    radio.startListening();
}

void loop()
{
  byte ackPL[] = {1};
  if(radio.available())
  {
    // char recv_message[32]; 
    byte recv_message[radio.getDynamicPayloadSize()]; 
    radio.read(&recv_message, radio.getDynamicPayloadSize());
    printf("Received: ");
    for (int i = 0; i < sizeof(recv_message); i++)
      printf("%d,",recv_message[i]);
    printf("\nTranslating the received message...\n");
    char string[radio.getDynamicPayloadSize()];    
    for(int n = 0; n < sizeof(recv_message); n++)
    {
        // //Decode into standart unicode set
        if (n >= 32 && n <= 126)
            string[n] += recv_message[n]; 
    }
    printf("%s\n",string);
    radio.writeAckPayload(1, ackPL, sizeof(ackPL));
    printf("Loaded payload reply of %d\n",ackPL[0]);
  }
}