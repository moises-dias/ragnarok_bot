#include <Keyboard.h>
#include <Mouse.h>

String incoming = "";
bool captcha_state = false;

void setup() {
  delay(1000);
  pinMode(3, INPUT_PULLUP); // pino 3 no low segura o programa
  Keyboard.begin();
  Mouse.begin();
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  while (digitalRead(3) == HIGH) {
    if (!captcha_state) {
      move();
      attack();
    }
    check_captcha();
  }
}

void move() {
  Keyboard.press(KEY_LEFT_ALT);
  delay(100);
  Keyboard.press('1');
  delay(100);
  Keyboard.releaseAll();
  delay(100);
}

void attack() {
  for(int i = 0; i < 4; i++) {
    Keyboard.press(KEY_F1);
    delay(100);
    Mouse.press();
    delay(100);
    Keyboard.releaseAll();
    delay(100);
    Mouse.release();
    delay(100);
  }
}

void check_captcha() {
  while(Serial.available()){
    char inChar = (char)Serial.read();

    if (inChar == 'l') {
      captcha_state = true; // lock
    }
    else if (inChar == 'u') {
      captcha_state = false; // unlock
    }
    else if (inChar == 'e') {
      Keyboard.press(KEY_RETURN);
      delay(100);
      Keyboard.releaseAll();
    }
    else {
      Keyboard.press(inChar);
      delay(100);
      Keyboard.releaseAll();
    }
    delay(700);
  }
}