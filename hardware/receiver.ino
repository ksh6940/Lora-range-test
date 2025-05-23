#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>

const int chipSelect = 7;  // SD 카드 CS 핀
SoftwareSerial loraSerial(0, 1); // D10 = RX, D11 = TX ← 변경됨

File logFile;
bool setupComplete = false;  // 설정 완료 여부를 추적하는 변수

void setup() {
  Serial.begin(9600);         // USB 시리얼
  loraSerial.begin(9600);     // LoRa 통신

  Serial.println("시작 중...");

  // SD 카드 초기화
  if (!SD.begin(chipSelect)) {
    Serial.println("SD 카드 초기화 실패!");
    while (1);  // 종료되지 않음, 무한 루프
  }
  Serial.println("SD 카드 초기화 성공");

  // 로그 파일 헤더 (최초 한 번)
  logFile = SD.open("log.csv", FILE_WRITE);
  if (logFile) {
    logFile.println("Time(ms),Data,RSSI,SNR");
    logFile.close();
    Serial.println("로그 파일 생성 및 헤더 작성 완료");
  } else {
    Serial.println("로그 파일 열기 실패!");
  }

  setupComplete = true;  // 설정 완료 플래그를 true로 설정
  Serial.println("LoRa Receiver Ready");
}

void loop() {
  if (!setupComplete) {
    return;  // 설정이 완료되지 않았다면, 다른 처리는 하지 않음
  }

  if (loraSerial.available()) {
    String recvLine = loraSerial.readStringUntil('\n');
    recvLine.trim();
    
    // 수신된 데이터 출력 (디버깅 메시지)
    Serial.println("수신된 데이터: " + recvLine); // 수신된 데이터 출력

    if (recvLine.startsWith("+RCV=")) {
      parseAndLogData(recvLine);  // 데이터 파싱 후 기록
    } else {
      Serial.println("수신된 데이터가 +RCV= 형식이 아님");  // 형식 오류 메시지 출력
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
    Serial.println("파싱 실패! 예상되는 구분자가 없습니다.");
    return;
  }

  String data = input.substring(secondComma + 1, thirdComma);
  String rssi = input.substring(thirdComma + 1, fourthComma);
  String snr = input.substring(fourthComma + 1);

  unsigned long currentTime = millis();
  String logEntry = String(currentTime) + "," + data + "," + rssi + "," + snr;

  logFile = SD.open("log.csv", FILE_WRITE);
  if (logFile) {
    logFile.println(logEntry);
    logFile.close();
  } else {
    Serial.println("로그 파일 열기 실패");
  }
}
