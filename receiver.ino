#include <SPI.h>
#include <SD.h>

#define LED_pin 7

const int btn_pin = 2;
int buttonState = 0;
int lastButtonState = 0;

File myFile;

void setup() {
  Serial.begin(57600);
  Serial.print("Initializing SD Card...");

  if (!SD.begen(4)){
    Serial.println("Initialization failed!");
    while(1);
  }
  Serial.println("Initialization done.");

  Serial.print("Intializing Module...");

  pinMode(LED_pin, OUTPUT);
  pinMode(btn_pin, INPUT);

  Serial.print("Intializing Module Done")
}

void loop() {
  buttonState = digitalRead(btn_pin);

  if (buttonState == HIGH && lastButtonState == LOW) {
    digitalWrite(LED_pin, HIGH);
    Serial.println("AT+SEND=2,1,Hello World");
    delay(200);
  }

  if (buttonState == LOW) {
    digitalWrite(LED_pin, LOW);
  }

  lastButtonState = buttonState;
}

void saveFile(RSSI){
  myFile = SD.open("test.csv", FILE_WRITE);

  if (myFile) {
    Serial.print("Writing to test.csv");
    myFile.println(RSSI);
    myFile.close();
    Serial.println("done.")
  } else {
    Serial.println("error opening csv file.")
  }
}
