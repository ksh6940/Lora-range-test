#include <SoftwareSerial.h>

// 핀 정의
const int buttonPin = 2;
const int ledPin = 7;

// SoftwareSerial 핀 설정 (RX, TX)
SoftwareSerial loraSerial(0, 1); // 예: D10 = RX, D11 = TX

// 버튼 상태 추적 변수
bool lastButtonState = LOW;
bool currentButtonState = LOW;
bool messageSent = false;  // 메시지를 한 번만 전송하기 위한 플래그 변수

void setup() {
  // 핀 모드 설정
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Serial 포트 초기화
  Serial.begin(9600);
  loraSerial.begin(9600); // Rylr998 기본 통신 속도

  // 초기 LED 상태 OFF
  digitalWrite(ledPin, LOW);
}

void loop() {
  currentButtonState = digitalRead(buttonPin);

  // 버튼이 눌렸을 때만 동작 (한 번만 전송하도록)
  if (currentButtonState == HIGH && lastButtonState == LOW && !messageSent) {
    // LED ON
    digitalWrite(ledPin, HIGH);

    // Rylr998으로 데이터 전송
    sendLoRaMessage("Hello World");

    // 메시지를 한 번만 전송하기 위해 플래그 설정
    messageSent = true;

    // 간단한 디바운싱 대기
    delay(300);

    // LED OFF (1초 후)
    delay(1000);
    digitalWrite(ledPin, LOW);
  }

  // 버튼 상태 변경을 감지하기 위한 코드
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    // 버튼을 떼었을 때 메시지 전송을 다시 가능하게 함
    messageSent = false;
  }

  lastButtonState = currentButtonState;
}

void sendLoRaMessage(String message) {
  // Rylr998 데이터 전송 명령 형식: AT+SEND=ADDRESS,LENGTH,DATA
  String command = "AT+SEND=1," + String(message.length()) + "," + message;
  Serial.println(command);
  loraSerial.println(command);

  // 응답 확인 (필요 시 시리얼 모니터 출력)
  while (loraSerial.available()) {
    Serial.write(loraSerial.read());
  }
}
#include <SoftwareSerial.h>

// 핀 정의
const int buttonPin = 2;
const int ledPin = 7;

// SoftwareSerial 핀 설정 (RX, TX)
SoftwareSerial loraSerial(0, 1); // 예: D10 = RX, D11 = TX

// 버튼 상태 추적 변수
bool lastButtonState = LOW;
bool currentButtonState = LOW;

void setup() {
  // 핀 모드 설정
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Serial 포트 초기화
  Serial.begin(9600);
  loraSerial.begin(9600); // Rylr998 기본 통신 속도

  // 초기 LED 상태 OFF
  digitalWrite(ledPin, LOW);
}

void loop() {
  currentButtonState = digitalRead(buttonPin);

  // 버튼이 눌렸을 때만 동작
  if (currentButtonState == HIGH && lastButtonState == LOW) {
    // LED ON
    digitalWrite(ledPin, HIGH);

    // Rylr998으로 데이터 전송
    sendLoRaMessage("Hello World");

    // 간단한 디바운싱 대기
    delay(300);

    // LED OFF (1초 후)
    delay(1000);
    digitalWrite(ledPin, LOW);
  }

  lastButtonState = currentButtonState;
}

void sendLoRaMessage(String message) {
  // Rylr998 데이터 전송 명령 형식: AT+SEND=ADDRESS,LENGTH,DATA
  String command = "AT+SEND=1," + String(message.length()) + "," + message;
  loraSerial.println(command);

  // 응답 확인 (필요 시 시리얼 모니터 출력)
  while (loraSerial.available()) {
    Serial.write(loraSerial.read());
  }
}
