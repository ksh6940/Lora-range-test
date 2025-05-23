# LoRa Range Test 🛰️📶

LoRa (Long Range) 통신 모듈의 거리별 신호 감쇠율(Attenuation Rate)을 측정하고 분석 데이터 저장 리포지토리입니다.

---

## 📌 목적 (Purpose)
- 거리 증가에 따른 **LoRa 신호 세기(RSSI)** 변화 측정
- 감쇠 계수(Attenuation Coefficient) 도출
- 실외 환경/실내 환경에서의 LoRa 통신 가능 거리 추정

---

## ⚙️ 실험 구성 (Experiment Setup)
- **LoRa 모듈**: RYLR998  
- **주파수 대역**: 915MHz   
- **측정 방식**: 송신 모듈 → 일정 거리마다 RSSI 수신 및 기록
- **측정 장소**: 공주고등학교 본동 2층 / 과학관 옆 주차장 

### 사용 장비
| 구성 요소 | 설명 |
|-----------|------|
| 송신기 | RYLR998 LoRa 모듈 + Arduino |
| 수신기 | 동일 모듈 + RSSI 로그 기록 |
| 측정 도구 | 줄자 |

---

## 🧪 실험 방법 (How to Test)
1. 거리별 위치에 포인트 지점을 표시
2. 수신기는 처음 위치에 배치하고, 송신기는 포인트를 옮겨가며 데이터를 송신
3. 송신기로부터 받은 수신기는 데이터를 csv 파일로 하여금 sd카드에 저장
4. 파이썬을 활용하여 데이터 분석을 통한 결과 분석

---

## 📁 데이터 및 코드 (Data & Code)
- `data/` : 실험 데이터 (.csv)  
- `src/` : 분석 코드 (Python, Jupyter Notebook)  
- `hardware/` : 회로 구성 및 안테나 정보

---

## 🔍 분석 내용
- 신호 감쇠 그래프 (거리 vs. RSSI)
- 로그 회귀를 통한 감쇠율 계산
- LoRa 전파 특성 시각화 (matplotlib 사용)
- 실내 환경과 실외 환경 비교 

--- 

## 📡 LoRa Signal Tracker 
- Vercel V0를 통해 제작
- 송신기와 연결하여 실험 중 진행 상황을 확인 목적

**url** : [LoRa Signal Tracker](https://v0-arduino-lo-ra-monitor.vercel.app/)

---

## 📬 연락처 (Contact)
작성자: ksh6940
문의: [GitHub Issues](https://github.com/ksh6940/Lora-range-test/issues)

---

## 📄 라이선스
현재 이 리포지토리는 별도의 라이선스를 지정하지 않았습니다.  
따라서 모든 권리는 작성자에게 있으며, 무단 사용, 복제, 배포를 금합니다.  
필요 시 [Issues](https://github.com/ksh6940/Lora-range-test/issues)로 문의 바랍니다.

