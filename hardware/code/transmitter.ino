#include <SoftwareSerial.h>

// 핀 정의
const int buttonPin = 2;
const int ledPin = 7;

// SoftwareSerial 핀 설정 (RX, TX)
SoftwareSerial loraSerial(0, 1); // Rylr998 연결용 (주의: 0,1은 기본 UART와 겹침)

// 버튼 상태 추적
bool lastButtonState = LOW;
bool currentButtonState = LOW;
bool messageSent = false;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  loraSerial.begin(9600);

  digitalWrite(ledPin, LOW);
}

void loop() {
  currentButtonState = digitalRead(buttonPin);

  // 버튼이 눌렸고 이전에는 안 눌렸으며 아직 메시지를 전송하지 않은 경우
  if (currentButtonState == HIGH && lastButtonState == LOW && !messageSent) {
    digitalWrite(ledPin, HIGH);

    sendLoRaMessage("Hello World");

    messageSent = true;

    delay(1000);  // 메시지 전송 후 LED 1초 켜기
    digitalWrite(ledPin, LOW);
  }

  // 버튼을 떼면 다시 전송 가능하게 플래그 초기화
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    messageSent = false;
  }

  lastButtonState = currentButtonState;
}

void sendLoRaMessage(String message) {
  String command = "AT+SEND=1," + String(message.length()) + "," + message;
  Serial.println("[Sending] " + command);
  loraSerial.println(command);

  // 응답 출력
  delay(100); // 응답 대기
  while (loraSerial.available()) {
    Serial.write(loraSerial.read());
  }
}
