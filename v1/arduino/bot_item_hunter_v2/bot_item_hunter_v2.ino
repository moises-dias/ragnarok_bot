#include <Keyboard.h>
#include <Mouse.h>

int ctr = 0;
bool boxes = false;
bool tickets = false;

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
    check_serial();
    move();
    attack();
    ctr++;
    if (ctr > 200 || ctr < 0) {
      chama_reveladora();
      ctr = 0;
    }
    while (tickets) {
      check_serial();
      store_items();
      // make_ticket();
    }
  }
}

void keyboard_press(char key, int timeout) {
  Keyboard.press(key);
  delay(timeout);
}

void keyboard_release(int timeout) {
  Keyboard.releaseAll();
  delay(timeout);
}

void keyboard_click(char key, int timeout) {
  keyboard_press(key, timeout);
  keyboard_release(timeout);
}

void mouse_press(int timeout) {
  Mouse.press();
  delay(timeout);
}

void mouse_release(int timeout) {
  Mouse.release();
  delay(timeout);
}

void mouse_click(int timeout) {
  mouse_press(timeout);
  mouse_release(timeout);
}


void chama_reveladora() {
  for(int i = 0; i < 10; i++) {
    keyboard_click(KEY_F2, 200);
  }
}

void move() {
  keyboard_press(KEY_LEFT_ALT, 100);
  keyboard_press('1', 100);
  keyboard_release(100);
}

void attack() {
  for(int i = 0; i < 10; i++) {
    if (check_serial())
      return;
    keyboard_click(KEY_F1, 100);
    mouse_click(100);
    if (boxes) {
      for(int i = 0; i < 3; i++) {
        keyboard_click(KEY_F3, 30);
      }
    }
  }
}

bool check_serial() {
  while(Serial.available()){
    char inChar = (char)Serial.read();
    delay(500);

    if (inChar == 't') { // tickets
      tickets = true;
      return false;
    }
    else if (inChar == 'b') { // boxes
      boxes = !boxes;
      return false;
    }
    else if (inChar == 'c') { // captcha
      while (inChar != 'f') { // finished
        inChar = (char)Serial.read();
        delay(500);
        if (inChar == 'e') {
          keyboard_click(KEY_RETURN, 100);
        }
        else if (inChar != 'f') {
          keyboard_click(inChar, 100);
        }
      }
      return true;
    }
  }
  return false;
}

void reset_cursor(int timeout) {
  for(int i = 0; i < 7; i++) {
    Mouse.move(-127, -127, 0);
  }
  delay(timeout);
}

// void move_cursor(int m_x, int m_y, int timeout) {
//   while (m_x > 0 || m_y > 0) {
//     if (m_x > 126)
//       to_move_x = 127;
//     else
//       to_move_x = m_x;
//     if (m_y > 126)
//       to_move_y = 127;
//     else
//       to_move_y = m_y;
//     Mouse.move(to_move_x, to_move_y, 0);
//     if (to_move_x > 0)
//       m_x -= to_move_x;
//     if (to_move_y > 0)
//       m_y -= to_move_y;
//   }
//   delay(timeout);
// }

void move_cursor(int m_x, int m_y, int timeout) {
  while (abs(m_x) != 0 || abs(m_y) != 0) {
    if (m_x > 126)
      to_move_x = 127;
    else if (m_x < -126)
      to_move_x = -127
    else
      to_move_x = m_x;

    if (m_y > 126)
      to_move_y = 127;
    else if (m_y < -126)
      to_move_y = -127
    else
      to_move_y = m_y;

    Mouse.move(to_move_x, to_move_y, 0);
    if (to_move_x != 0)
      m_x -= to_move_x;
    if (to_move_y != 0)
      m_y -= to_move_y;
  }
  delay(timeout);
}

void make_ticket() {

  // mover até npc
  for (int i = 0; i < 3; i++) {
    keyboard_press(KEY_LEFT_ALT, 100);
    keyboard_press('2', 100);
    keyboard_release(100);
  }
  // delay(7000);

  // resetar posicao do mouse
  reset_cursor(150);
  // move mouse ate npc
  move_cursor(400, 350, 150);

  // fazendo 3 tickets
  for (int i = 0; i < 5; i++) {
    // check_serial();
    // clica enter enter enter baixo enter enter
    mouse_click(150);
    keyboard_click(KEY_RETURN, 150);
    keyboard_click(KEY_RETURN, 150);
    keyboard_click(KEY_RETURN, 150);
    keyboard_click(KEY_DOWN_ARROW, 150);
    keyboard_click(KEY_RETURN, 150);
    keyboard_click(KEY_RETURN, 150);
  }

  tickets = false;
}

void store_items() {
  // espera ataque atual acabar
  delay(4000);
  if (check_serial())
    return;
  // abrir bau
  for(int i = 0; i < 2; i++) {
    keyboard_press(KEY_LEFT_ALT, 100);
    keyboard_press('0', 100);
    keyboard_release(100);
  }
  // resetar posicao do mouse
  reset_cursor(100);
  // mover mouse ate ygg/caixa
  move_cursor(50, 180, 100);
  for(int i = 0; i < 3; i++) {
    // clicar no ygg/caixa
    mouse_press(100);
    // arrastar ate o bau
    move_cursor(280, 0, 100);
    mouse_release(100);
    // dar enter
    if (check_serial())
      return;
    keyboard_click(KEY_RETURN, 100);
    // retorna pra pegar o segundo apenas
    if (i < 2) {
      move_cursor(-280, 0, 100);
    }
  }

  // fazer 2x so pra garantir, pegar 2 d kda
  for(int i = 0; i < 2; i++) {
    // mouse ja ta no ygg/caixa no bau, trazer um de cada
    for(int i = 0; i < 2; i++) {
      // clicar no ygg/caixa
      mouse_press(100);
      // arrastar ate o inventario
      move_cursor(-120, 0, 100);
      mouse_release(100);
      // pegar um apenas
      if (i == 0) {
        keyboard_click('1', 100);
      }
      // dar enter
      if (check_serial())
        return;
      keyboard_click(KEY_RETURN, 100);
      // retorna pra pegar o segundo apenas
      if (i == 0) {
        move_cursor(120, 30, 100);
      }
    }
    Mouse.move(120, -30, 0);
  }
  move_cursor(200, 200, 100);

  tickets = false;
}
