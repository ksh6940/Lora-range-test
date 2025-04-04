#include <SPI.h>
#include <SD.h>

#define LED_pin 7
const int btn_pin = 2;

int buttonState = 0;
int lastButtonState = 0;
String incomingstring;

File myFile;

void setup() {
  Serial.begin(115200);

  Serial.print("Initializing SD Card...");

  // SD 카드 초기화
  if (!SD.begin(4)) {
    Serial.println("Initialization failed!");
    while (1); 
  }
  Serial.println("Initialization done.");

  pinMode(LED_pin, OUTPUT);
  pinMode(btn_pin, INPUT);
}

void loop() {
  buttonState = digitalRead(btn_pin);

  // 버튼 눌렀을 때 LED 켜고 데이터 저장 준비
  if (buttonState == HIGH && lastButtonState == LOW) {
    digitalWrite(LED_pin, HIGH);
    Serial.println("Button Pressed! Ready to save data.");
    delay(500);  // 버튼을 누를 때 잠시 대기
  } else {
    digitalWrite(LED_pin, LOW);
  }

  // 수신된 데이터 처리
  if (Serial.available()) {  // 수신 데이터가 있으면
    incomingstring = Serial.readString();
    Serial.print("Received data: ");
    Serial.println(receivedData);

    // RSSI 값 읽기 (수신된 신호 강도)
    Serial.println("AT+RSSI");
    delay(100);  // 짧은 시간 대기
    if (Serial.available()) {
      String rssiData = mySerial.readString();
      Serial.print("RSSI: ");
      Serial.println(rssiData);  // RSSI 값 출력

      // 수신된 데이터와 RSSI를 저장
      if (buttonState == HIGH) {
        saveTestFile(receivedData, rssiData);
      }
    }
  }

  lastButtonState = buttonState;  // 버튼 상태 업데이트
}

// 수신된 데이터를 테스트 파일에 저장하는 함수
void saveTestFile(String data, String rssi) {
  myFile = SD.open("test_data.csv", FILE_WRITE);

  if (myFile) {
    Serial.print("Writing to test_data.csv...");
    myFile.print("Received Data: ");
    myFile.print(data);  // 수신된 데이터를 파일에 저장
    myFile.print(", RSSI: ");  // RSSI 값 추가
    myFile.println(rssi);  // RSSI 값 저장
    myFile.close();
    Serial.println(" done.");
  } else {
    Serial.println("Error opening test_data.csv.");
  }
}
