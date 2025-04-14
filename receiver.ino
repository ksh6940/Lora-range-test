#include <SoftwareSerial.h>

SoftwareSerial SoftSerial(2, 3); // Rx, Tx
String buffer = "";

void setup() {
    Serial.begin(9600);
    SoftSerial.begin(9600);
}

void loop() {
    if (SoftSerial.available()) {
        int readByte = SoftSerial.read();
        Serial.write(readByte);

        if (readByte == '\r') {
            String s = buffer.substring(0, 1);
            if (s.equals("0")) {
                Serial.println("Received: 0");
            } else if (s.equals("1")) {
                Serial.println("Received: 1");
            } else {
                Serial.println("Unknown input");
            }
            buffer = "";
        }
    } else {
        buffer += (char)SoftSerial.read();
    }
}
