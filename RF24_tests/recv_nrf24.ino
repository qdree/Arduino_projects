radio = NRF24(GPIO, spidev.SpiDev())
radio.begin(0, 17)

radio.setRetries(0,15)

radio.setPayloadSize(25)
radio.setChannel(0x76)
radio.setDataRate(NRF24.BR_1MBPS)
radio.setPALevel(NRF24.PA_MAX)

radio.setAutoAck(True)
radio.enableDynamicPayloads()

radio.enableAckPayload()

radio.openWritingPipe(pipes[0])
radio.openReadingPipe(1, pipes[1])

radio.printDetails()
#time.sleep(3)

radio.startListening()

while True:
        #ackPL = ['R','e', 'c', 'e', 'i', 'v', 'e', 'd']
        ackPL = [1]
        while not radio.available(0):
                time.sleep(1/100)

        recv_message = []
        radio.read(recv_message, radio.getDynamicPayloadSize())
        print ("Received:")
        print (recv_message)
        print ("Translating the received message...")
        string = ""
        for n in recv_message:
                # Decode into standart unicode set
                if (n >= 32 and n <= 126):
                        string += chr(n)
        print (string)
        radio.writeAckPayload(1, ackPL, len(ackPL))
        print ("Loaded payload reply of {}".format(ackPL))
