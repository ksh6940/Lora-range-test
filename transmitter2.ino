#include <math.h>

float angle = 0.0;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  float sineValue = sin(angle); 
  
  angle += 0.1;
  
  if (angle >= 360.0) {
    angle = 0.0;  
  }

  // 사인 값 출력
  Serial.print("sin : ");
  Serial.println(sineValue);
  delay(100);  // 0.1초 대기

  // sineValue가 1.00 또는 -1.00에 가까운 값일 때만 조건을 만족
  if (abs(sineValue - 1.0) < 0.01 || abs(sineValue + 1.0) < 0.01) {
    Serial.println("AT+SEND=2,1,A");
    delay(1000);  // 1초 대기 (송신 간격)
  }
}
