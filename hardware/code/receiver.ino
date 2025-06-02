#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>

const int chipSelect = 7;  // SD 카드 CS 핀
SoftwareSerial loraSerial(0, 1); // D10 = RX, D11 = TX (※ 0Q, 1 대신 사용 추천)

File logFile;
bool setupComplete = false;

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);

  Serial.println("시작 중...");

  // SD 카드 초기화
  if (!SD.begin(chipSelect)) {
    Serial.println("SD 카드 초기화 실패!");
    while (1);
  }
  Serial.println("SD 카드 초기화 성공");

  // 로그 파일 헤더
  logFile = SD.open("log.csv", FILE_WRITE);
  if (logFile) {
    logFile.println("Time(ms),Data,RSSI,SNR");
    logFile.close();
    Serial.println("로그 파일 생성 및 헤더 작성 완료");
  } else {
    Serial.println("로그 파일 열기 실패!");
  }

  setupComplete = true;
  Serial.println("LoRa Receiver Ready");
}

void loop() {
  if (!setupComplete) return;

  if (loraSerial.available()) {
    String recvLine = loraSerial.readStringUntil('\n');
    recvLine.trim();

    Serial.println("수신된 원시 데이터: " + recvLine);

    if (recvLine.startsWith("+RCV=")) {
      parseAndLogData(recvLine);
    } else {
      Serial.println("형식 오류: +RCV=로 시작하지 않음");
    }
  }
}

void parseAndLogData(String input) {
  // 예: +RCV=1,11,Hello World,-47,12
  int firstComma  = input.indexOf(',');
  int secondComma = input.indexOf(',', firstComma + 1);
  int thirdComma  = input.indexOf(',', secondComma + 1);
  int fourthComma = input.indexOf(',', thirdComma + 1);

  if (firstComma == -1 || secondComma == -1 || thirdComma == -1 || fourthComma == -1) {
    Serial.println("파싱 실패! 콤마가 충분하지 않음.");
    return;
  }

  String data = input.substring(secondComma + 1, thirdComma);
  String rssi = input.substring(thirdComma + 1, fourthComma);
  String snr  = input.substring(fourthComma + 1);

  unsigned long currentTime = millis();
  String logEntry = String(currentTime) + "," + data + "," + rssi + "," + snr;

  // SD 카드에 저장
  logFile = SD.open("log.csv", FILE_WRITE);
  if (logFile) {
    logFile.println(logEntry);
    logFile.close();
  } else {
    Serial.println("로그 파일 열기 실패");
  }

  // 📢 시리얼 출력 (USB Serial)
  Serial.println("수신 메시지: " + data);
  Serial.println("RSSI: " + rssi + " dBm");
  Serial.println("SNR: " + snr + " dB");
}
