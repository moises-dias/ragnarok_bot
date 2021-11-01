#include <Keyboard.h>
#include <Mouse.h>


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
    store_items();
  }
}


void store_items() {
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
      Keyboard.press('1');
      delay(200);
      Keyboard.releaseAll();
      delay(200);
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