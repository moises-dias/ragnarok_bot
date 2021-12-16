#include <Keyboard.h>
#include <Mouse.h>

void setup() {
  delay(1000);
  pinMode(10, INPUT_PULLUP); // pino 10 no high guarda ticket
  Keyboard.begin();
  Mouse.begin();
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  while (digitalRead(10) == HIGH) {
    ticket();
  }
}

void ticket() {

  // resetar posicao do mouse
  for(int i = 0; i < 7; i++) {
    Mouse.move(-127, -127, 0);
  }
  delay(200);
  // move mouse ate npc
  Mouse.move(100, 100, 0);
  Mouse.move(100, 100, 0);  
  Mouse.move(100, 100, 0);  
  Mouse.move(100, 50, 0);  
  delay(200);

  // fazendo 5 tickets
  for (int i = 0; i < 5; i++) {
    // clica enter enter enter baixo enter enter
    Mouse.press();
    delay(200);
    Mouse.release();
    delay(200);
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.releaseAll();
    delay(200);
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.releaseAll();
    delay(200);
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.releaseAll();
    delay(200);
    Keyboard.press(KEY_DOWN_ARROW);
    delay(200);
    Keyboard.releaseAll();
    delay(200);
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.releaseAll();
    delay(200);
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.releaseAll();
    delay(200);
  }

  // abrir bau
  Keyboard.press(KEY_LEFT_ALT);
  delay(200);
  Keyboard.press('3');
  delay(200);
  Keyboard.releaseAll();
  delay(200);
  Keyboard.press(KEY_LEFT_ALT);
  delay(200);
  Keyboard.press('0');
  delay(200);
  Keyboard.releaseAll();
  delay(200);

  // resetar posicao do mouse
  for(int i = 0; i < 7; i++) {
    Mouse.move(-127, -127, 0);
  }
  delay(200);

  // mover mouse ate ygg
  Mouse.move(100, 100, 0);
  Mouse.move(100, 90, 0);
  Mouse.move(100, 0, 0);
  Mouse.move(40, 0, 0);
  delay(200);

  // clicar no ygg
  Mouse.press();
  delay(200);

  // arrastar ate o inventario
  Mouse.move(-120, 0, 0);
  delay(200);
  Mouse.release();
  delay(200);
  // pegar 500
  Keyboard.press('5');
  delay(200);
  Keyboard.releaseAll();
  delay(200);
  Keyboard.press('0');
  delay(200);
  Keyboard.releaseAll();
  delay(200);
  Keyboard.press('0');
  delay(200);
  Keyboard.releaseAll();
  delay(200);
  // dar enter
  Keyboard.press(KEY_RETURN);
  delay(200);
  Keyboard.releaseAll();
  delay(200);

  // sai do inventario
  Keyboard.press(KEY_LEFT_ALT);
  delay(200);
  Keyboard.press('2');
  delay(200);
  Keyboard.releaseAll();
  delay(1000);
}
