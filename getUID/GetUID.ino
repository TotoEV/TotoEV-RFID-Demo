//RFID Tag typer
//Types out tag id in hex over USB keyboard

#include <SPI.h>
#include <MFRC522.h>
//#include <Keyboard.h>

#define RST_PIN 9         
#define SS_PIN 10        

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  SPI.begin();              //start SPI
  mfrc522.PCD_Init();       //start RC522 module
  //Keyboard.begin();         //start USB keyboard
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);     //LED off
  Serial.begin(9600);
  Serial.println("*** TotoEV RFID Card Demo ***");
  Serial.println();
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()){return;}
  if (!mfrc522.PICC_ReadCardSerial()){return;}
  digitalWrite(13,HIGH);     //LED on
  Serial.println("Found MiFare RFID Card!");
  Serial.print(F("Card UID:"));
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  
  //Keyboard.print("\n");
  mfrc522.PICC_HaltA();
  digitalWrite(13,LOW);     //LED off
  Serial.println();
  Serial.println();
}

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
