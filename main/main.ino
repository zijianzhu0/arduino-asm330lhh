#include <SPI.h>
// Arduino SPI reference: https://github.com/arduino/ArduinoCore-avr/blob/master/libraries/SPI/src/SPI.h


// asm330lhh specs
// Datasheet: https://www.st.com/resource/en/datasheet/asm330lhh.pdf
// Evalboard: https://www.st.com/en/evaluation-tools/steval-mki193v1.html#documentation
// SPI max clock frequency: 10 Mhz
// Endianness: MSBFIRST 
// Clock idle (clock priority): HIGH
// Clock phase: FALLING
// SPI_MODE selection: https://docs.arduino.cc/learn/communication/spi/
const int CS_PIN = 10; // Chip Select (SS)
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // SPI.begin(); // Initialize SPI
  SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE2));
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); // Deselect device
}

void loop() {
  // put your main code here, to run repeatedly:
  byte receivedData;

  // Send a command (example: read register 0x00)
  receivedData = SPI_Transfer(0x0F); 

  Serial.print("Received Data: 0x");
  Serial.println(receivedData, HEX);

  delay(1000);
}

// Function to transfer data via SPI
byte SPI_Transfer(byte data) {
    digitalWrite(CS_PIN, LOW);  // Select SPI device
    byte result = SPI.transfer(data); // Send and receive
    digitalWrite(CS_PIN, HIGH); // Deselect device
    return result;
}