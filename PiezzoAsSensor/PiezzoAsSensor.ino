// these constants won't change:
const int ledPin = 13;      // led connected to digital pin 13
const int knockSensor = A1; // the piezo is connected to analog pin 0
const int threshold = 20;  // threshold value to decide when the detected sound is a knock or not


// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW;         // variable used to store the last LED status, to toggle the light

void setup() {
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  Serial.begin(9600);       // use the serial port
}

void loop() {
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(knockSensor);

  // if the sensor reading is greater than the threshold:
  if (sensorReading >= threshold) {
    // //toggle the status of the ledPin:
    // ledState = !ledState;
    // //update the LED pin itself:
    // digitalWrite(ledPin, ledState);
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    // send the string "Knock!" back to the computer, followed by newline
    Serial.println("SENSED!");
  }
  delay(100);  // delay to avoid overloading the serial port buffer
}