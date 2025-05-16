#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>

const int chipSelect = 7;  // SD 카드 CS 핀
SoftwareSerial loraSerial(0, 1); // D10 = RX, D11 = TX  ← 변경됨

File logFile;

void setup() {
  Serial.begin(9600);         // USB 시리얼
  loraSerial.begin(9600);     // LoRa 통신

  if (!SD.begin(chipSelect)) {
    Serial.println("SD 카드 초기화 실패!");
    while (1);
  }
  Serial.println("SD 카드 초기화 성공");

  // 로그 파일 헤더 (최초 한 번)
  logFile = SD.open("log.csv", FILE_WRITE);
  if (logFile) {
    logFile.println("Time(ms),Data,RSSI,SNR");
    logFile.close();
  }

  Serial.println("LoRa Receiver Ready");
}

void loop() {
  if (loraSerial.available()) {
    String recvLine = loraSerial.readStringUntil('\n');
    recvLine.trim();
    Serial.println("수신: " + recvLine);

    if (recvLine.startsWith("+RCV=")) {
      parseAndLogData(recvLine);
    }
  }
}

void parseAndLogData(String input) {
  // 예시: +RCV=1,11,Hello World,-47,12
  int firstComma = input.indexOf(',');
  int secondComma = input.indexOf(',', firstComma + 1);
  int thirdComma = input.indexOf(',', secondComma + 1);
  int fourthComma = input.indexOf(',', thirdComma + 1);

  if (firstComma == -1 || secondComma == -1 || thirdComma == -1 || fourthComma == -1) {
    Serial.println("파싱 실패");
    return;
  }

  String data = input.substring(secondComma + 1, thirdComma);
  String rssi = input.substring(thirdComma + 1, fourthComma);
  String snr = input.substring(fourthComma + 1);

  unsigned long currentTime = millis();
  String logEntry = String(currentTime) + "," + data + "," + rssi + "," + snr;

  Serial.println("로그: " + logEntry);

  logFile = SD.open("log.csv", FILE_WRITE);
  if (logFile) {
    logFile.println(logEntry);
    logFile.close();
  } else {
    Serial.println("로그 파일 열기 실패");
  }
}
