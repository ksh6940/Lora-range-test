#define LED_pin 13
const int btn_pin = 2;
int buttonState = 0;
int lastButtonState = 0;

void setup() {
  Serial.begin(57600);
  pinMode(LED_pin, OUTPUT);
  pinMode(btn_pin, INPUT);
}

void loop() {
  buttonState = digitalRead(btn_pin);

  if (buttonState == HIGH && lastButtonState == LOW) {
    digitalWrite(LED_pin, HIGH);
    Serial.println("AT+SEND=2,1,Hello World");
    delay(200);
  }

  if (buttonState == LOW) {
    digitalWrite(LED_pin, LOW);
  }

  lastButtonState = buttonState;
}
