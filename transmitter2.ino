#include <SoftwareSerial.h>
#include <math.h>

SoftwareSerial mySerial(10, 11);  // RX, TX 핀 (0, 1은 기본 시리얼에 사용됨)

float angle = 0.0;

void setup() {
  Serial.begin(9600);  // 하드웨어 시리얼 통신 시작
  mySerial.begin(9600);  // Rylr998 모듈과의 통신 속도 설정

  Serial.println("송신기 준비 완료!");
  delay(1000);

  // LoRa 모듈 초기화
  mySerial.println("AT+MODE=1");  // 1: 송신 모드
  delay(1000);

  Serial.print("Initializing LoRa Module... ");
}

void loop() {
  float sineValue = sin(angle);  // 사인 함수 계산
  
  angle += 0.1;  // 각도 증가
  
  if (angle >= 360.0) {
    angle = 0.0;  // 360도 이상이면 초기화
  }

  // 사인 값 출력
  Serial.print("sin : ");
  Serial.println(sineValue);
  delay(100);  // 0.1초 대기

  // sineValue가 1.00 또는 -1.00에 가까운 값일 때만 조건을 만족
  if (abs(sineValue - 1.0) < 0.01 || abs(sineValue + 1.0) < 0.01) {
    // 데이터 송신: AT+SEND=<length>,<destination>,<data>
    // <length> = 데이터의 길이 (Hello World는 11자)
    // <destination>은 수신기의 주소, 여기에선 1번으로 설정
    Serial.println("AT+SEND=11,1,Hello World");  // 11은 데이터 길이, 1은 수신기 주소
    mySerial.println("AT+SEND=11,1,Hello World");  // 실제 LoRa 모듈에 데이터 송신

    delay(1000);  // 1초 대기 (송신 간격)
  }
}
