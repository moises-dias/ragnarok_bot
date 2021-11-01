#include <Keyboard.h>
#include <Mouse.h>

String incoming = "";
bool captcha_state = false;

void setup() {
  delay(1000);
  pinMode(3, INPUT_PULLUP); // pino 3 no low segura o programa
  pinMode(10, INPUT_PULLUP); // pino 10 no low autoclicka
  Keyboard.begin();
  Mouse.begin();
  Serial.begin(9600);
  delay(1000);
}

int ctr = 0;
bool boxes = false;
void loop() {
  while (digitalRead(3) == HIGH) {
    if (!captcha_state) {
      move();
      attack();
    }
    check_captcha();
    ctr++;
    if (ctr > 200) {
      chama_reveladora();
      ctr = 0;
    }
  }
  while (digitalRead(10) == HIGH) {
    Keyboard.press('1');
    delay(20);
    Keyboard.releaseAll();
    delay(20);
    Mouse.press();
    delay(20);
    Mouse.release();
    delay(20);
    Keyboard.press('1');
    delay(20);
    Keyboard.releaseAll();
    delay(20);
    Mouse.press();
    delay(20);
    Mouse.release();
    delay(20);
  }
}

void chama_reveladora() {
  for(int i = 0; i < 10; i++) {
    Keyboard.press(KEY_F2);
    delay(200);
    Keyboard.releaseAll();
    delay(200);
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
  for(int i = 0; i < 7; i++) {
    Keyboard.press(KEY_F1);
    delay(100);
    Mouse.press();
    delay(100);
    Keyboard.releaseAll();
    delay(100);
    Mouse.release();
    delay(100);
    if (boxes) {
      for(int i = 0; i < 5; i++) {
        Keyboard.press(KEY_F3);
        delay(30);
        Keyboard.releaseAll();
        delay(30);
      }
    }
    
  }
}

void check_captcha() {
  while(Serial.available()){
    char inChar = (char)Serial.read();

    if (inChar == 's') { // storage
      store_items();
    }
    else if (inChar == 'b') { // boxes
      boxes = !boxes;
    }
    else if (inChar == 'l') {
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

void store_items() {
  // espera ataque atual acabar
  delay(4000);
  // abrir bau
  for(int i = 0; i < 2; i++) {
    Keyboard.press(KEY_LEFT_ALT);
    delay(200);
    Keyboard.press('0');
    delay(200);
    Keyboard.releaseAll();
    delay(200);
  }

  // resetar posicao do mouse
  for(int i = 0; i < 7; i++) {
    Mouse.move(-127, -127, 0);
  }
  delay(200);
  // mover mouse ate ygg/caixa
  Mouse.move(50, 120, 0);
  Mouse.move(0, 60, 0);
  delay(200);
  for(int i = 0; i < 3; i++) {
    // clicar no ygg/caixa
    Mouse.press();
    delay(200);
    // arrastar ate o bau
    Mouse.move(120, 0, 0);
    Mouse.move(120, 0, 0);
    Mouse.move(40, 0, 0);
    delay(200);
    Mouse.release();
    delay(200);
    // dar enter
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.releaseAll();
    delay(200);
    // retorna pra pegar o segundo apenas
    if (i < 2) {
      Mouse.move(-120, 0, 0);
      Mouse.move(-120, 0, 0);
      Mouse.move(-40, 0, 0);
      delay(200);
    }
  }

  // fazer 2x so pra garantir, pegar 2 d kda
  for(int i = 0; i < 2; i++) {
    // mouse ja ta no ygg/caixa no bau, trazer um de cada
    for(int i = 0; i < 2; i++) {
      // clicar no ygg/caixa
      Mouse.press();
      delay(200);
      // arrastar ate o inventario
      Mouse.move(-120, 0, 0);
      delay(200);
      Mouse.release();
      delay(200);
      // pegar um apenas
      if (i == 0) {
        Keyboard.press('1');
        delay(200);
        Keyboard.releaseAll();
        delay(200);
      }
      // dar enter
      Keyboard.press(KEY_RETURN);
      delay(200);
      Keyboard.releaseAll();
      delay(200);
      // retorna pra pegar o segundo apenas
      if (i == 0) {
        Mouse.move(120, 0, 0);
        Mouse.move(0, 30, 0);
        delay(200);
      }
    }
    Mouse.move(120, 0, 0);
    Mouse.move(0, -30, 0);
  }
  Mouse.move(100, 100, 0);
  Mouse.move(100, 100, 0);
}
